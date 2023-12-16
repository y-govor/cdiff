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

#include "argument.h"

#include <stdexcept>

/**
 * @brief Initialize parameters with specified values
 *
 * @param name Argument name
 * @param isBool Whether the argument is boolean
 * @param value Argument value
 */
Argument::Argument(const std::string& name, bool isBool,
                   const std::string& value) :
                   name(name), isBool(isBool), value(value) { }

/**
 * @brief Get argument name
 *
 * @return Argument name
 */
std::string Argument::getName(void) const
{
    return this->name;
}

/**
 * @brief Set argument name
 *
 * @param name Argument name
 */
void Argument::setName(const std::string& name)
{
    this->name = name;
}

/**
 * @brief Get whether the argument is boolean
 *
 * @return Whether the argument is boolean
 */
bool Argument::getIsBool(void) const
{
    return this->isBool;
}

/**
 * @brief Set whether the argument is boolean
 *
 * @param isBool Whether the argument is boolean
 */
void Argument::setIsBool(bool isBool)
{
    this->isBool = isBool;
}

/**
 * @brief Get argument value
 *
 * @return Argument value
 */
std::string Argument::getValue(void) const
{
    return this->value;
}

/**
 * @brief Set argument value
 *
 * @param value Argument value
 */
void Argument::setValue(const std::string& value)
{
    this->value = value;
}