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

#include "app_controller.h"

#include <iostream>
#include <stdexcept>

#include "arg_parser.h"
#include "diff.h"
#include "file_handler.h"
#include "string_helper.h"

/**
 * @brief Initialize parameters
 *
 * @param argc Number of command line arguments
 * @param argv Command line arguments passed to the program
 */
AppController::AppController(int argc, char* argv[], std::vector<Argument>& args) :
    args(args),         // List of valid command line arguments
    argc(argc),         // Number of command line arguments
    argv(argv),         // Command line arguments passed to the program
    options(),          // Program options
    originalFilename(), // Path to the original file
    modifiedFilename(), // Path to the modified file
    original(),         // Lines from the original file
    modified() { }      // Lines from the modified file

/**
 * @brief Display help (usage)
 *
 */
void AppController::displayHelp(void)
{
    std::cout << "Usage: cdiff [options] [files]\n\n"
        << "Description:\n"
        << "  Compare two files and display the difference.\n\n"
        << "Options:\n"
        << "  -h, --help\t\t\tDisplay this help message and exit.\n"
        << "  -c, --color\t\t\tEnable color support when printing to console.\n"
        << "  -a, --force-ansi\t\tUse ANSI escape codes for colors on Windows systems.\n"
        << "  -o, --out-file FILE\t\tRedirect output to the file instead of a console.\n"
        << "  -n, --lines NUM\t\tNumber of lines for context (3 by default).\n\n"
        << "Files:\n"
        << "  original\t\t\tOriginal file.\n"
        << "  modified\t\t\tNew (modified) file.\n\n"
        << "Examples:\n"
        << "  cdiff original.txt modified.txt\n"
        << "  cdiff -c -a original.txt modified.txt\n"
        << "  cdiff -o output.diff -n 5 original.txt modified.txt\n";
}

/**
 * @brief Parse command line arguments
 *
 * @return true if parsing was successful and
 * help was not displayed, false otherwise
 */
bool AppController::parseArguments(void)
{
    ArgParser argParser(argc, argv, args);

    // Parse command line arguments
    argParser.parse();

    // Display help if '-h' or '--help' arguments are present
    if(argParser.getArgumentValue("-h") == "true" ||
       argParser.getArgumentValue("--help") == "true")
    {
        displayHelp();
        return false;
    }

    // Set values for program options
    options.setUseColors(argParser.getArgumentValue("-c") == "true" ||
        argParser.getArgumentValue("--color") == "true");
    options.setForceAnsiCodes(argParser.getArgumentValue("-a") == "true" ||
        argParser.getArgumentValue("--force-ansi") == "true");

    std::string outputFilePath;

    if(!argParser.getArgumentValue("-o").empty())
        outputFilePath = argParser.getArgumentValue("-o");
    else if(!argParser.getArgumentValue("--out-file").empty())
        outputFilePath = argParser.getArgumentValue("--out-file");

    if(!outputFilePath.empty())
    {
        if(StringHelper::isValidFilename(outputFilePath))
        {
            options.setOutputToFile(true);
            options.setOutputFilePath(outputFilePath);
        }
        else
        {
            throw std::invalid_argument("output file name is not valid");
        }
    }

    if(argParser.getArgumentValue("-n") == "3" &&
       argParser.getArgumentValue("--lines") == "3")
    {
        options.setContextLines(3);
    }

    if(argParser.getArgumentValue("-n") != "3")
    {
        // Convert string to unsigned int
        options.setContextLines(
            StringHelper::str2uint(argParser.getArgumentValue("-n"))
        );
    }
    else if(argParser.getArgumentValue("--lines") != "3")
    {
        // Convert string to unsigned int
        options.setContextLines(
            StringHelper::str2uint(argParser.getArgumentValue("--lines"))
        );
    }

    // Path to the original file
    originalFilename = argv[argc - 2];
    // Path to the modified file
    modifiedFilename = argv[argc - 1];

    if(!StringHelper::isValidFilename(originalFilename) ||
       !StringHelper::isValidFilename(modifiedFilename))
        throw std::invalid_argument("input file name is not valid");

    return true;
}

/**
 * @brief Read contents of the original and modified files
 *
 */
void AppController::readFileContents(void)
{
    // Open files
    FileHandler fileOriginal(originalFilename, std::ios::in);
    FileHandler fileModified(modifiedFilename, std::ios::in);

    // Read each line into the vector
    original = fileOriginal.read();
    modified = fileModified.read();

    // Close file streams
    fileOriginal.close();
    fileModified.close();
}

/**
 * @brief Calculate and output the difference between files
 *
 */
void AppController::calculateDiff(void)
{
    Diff diff(original, modified, originalFilename, modifiedFilename, options);
    diff.calculate();
    diff.print();
}