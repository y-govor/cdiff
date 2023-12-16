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

#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>

/**
 * @brief Program options
 *
 */
class Options
{
    private:
        /**
         * @brief Whether to use colors when printing to console
         *
         */
        bool useColors;
        /**
         * @brief Whether to use ANSI escape codes for colors on Windows
         *
         */
        bool forceAnsiCodes;
        /**
         * @brief Whether to output to file instead of a console
         *
         */
        bool outputToFile;
        /**
         * @brief Number of context lines
         *
         */
        unsigned int contextLines;
        /**
         * @brief Path to the output file
         *
         */
        std::string outputFilePath;

    public:
        /**
         * @brief Initialize parameters with default values
         *
         */
        Options(void);
        /**
         * @brief Check whether colors are used when printing to console
         *
         * @return true if colors are used when printing to console, false otherwise
         */
        bool getUseColors(void) const;
        /**
         * @brief Specify whether colors are used when printing to console
         *
         * @param useColors Whether colors are used when printing to console
         */
        void setUseColors(bool useColors);
        /**
         * @brief Check whether ANSI escape codes are used on Windows
         *
         * @return true if ANSI escape codes are used on Windows, false otherwise
         */
        bool getForceAnsiCodes(void) const;
        /**
         * @brief Specify whether ANSI escape codes are used on Windows
         *
         * @param forceAnsiCodes Whether ANSI escape codes are used on Windows
         */
        void setForceAnsiCodes(bool forceAnsiCodes);
        /**
         * @brief Check whether the output is set to file instead of a console
         *
         * @return true if whether the output is set to file, false otherwise
         */
        bool getOutputToFile(void) const;
        /**
         * @brief Specify whether the output is set to file instead of a console
         *
         * @param outputToFile Whether the output is set to file instead of a console
         */
        void setOutputToFile(bool outputToFile);
        /**
         * @brief Get the number of context lines
         *
         * @return Number of context lines
         */
        unsigned int getContextLines(void) const;
        /**
         * @brief Set the number of context lines
         *
         * @param contextLines Number of context lines
         */
        void setContextLines(unsigned int contextLines);
        /**
         * @brief Get the path to the output file
         *
         * @return Path to the output file
         */
        std::string getOutputFilePath(void) const;
        /**
         * @brief Set the path to the output file
         *
         * @param outputFilePath Path to the output file
         */
        void setOutputFilePath(const std::string& outputFilePath);
};

#endif // OPTIONS_H