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

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <fstream>
#include <string>
#include <vector>

/**
 * @brief Class for reading from / writing to file
 *
 */
class FileHandler
{
    private:
        /**
         * @brief Input/output file stream
         *
         */
        std::fstream fileStream;

    public:
        /**
         * @brief Initialize file stream
         *
         * @param fname Filename
         * @param mode File mode
         */
        FileHandler(const std::string& fname, std::ios_base::openmode mode);
        /**
         * @brief Close the file stream
         *
         */
        ~FileHandler(void);
        /**
         * @brief Read text from file
         *
         * @return Vector with lines from file
         */
        std::vector<std::string> read(void);
        /**
         * @brief Write text to file
         *
         * @param data Text to be written
         */
        void write(const std::string& data);
        /**
         * @brief Close file stream
         *
         */
        void close(void);
};

#endif // FILE_HANDLER_H