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

#include "color_handler.h"

#include <iostream>
#include <stdexcept>

/**
 * @brief Initialize colors
 *
 * @param forceAnsi Force ANSI codes on Windows
 */
ColorHandler::ColorHandler(bool forceAnsi) : useAnsi(forceAnsi)
{
#if defined(_WIN32) // Windows
    if(useAnsi) return;

    // Retrieve a handle for stdout
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if(hConsole == INVALID_HANDLE_VALUE)
        throw std::runtime_error("could not get a handle for stdout");

    // Store current console attributes
    if(!GetConsoleScreenBufferInfo(hConsole, &csbi))
        throw std::runtime_error("could not store console attributes");
#else // POSIX
    useAnsi = true;
#endif // _WIN32
}

/**
 * @brief Restore default color on exit
 *
 */
ColorHandler::~ColorHandler(void)
{
    resetColor();
}

/**
 * @brief Set foreground color
 *
 * @param color Color
 */
void ColorHandler::setColor(Color color) const
{
    // Output ANSI escape code of the specified color
    if(useAnsi) std::cout << ansiCodes[static_cast<int>(color)];

#if defined(_WIN32) // Windows
    // Set color attributes
    SetConsoleTextAttribute(hConsole, colorAttributes[static_cast<int>(color)]);
#endif // _WIN32
}

/**
 * @brief Reset foreground color
 *
 */
void ColorHandler::resetColor(void) const
{
    // Output ANSI escape code for resetting the color
    if(useAnsi) std::cout << ansiCodes[3];

#if defined(_WIN32) // Windows
    // Set color attributes
    SetConsoleTextAttribute(hConsole, csbi.wAttributes);
#endif // _WIN32
}