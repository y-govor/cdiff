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

#ifndef ARGUMENT_H
#define ARGUMENT_H

#include <string>

/**
 * @brief Command line argument
 *
 */
class Argument
{
    private:
        /**
         * @brief Argument name
         *
         */
        std::string name;
        /**
         * @brief Whether the argument is boolean
         *
         */
        bool isBool;
        /**
         * @brief Argument value
         *
         */
        std::string value;

    public:
        /**
         * @brief Initialize parameters with specified values
         *
         * @param name Argument name
         * @param isBool Whether the argument is boolean
         * @param value Argument value
         */
        Argument(const std::string& name, bool isBool, const std::string& value);
        /**
         * @brief Get argument name
         *
         * @return Argument name
         */
        std::string getName(void) const;
        /**
         * @brief Set argument name
         *
         * @param name Argument name
         */
        void setName(const std::string& name);
        /**
         * @brief Get whether the argument is boolean
         *
         * @return Whether the argument is boolean
         */
        bool getIsBool(void) const;
        /**
         * @brief Set whether the argument is boolean
         *
         * @param isBool Whether the argument is boolean
         */
        void setIsBool(bool isBool);
        /**
         * @brief Get argument value
         *
         * @return Argument value
         */
        std::string getValue(void) const;
        /**
         * @brief Set argument value
         *
         * @param value Argument value
         */
        void setValue(const std::string& value);
};

#endif // ARGUMENT_H