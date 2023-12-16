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

#include "string_helper.h"

#include <algorithm>
#include <climits>
#include <stdexcept>

/**
 * @brief Check if string contains specified characters
 *
 * @param str Input string
 * @param chars String with characters
 * @return true if string contains specified characters, false otherwise
 */
bool StringHelper::contains(const std::string& str, const std::string& chars)
{
    return str.find_first_of(chars) != std::string::npos;
}

/**
 * @brief Check if vector contains specified string
 *
 * @param v Input vector
 * @param str String
 * @return true if vector contains specified string, false otherwise
 */
bool StringHelper::isInVector(const std::vector<std::string>& v, const std::string& str)
{
    return std::find(v.begin(), v.end(), str) != v.end();
}

/**
 * @brief Convert all characters in the string to uppercase
 *
 * @param str Input string
 * @return Uppercase string
 */
std::string StringHelper::toUppercase(const std::string& str)
{
    std::string newStr = str;
    std::transform(newStr.begin(), newStr.end(), newStr.begin(),
        [](unsigned char c) { return std::toupper(c); });
    return newStr;
}

/**
 * @brief Get base filename from the path
 *
 * @param path Absolute or relative path to the file
 * @return Base filename
 */
std::string StringHelper::getBaseFilename(const std::string& path)
{
    return path.substr(path.find_last_of("/\\") + 1);
}

/**
 * @brief Check if string is a valid filename
 *
 * @param str Input string
 * @return true if string is a valid filename, false otherwise
 */
bool StringHelper::isValidFilename(const std::string& str)
{
    // Maximum length for file path in older versions of Windows
    const std::size_t maxLen = 255;
    // Invalid characters for filename in Windows
    const std::string invalidChars = "\\/:*?\"<>|";
    // Reserved names in Windows
    std::vector<std::string> reservedNames = {"CON", "PRN", "AUX", "NUL",
        "COM1", "COM2", "COM3", "LPT1", "LPT2", "LPT3"};

    // Get the base filename
    const std::string baseName = getBaseFilename(str);

    return !(
        baseName.empty() ||
        (baseName.length() > maxLen) ||
        contains(baseName, invalidChars) ||
        isInVector(reservedNames, toUppercase(baseName))
    );
}

/**
 * @brief Convert string to unsigned integer
 *
 * @param str Input string
 * @return Unsigned integer value
 */
unsigned int StringHelper::str2uint(const std::string& str)
{
    const long long l = std::stoll(str);

    if(l >= 0 && l <= UINT_MAX)
        return (unsigned int)l;
    else
        throw std::range_error("value is out of acceptable range");
}