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

#ifndef DIFF_H
#define DIFF_H

#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "color_handler.h"
#include "diff_item.h"
#include "options.h"

/**
 * @brief Class for calculating and printing difference between files
 *
 */
class Diff
{
    private:
        /**
         * @brief Collection of calculated differences
         *
         */
        std::vector<DiffItem> items;
        /**
         * @brief Lines from the original file
         *
         */
        std::vector<std::string>& original;
        /**
         * @brief Lines from the modified file
         *
         */
        std::vector<std::string>& modified;
        /**
         * @brief Name of the original file
         *
         */
        std::string originalFilename;
        /**
         * @brief Name of the modified file
         *
         */
        std::string modifiedFilename;
        /**
         * @brief Program options
         *
         */
        Options& options;
        /**
         * @brief Number of lines in the original file
         *
         */
        const int N;
        /**
         * @brief Number of lines in the modified file
         *
         */
        const int M;
        /**
         * @brief Total number of lines in both files
         *
         */
        const int MAX;
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
        void generateHunk(std::ostream& os,
                          std::unique_ptr<ColorHandler>& ch,
                          unsigned short start,
                          unsigned short end,
                          unsigned short linesChangedOld,
                          unsigned short linesChangedNew) const;
        /**
         * @brief Generate output in unified format and write it to stream
         *
         * @param os Output stream
         */
        void generateUnidiff(std::ostream& os) const;

    public:
        /**
         * @brief Initialize parameters with specified values
         *
         * @param original Lines from the original file
         * @param modified Lines from the modified file
         * @param originalFilename Name of the original file
         * @param modifiedFilename Name of the modified file
         * @param options Program options
         */
        Diff(std::vector<std::string>& original,
             std::vector<std::string>& modified,
             const std::string& originalFilename,
             const std::string& modifiedFilename,
             Options& options);
        /**
         * @brief Calculate the difference between two sequences.
         * Based on 'An O(ND) Difference Algorithm' by Eugene W. Myers
         * http://www.xmailserver.org/diff2.pdf
         *
         */
        void calculate(void);
        /**
         * @brief Print the difference to console or write it to file
         *
         */
        void print(void) const;
};

#endif // DIFF_H