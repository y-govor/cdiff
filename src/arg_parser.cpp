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

#include "arg_parser.h"

#include <iterator>
#include <stdexcept>

/**
 * @brief Initialize command line arguments parser
 *
 * @param argc Number of command line arguments
 * @param argv List of command line arguments
 */
ArgParser::ArgParser(int argc, char* argv[]) :
    ELEMENT_DOES_NOT_EXIST(-1),
    argv(argv + 1, argv + argc) { } // Convert an array of C strings (char*)
                                    // to string vector

/**
 * @brief Initialize command line arguments parser
 *
 * @param argc Number of command line arguments
 * @param argv List of command line arguments
 * @param args List of valid command line arguments
 */
ArgParser::ArgParser(int argc, char* argv[],
                     const std::vector<Argument>& args) :
                     ELEMENT_DOES_NOT_EXIST(-1),
                     argv(argv + 1, argv + argc),
                     args(args) { }

/**
 * @brief Add a valid command line argument
 *
 * @param name Argument name
 * @param isBool Whether the argument is boolean
 * @param value Argument value
 */
void ArgParser::addArgument(const std::string& name, bool isBool,
                            const std::string& value)
{
    args.push_back(Argument(name, isBool, value));
}

/**
 * @brief Remove a valid command line argument
 *
 * @param name Argument name
 * @return true if argument existed and was removed, false otherwise
 */
bool ArgParser::removeArgument(const std::string& name)
{
    // Get the index of the argument
    std::size_t index = getArgumentIndex(name);

    if(index == ELEMENT_DOES_NOT_EXIST) return false;

    // Create an iterator for the vector with valid arguments
    std::vector<Argument>::iterator it = args.begin();
    // Move iterator to the specified index
    if(index > 0) std::advance(it, index);
    // Remove element at the current position
    args.erase(it);

    return true;
}

/**
 * @brief Get the index of the argument
 *
 * @param name Argument name
 * @return Index of the argument
 */
std::size_t ArgParser::getArgumentIndex(const std::string& name)
{
    std::size_t i;
    std::size_t n = args.size();

    for(i = 0; i < n; i++)
    {
        if(args[i].getName() == name)
            return i;
    }

    return ELEMENT_DOES_NOT_EXIST;
}

/**
 * @brief Get the argument value
 *
 * @param name Argument name
 * @return Value of an argument if it exists, an empty string otherwise
 */
std::string ArgParser::getArgumentValue(const std::string &name)
{
    // Get the index of the argument
    std::size_t index = getArgumentIndex(name);

    // Return an empty string if an argument
    // with the specified name does not exist
    if(index == ELEMENT_DOES_NOT_EXIST) return std::string();

    return args[index].getValue();
}

/**
 * @brief Parse command line arguments
 *
 */
void ArgParser::parse(void)
{
    const std::size_t argvCount = argv.size();
    const char delim = '=';
    std::size_t index, pos;

    // If the first argument is '-h' or '--help'
    if(argvCount > 0 && (argv[0] == "-h" || argv[0] == "--help"))
    {
        // Set the value to true
        args[getArgumentIndex(argv[0])].setValue("true");
        // Ignore other arguments and quit
        return;
    }

    // Program requires at least 2 arguments if neither
    // '-h' nor '--help' is the first argument
    if(argvCount < 2)
        throw std::invalid_argument("missing required arguments");

    // Check up to 2 last arguments
    for(std::size_t i = 0; i < argvCount - 2; i++)
    {
        // Check if an argument is valid
        index = getArgumentIndex(argv[i]);

        if(index != ELEMENT_DOES_NOT_EXIST) // String matched argument name
        {
            if(args[index].getIsBool()) // Boolean argument
            {
                args[index].setValue("true");
            }
            else // Non-boolean argument
            {
                // Check the next argument for value
                if((i + 1 < argvCount - 2) &&
                   getArgumentIndex(argv[i + 1]) == ELEMENT_DOES_NOT_EXIST)
                    args[index].setValue(argv[i + 1]);
                else
                    throw std::invalid_argument("invalid arguments");

                // Skip the next argument
                i++;
            }
        }
        else // String did not match argument name
        {
            // Find a delimiter in the string
            pos = argv[i].find(delim);

            // Delimiter was not found, argument is invalid
            if(pos == std::string::npos)
                throw std::invalid_argument("invalid arguments");

            // Check if a substring is a valid argument
            index = getArgumentIndex(argv[i].substr(0, pos));

            if(index == ELEMENT_DOES_NOT_EXIST)
                throw std::invalid_argument("invalid arguments");

            // Extract value
            args[index].setValue(argv[i].substr(pos + 1));
        }
    }
}