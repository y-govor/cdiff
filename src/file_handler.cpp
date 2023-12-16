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

#include "file_handler.h"

#include <stdexcept>

/**
 * @brief Initialize file stream
 *
 * @param fname Filename
 * @param mode File mode
 */
FileHandler::FileHandler(const std::string& fname, std::ios_base::openmode mode) :
    fileStream(fname, mode)
{
    if(!fileStream.is_open())
        throw std::runtime_error("could not open " + fname);
}

/**
 * @brief Close the file stream
 *
 */
FileHandler::~FileHandler(void)
{
    close();
}

/**
 * @brief Read text from file
 *
 * @return Vector with lines from file
 */
std::vector<std::string> FileHandler::read(void)
{
    std::vector<std::string> lines;
    std::string line;

    while(std::getline(fileStream, line))
        lines.push_back(line);

    return lines;
}

/**
 * @brief Write text to file
 *
 * @param data Text to be written
 */
void FileHandler::write(const std::string& data)
{
    fileStream << data;
}

/**
 * @brief Close file stream
 *
 */
void FileHandler::close(void)
{
    if(fileStream.is_open())
        fileStream.close();
}