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

#include "options.h"

/**
 * @brief Initialize parameters with default values
 *
 */
Options::Options(void) :
    useColors(false),       // Whether to use colors when printing to console
    forceAnsiCodes(false),  // Whether to use ANSI escape codes on Windows
    outputToFile(false),    // Whether to output to file instead of a console
    contextLines(3),        // Number of context lines
    outputFilePath() { }    // Path to the output file

/**
 * @brief Check whether colors are used when printing to console
 *
 * @return true if colors are used when printing to console, false otherwise
 */
bool Options::getUseColors(void) const
{
    return this->useColors;
}

/**
 * @brief Specify whether colors are used when printing to console
 *
 * @param useColors Whether colors are used when printing to console
 */
void Options::setUseColors(bool useColors)
{
    this->useColors = useColors;
}

/**
 * @brief Specify whether ANSI escape codes are used on Windows
 *
 * @param forceAnsiCodes Whether ANSI escape codes are used on Windows
 */
bool Options::getForceAnsiCodes(void) const
{
    return this->forceAnsiCodes;
}

/**
 * @brief Specify whether ANSI escape codes are used on Windows
 *
 * @param forceAnsiCodes Whether ANSI escape codes are used on Windows
 */
void Options::setForceAnsiCodes(bool forceAnsiCodes)
{
    this->forceAnsiCodes = forceAnsiCodes;
}

/**
 * @brief Check whether the output is set to file instead of a console
 *
 * @return true if whether the output is set to file, false otherwise
 */
bool Options::getOutputToFile(void) const
{
    return this->outputToFile;
}

/**
 * @brief Specify whether the output is set to file instead of a console
 *
 * @param outputToFile Whether the output is set to file instead of a console
 */
void Options::setOutputToFile(bool outputToFile)
{
    this->outputToFile = outputToFile;
}

/**
 * @brief Get the number of context lines
 *
 * @return Number of context lines
 */
unsigned int Options::getContextLines(void) const
{
    return this->contextLines;
}

/**
 * @brief Set the number of context lines
 *
 * @param contextLines Number of context lines
 */
void Options::setContextLines(unsigned int contextLines)
{
    this->contextLines = contextLines;
}

/**
 * @brief Get the path to the output file
 *
 * @return Path to the output file
 */
std::string Options::getOutputFilePath(void) const
{
    return this->outputFilePath;
}

/**
 * @brief Set the path to the output file
 *
 * @param outputFilePath Path to the output file
 */
void Options::setOutputFilePath(const std::string& outputFilePath)
{
    this->outputFilePath = outputFilePath;
}