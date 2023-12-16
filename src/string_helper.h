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

#ifndef STRING_HELPER_H
#define STRING_HELPER_H

#include <string>
#include <vector>

/**
 * @brief Namespace containing helper functions to work with strings
 *
 */
namespace StringHelper
{
    /**
     * @brief Check if string contains specified characters
     *
     * @param str Input string
     * @param chars String with characters
     * @return true if string contains specified characters, false otherwise
     */
    bool contains(const std::string& str, const std::string& chars);
    /**
     * @brief Check if vector contains specified string
     *
     * @param v Input vector
     * @param str String
     * @return true if vector contains specified string, false otherwise
     */
    bool isInVector(const std::vector<std::string>& v, const std::string& str);
    /**
     * @brief Convert all characters in the string to uppercase
     *
     * @param str Input string
     * @return Uppercase string
     */
    std::string toUppercase(const std::string& str);
    /**
     * @brief Get base filename from the path
     *
     * @param path Absolute or relative path to the file
     * @return Base filename
     */
    std::string getBaseFilename(const std::string& path);
    /**
     * @brief Check if string is a valid filename
     *
     * @param str Input string
     * @return true if string is a valid filename, false otherwise
     */
    bool isValidFilename(const std::string& str);
    /**
     * @brief Convert string to unsigned integer
     *
     * @param str Input string
     * @return Unsigned integer value
     */
    unsigned int str2uint(const std::string& str);
}

#endif // STRING_HELPER_H