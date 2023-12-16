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

#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

#include <string>
#include <vector>

#include "argument.h"
#include "options.h"

/**
 * @brief Class containing the main logic for application
 *
 */
class AppController
{
    private:
        /**
         * @brief List of valid command line arguments
         *
         */
        const std::vector<Argument> args;
        /**
         * @brief Number of command line arguments
         *
         */
        const int argc;
        /**
         * @brief Command line arguments passed to the program
         *
         */
        char** argv;
        /**
         * @brief Program options
         *
         */
        Options options;
        /**
         * @brief Path to the original file
         *
         */
        std::string originalFilename;
        /**
         * @brief Path to the modified file
         *
         */
        std::string modifiedFilename;
        /**
         * @brief Lines from the original file
         *
         */
        std::vector<std::string> original;
        /**
         * @brief Lines from the modified file
         *
         */
        std::vector<std::string> modified;
        /**
         * @brief Display help (usage)
         *
         */
        void displayHelp(void);

    public:
        /**
         * @brief Initialize parameters
         *
         * @param argc Number of command line arguments
         * @param argv Command line arguments passed to the program
         * @param args List of valid command line arguments
         */
        AppController(int argc, char* argv[], std::vector<Argument>& args);
        /**
         * @brief Parse command line arguments
         *
         * @return true if parsing was successful and
         * help was not displayed, false otherwise
         */
        bool parseArguments(void);
        /**
         * @brief Read contents of the original and modified files
         *
         */
        void readFileContents(void);
        /**
         * @brief Calculate and output the difference between files
         *
         */
        void calculateDiff(void);
};

#endif // APP_CONTROLLER_H