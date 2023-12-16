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

#include "file_helper.h"

#include <fstream>

#if defined(_WIN32) // Windows
#include <windows.h>
#else // POSIX
#include <sys/stat.h>
#endif // _WIN32

/**
 * @brief Get the last modification date of the specified file.
 * A date and time returned by the function is a local time
 *
 * @param fname Path to the file
 * @param dt Object of the class that will hold the date and time
 */
void FileHelper::getLastModifiedDate(const std::string& fname, DateTime& dt)
{
#if defined(_WIN32) // Windows
    // Get the handle to the file
    HANDLE hFile = CreateFileA(fname.c_str(), GENERIC_READ, 0, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if(hFile == INVALID_HANDLE_VALUE)
        throw std::runtime_error("could not get a handle for the file");

    FILETIME ft;
    SYSTEMTIME stUTC, stLocal;

    // Get last modification date of the file
    if(!GetFileTime(hFile, NULL, NULL, &ft))
        throw std::runtime_error("could not get last modification date of the file");

    CloseHandle(hFile);

    // Convert FILETIME to SYSTEMTIME
    if(!FileTimeToSystemTime(&ft, &stUTC))
        throw std::runtime_error("could not convert time to appropriate format");

    // Convert UTC time to the local time
    if(!SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal))
        throw std::runtime_error("could not convert time to appropriate format");

    // Pass values to the DateTime class
    dt.setYear(stLocal.wYear);
    dt.setMonth(stLocal.wMonth);
    dt.setDay(stLocal.wDay);
    dt.setHour(stLocal.wHour);
    dt.setMinute(stLocal.wMinute);
    dt.setSecond(stLocal.wSecond);
    dt.setNanoseconds(stLocal.wMilliseconds); // Program will store
                                              // milliseconds instead of
                                              // nanoseconds for Windows
#else // POSIX
    struct stat attr;

    // Get file attributes
    if(stat(fname.c_str(), &attr))
        throw std::runtime_error("could not get last modification date of the file");

    // Convert to local time
    std::tm* t = std::localtime(&attr.st_mtim.tv_sec);

    if(t == nullptr)
        throw std::runtime_error("could not convert time to appropriate format");

    // Pass values to the DateTime class
    dt.setYear(t->tm_year + 1900); // tm_year keeps track of years since 1900
    dt.setMonth(t->tm_mon + 1); // tm_mon has a valid range of 0-11
    dt.setDay(t->tm_mday);
    dt.setHour(t->tm_hour);
    dt.setMinute(t->tm_min);
    dt.setSecond(t->tm_sec);
    dt.setNanoseconds(attr.st_mtim.tv_nsec);
#endif // _WIN32
}

/**
 * @brief Check if a file has empty line at the end (ends with '\n')
 *
 * @param fname Path to the file
 * @return true if a file has empty line at the end, false otherwise
 */
bool FileHelper::hasEndingNewLine(const std::string &fname)
{
    char c;

    // Open the file
    std::ifstream file(fname);

    // Check if file is open
    if(!file.is_open())
        throw std::ios_base::failure("failed to open a file");

    // Jump to the one position before EOF
    file.seekg(-1, std::ios_base::end);

    // Get last character
    file.get(c);

    // Check for new line
    return c == '\n';
}