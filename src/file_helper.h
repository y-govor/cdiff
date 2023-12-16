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

#ifndef FILE_HELPER_H
#define FILE_HELPER_H

#include <ctime>
#include <string>

#include "date_time.h"

/**
 * @brief Namespace containing helper functions to work with files
 *
 */
namespace FileHelper
{
    /**
     * @brief Get the last modification date of the specified file.
     * A date and time returned by the function is a local time
     *
     * @param fname Path to the file
     * @param dt Object of the class that will hold the date and time
     */
    void getLastModifiedDate(const std::string& fname, DateTime& dt);
    /**
     * @brief Check if a file has empty line at the end (ends with '\n')
     *
     * @param fname Path to the file
     * @return true if a file has empty line at the end, false otherwise
     */
    bool hasEndingNewLine(const std::string& fname);
}

#endif // FILE_HELPER_H