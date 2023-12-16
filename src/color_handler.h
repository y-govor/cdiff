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

#ifndef COLOR_HANDLER_H
#define COLOR_HANDLER_H

#include <string>

// Windows-specific
#if defined(_WIN32)
#include <windows.h>
#endif // _WIN32

/**
 * @brief Colors needed for output
 *
 */
enum class Color : int
{
    Red         = 0,
    Green       = 1,
    Magenta     = 2
};

/**
 * @brief Class for handling colors for console output
 *
 */
class ColorHandler
{
    private:
        /**
         * @brief Whether to use ANSI escape codes for colors
         *
         */
        bool useAnsi;
        /**
         * @brief ANSI escape codes
         *
         */
        std::string ansiCodes[4] = {
            "\033[31m", // Red foreground
            "\033[32m", // Green foreground
            "\033[35m", // Magenta foreground
            "\033[0m"   // Reset color
        };

// Windows-specific
#if defined(_WIN32)
        /**
         * @brief Handle to the stdout
         *
         */
        HANDLE hConsole;
        /**
         * @brief Variable for storing console attributes
         *
         */
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        /**
         * @brief Windows-specific console color attributes
         *
         */
        WORD colorAttributes[3] = {
            FOREGROUND_RED,                     // Red
            FOREGROUND_GREEN,                   // Green
            FOREGROUND_RED | FOREGROUND_BLUE    // Magenta
        };
#endif // _WIN32

    public:
        /**
         * @brief Initialize colors
         *
         * @param forceAnsi Force ANSI codes on Windows
         */
        ColorHandler(bool forceAnsi);
        /**
         * @brief Restore default color on exit
         *
         */
        ~ColorHandler(void);
        /**
         * @brief Set foreground color
         *
         * @param color Color
         */
        void setColor(Color color) const;
        /**
         * @brief Reset foreground color
         *
         */
        void resetColor(void) const;
};

#endif // COLOR_HANDLER_H