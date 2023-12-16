/** MIT License
 *
 * Copyright (c) 2023 Yurii Govor
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "diff.h"

#include <algorithm>
#include <iostream>
#include <sstream>

#include "file_handler.h"
#include "file_helper.h"

// For compatibility with MSVC
#ifdef min
#undef min
#endif

/**
 * @brief Initialize parameters with specified values
 *
 * @param original Lines from the original file
 * @param modified Lines from the modified file
 * @param originalFilename Name of the original file
 * @param modifiedFilename Name of the modified file
 * @param options Program options
 */
Diff::Diff(std::vector<std::string>& original,
           std::vector<std::string>& modified,
           const std::string& originalFilename,
           const std::string& modifiedFilename,
           Options& options) :
           original(original),
           modified(modified),
           originalFilename(originalFilename),
           modifiedFilename(modifiedFilename),
           options(options),
           N(original.size()),
           M(modified.size()),
           MAX(N + M) { }

/**
 * @brief Calculate the difference between two sequences.
 * Based on 'An O(ND) Difference Algorithm' by Eugene W. Myers
 * http://www.xmailserver.org/diff2.pdf
 *
 */
void Diff::calculate(void)
{
    // Vector for storing furthest-reaching matching points
    // along diagonals in the edit graph
    std::vector<int> v_x(MAX * 2 + 1, 0);
    // Vector for storing history of changes for each diagonal
    std::vector<std::vector<DiffItem>> v_history(MAX * 2 + 1);

    int x, oldX, y;
    // Vector for storing current history of changes
    std::vector<DiffItem> history;

    for(int d = 0; d <= MAX; d++) // Possible differences
    {
        for(int k = -d; k <= d; k += 2) // Positions within the diagonal range
        {
            // Check if k is at the boundary or the value to the left
            // is smaller than the value to the right
            if(k == -d || (k != -d && v_x[MAX + k - 1] < v_x[MAX + k + 1]))
            {
                // Update x, oldX, and history based on the value to the right
                oldX = v_x[MAX + k + 1];
                history = v_history[MAX + k + 1];
                x = oldX;
            }
            else
            {
                // Update x, oldX, and history based on the value to the left
                oldX = v_x[MAX + k - 1];
                history = v_history[MAX + k - 1];
                x = oldX + 1;
            }

            y = x - k;

            // Detect insertion or removal of the line
            if((y >= 1 && y <= M) && (k == -d ||
               (k != -d && v_x[MAX + k - 1] < v_x[MAX + k + 1]))) // Line was inserted
            {
                // Add line insertion to the history
                history.push_back(DiffItem(Change::Insert,
                    (x - 1 < 0) ? 0 : (x - 1),  // Line in the old file
                    (y - 1 < 0) ? 0 : (y - 1))  // Line in the new file
                );
            }
            else if(x >= 1 && x <= N) // Line was removed
            {
                // Add line removal to the history
                history.push_back(DiffItem(Change::Remove,
                    (x - 1 < 0) ? 0 : (x - 1),  // Line in the old file
                    (y - 1 < 0) ? 0 : (y - 1))  // Line in the new file
                );
            }

            // Add all unchanged lines to the history
            while(x < N && y < M && original[x] == modified[y])
            {
                x++;
                y++;

                history.push_back(DiffItem(Change::Equal,
                    (x - 1 < 0) ? 0 : (x - 1),  // Line in the old file
                    (y - 1 < 0) ? 0 : (y - 1))  // Line in the new file
                );
            }

            // Check if the end of both sequences is reached
            if(x >= N && y >= M)
            {
                // Save history and stop
                items = history;
                return;
            }
            else
            {
                // Update v_x and v_history with the current state
                v_x[MAX + k] = x;
                v_history[MAX + k] = history;
            }
        }
    }

    // The length of SES (shortest edit script) exceeds the maximum length
    throw std::runtime_error("could not find edit script");
}

/**
 * @brief Generate output of the hunk and write it to stream
 *
 * @param os Output stream
 * @param ch Smart pointer to the ColorHandler instance
 * @param start Index of the start of the hunk
 * @param end Index of the end of the hunk
 * @param linesChangedOld Number of lines changed in the original file
 * @param linesChangedNew Number of lines changed in the modified file
 */
void Diff::generateHunk(std::ostream& os,
                        std::unique_ptr<ColorHandler>& ch,
                        unsigned short start,
                        unsigned short end,
                        unsigned short linesChangedOld,
                        unsigned short linesChangedNew) const
{
    // Whether to use colors (only while printing to console)
    bool useColors = options.getUseColors() && !options.getOutputToFile();

    // Output range information

    if(useColors) ch->setColor(Color::Magenta);

    os << "@@ -"
        << items[start].getLineOld() + 1 // Starting line in the original file
        << ','
        << linesChangedOld // Number of lines in the original file the hunk
        << " +"            //                                    applies to
        << items[start].getLineNew() + 1 // Starting line in the modified file
        << ','
        << linesChangedNew // Number of lines in the modified file the hunk
        << " @@\n";        //                                    applies to

    if(useColors) ch->resetColor();

    // Output the hunk

    for(int i = start; i <= end; i++)
    {
        if(items[i].getChange() == Change::Remove) // Line is removed
        {
            if(useColors) ch->setColor(Color::Red);
            os << '-' << original[items[i].getLineOld()] << '\n';
            if(useColors) ch->resetColor();
        }
        else if(items[i].getChange() == Change::Insert) // Line is inserted
        {
            if(useColors) ch->setColor(Color::Green);
            os << '+' << modified[items[i].getLineNew()] << '\n';
            if(useColors) ch->resetColor();
        }
        else // Unchanged line
        {
            os << ' ' << original[items[i].getLineOld()] << '\n';
        }
    }
}

/**
 * @brief Generate output in unified format and write it to stream
 *
 * @param os Output stream
 */
void Diff::generateUnidiff(std::ostream& os) const
{
    // Create a smart pointer to the ColorHandler class
    std::unique_ptr<ColorHandler> ch = nullptr;
    // Whether to use colors (only while printing to console)
    bool useColors = options.getUseColors() && !options.getOutputToFile();

    try
    {
        // Create an instance of ColorHandler class
        // and assign it to the smart pointer
        ch = std::unique_ptr<ColorHandler>(
            new ColorHandler(options.getForceAnsiCodes())
        );
    }
    catch(std::exception& e)
    {
        std::cerr << "Error: " << e.what()
                  << "\nCould not initialize colors. Try disabling them.\n";
        return;
    }

    // Number of diff items
    const unsigned int itemCount = items.size();

    /*
     * A hunk is a block of consecutive changed lines, along with a
     * specified number of unchanged lines before and after it for context.
    */

    bool isHunk = false; // Is inside a hunk
    unsigned short hunkStart = 0; // Index where the hunk starts
    unsigned short hunkEnd = 0; // Index where the hunk ends
    unsigned short linesCount = 0; // Number of lines from the start of the
                                   // sequence or the end of the previous hunk
    unsigned short equalsCount = 0; // Number of unchanged lines
    unsigned short removesCount = 0; // Number of removed lines
    unsigned short insertsCount = 0; // Number of inserted lines
    unsigned int end; // Prediction of the index of the last item in the hunk
    unsigned int i, j; // Loop counters

    DateTime dtOriginal;
    DateTime dtModified;

    try
    {
        // Get last modification date of the original file
        FileHelper::getLastModifiedDate(originalFilename, dtOriginal);

        // Get last modification date of the original file
        FileHelper::getLastModifiedDate(modifiedFilename, dtModified);
    }
    catch(std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return;
    }

    // Output the header

    if(useColors) ch->setColor(Color::Red);
    os << "--- " << originalFilename << '\t' << dtOriginal.format() << '\n';
    if(useColors) ch->setColor(Color::Green);
    os << "+++ " << modifiedFilename << '\t' << dtModified.format() << '\n';
    if(useColors) ch->resetColor();

    // Iterate through all diff items
    for(i = 0, j = 1; i < itemCount; i++, j++)
    {
        // If not inside a hunk
        if(!isHunk)
        {
            if(items[i].getChange() != Change::Equal) // Changed line
            {
                isHunk = true;
                hunkEnd = i - 1;
            }
            else // Unchanged line
            {
                // If at the start of the sequence or
                // the previous hunk just ended,
                // count unchanged lines but only up to
                // the specified amount needed for context
                if(linesCount >= options.getContextLines())
                    hunkStart++;
                else
                    equalsCount++;

                linesCount++;
            }
        }

        // If inside a hunk
        if(isHunk)
        {
            if(items[i].getChange() == Change::Insert) // Inserted line
            {
                hunkEnd++; // Shift the position of the end of the hunk
                insertsCount++;
            }
            else if(items[i].getChange() == Change::Remove) // Removed line
            {
                hunkEnd++; // Shift the position of the end of the hunk
                removesCount++;
            }
            else // Unchanged line
            {
                // Mark the end of the hunk
                // (not including unchanged lines after)
                isHunk = false;
                linesCount = 0;

                // Calculate the end of the hunk.
                // Either up to n or to the last item,
                // where n is the number of context lines
                end = std::min(hunkEnd + options.getContextLines() + 1, itemCount);

                // Check n lines ahead
                for(j = hunkEnd + 1; j < end; j++)
                {
                    // If unchanged line found
                    if(items[j].getChange() != Change::Equal)
                    {
                        // Continue the hunk
                        isHunk = true;
                        break;
                    }
                    else
                    {
                        equalsCount++;
                        hunkEnd++; // Shift the index of the end of the hunk
                    }
                }

                // Skip checked elements
                i = j - 1;

                // If the end of the sequence is reached
                if(j == itemCount - 1)
                {
                    // Output the hunk
                    generateHunk(os, ch, hunkStart, hunkEnd,
                        equalsCount + removesCount,
                        equalsCount + insertsCount);

                    break;
                }

                // Skip the rest of the loop iteration if still inside a hunk
                if(isHunk) continue;

                // Check the next n + 1 lines to detect if the next hunk
                // goes right after the current one. In this case they will
                // be merged into one hunk.
                end = std::min(end + options.getContextLines(), itemCount);

                for(j = i; j < end; j++)
                {
                    if(items[j].getChange() != Change::Equal) // Changed line detected
                        break;

                    // If next n lines were checked, check the next line.
                    // If the next line is changed, continue the hunk
                    if(j == end - 1 && j + 1 < itemCount &&
                       items[j + 1].getChange() != Change::Equal)
                        isHunk = true;
                }

                // Skip the rest of the loop iteration if still inside a hunk
                if(isHunk) continue;

                // Output the hunk
                generateHunk(os, ch, hunkStart, hunkEnd,
                    equalsCount + removesCount,
                    equalsCount + insertsCount);

                linesCount = 0;
                equalsCount = 0;
                insertsCount = 0;
                removesCount = 0;
                hunkStart = hunkEnd + 1;
                i = hunkStart - 1;
                j = i + 1;
            }

            // If the end of the sequence is reached and hunk isn't printed yet
            if(i == itemCount - 1 && hunkStart < itemCount)
            {
                // Output the hunk
                generateHunk(os, ch, hunkStart, hunkEnd,
                    equalsCount + removesCount,
                    equalsCount + insertsCount);
            }
        }
    }

    // Display a message if a modified file does not end with a new line
    if(!FileHelper::hasEndingNewLine(modifiedFilename))
        os << "\\ No newline at end of file\n";
}

/**
 * @brief Print the difference to console or write it to file
 *
 */
void Diff::print(void) const
{
    if(options.getOutputToFile()) // Write to file
    {
        // Redirect unidiff output to stringstream
        std::stringstream ss;
        generateUnidiff(ss);
        // Create output file stream
        FileHandler outputFile(options.getOutputFilePath(), std::ios::out);
        // Convert stringstream output to string and write it to file
        outputFile.write(ss.str());
    }
    else // Print to console
    {
        generateUnidiff(std::cout);
    }
}