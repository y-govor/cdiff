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

#include <exception>
#include <iostream>
#include <vector>

#include "app_controller.h"
#include "argument.h"

int main(int argc, char* argv[])
{
    // List of valid arguments
    std::vector<Argument> args = {
        //       Name               Boolean     Default value
        Argument("-h",              true,       "false"),
        Argument("--help",          true,       "false"),
        Argument("-c",              true,       "false"),
        Argument("--color",         true,       "false"),
        Argument("-a",              true,       "false"),
        Argument("--force-ansi",    true,       "false"),
        Argument("-o",              false,      ""),
        Argument("--out-file",      false,      ""),
        Argument("-n",              false,      "3"),
        Argument("--lines",         false,      "3")
    };

    // Initialize application controller
    AppController controller(argc, argv, args);

    try
    {
        // Parse command line arguments
        if(!controller.parseArguments())
        {
            // Close application if help was displayed
            return 0;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n'
                  << "Use \'cdiff -h\' or  \'cdiff --help\' "
                  << "for more information\n";
        return 1;
    }

    try
    {
        // Read contents of the files
        controller.readFileContents();
        // Calculate and output the difference between files
        controller.calculateDiff();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}