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

#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <cstddef>
#include <string>
#include <vector>

#include "argument.h"

/**
 * @brief Class for parsing command line arguments
 *
 */
class ArgParser
{
    private:
        /**
         * @brief Constant that defines a code of non existing element.
         * This constant is equal to -1. Because size_t is unsigned it
         * will equal the maximum possible value instead.
         * It is used primarily to avoid a compiler warning when
         * comparing unsigned value (size_t) with signed.
         */
        const std::size_t ELEMENT_DOES_NOT_EXIST;
        /**
         * @brief Command line arguments passed to the program
         *
         */
        std::vector<std::string> argv;
        /**
         * @brief List of valid command line arguments
         *
         */
        std::vector<Argument> args;
        /**
         * @brief Get the index of the argument
         *
         * @param name Argument name
         * @return Index of the argument
         */
        std::size_t getArgumentIndex(const std::string& name);

    public:
        /**
         * @brief Initialize command line arguments parser
         *
         * @param argc Number of command line arguments
         * @param argv List of command line arguments
         */
        ArgParser(int argc, char* argv[]);
        /**
         * @brief Initialize command line arguments parser
         *
         * @param argc Number of command line arguments
         * @param argv List of command line arguments
         * @param args List of valid command line arguments
         */
        ArgParser(int argc, char* argv[], const std::vector<Argument>& args);
        /**
         * @brief Add a valid command line argument
         *
         * @param name Argument name
         * @param isBool Whether the argument is boolean
         * @param value Argument value
         */
        void addArgument(const std::string& name, bool isBool,
                         const std::string& value);
        /**
         * @brief Remove a valid command line argument
         *
         * @param name Argument name
         * @return true if argument existed and was removed, false otherwise
         */
        bool removeArgument(const std::string& name);
        /**
         * @brief Get the argument value
         *
         * @param name Argument name
         * @return Value of an argument if it exists, an empty string otherwise
         */
        std::string getArgumentValue(const std::string& name);
        /**
         * @brief Parse command line arguments
         *
         */
        void parse(void);
};

#endif // ARG_PARSER_H