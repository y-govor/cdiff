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

#ifndef DIFF_ITEM_H
#define DIFF_ITEM_H

/**
 * @brief Value that indicates how the line in the new file
 * was changed compared to the original file
 *
 */
enum class Change
{
    Equal,  // Line wasn't changed
    Remove, // Line was removed
    Insert  // Line was inserted
};

/**
 * @brief Class that represents an individual change to the original file
 *
 */
class DiffItem
{
    private:
        /**
         * @brief Value that indicates how the line in the new file
         * was changed compared to the original file
         *
         */
        Change change;
        /**
         * @brief Line in the original file where the change occured
         *
         */
        unsigned int lineOld;
        /**
         * @brief Line in the new file where the change occured
         *
         */
        unsigned int lineNew;

    public:
        /**
         * @brief Initialize parameters with specified values
         *
         * @param change Value that indicates how the line in the new file
         * was changed compared to the original file
         * @param lineOld Line in the original file where the change occured
         * @param lineNew Line in the new file where the change occured
         */
        DiffItem(Change change, unsigned int lineOld, unsigned int lineNew);
        /**
         * @brief Get the value that indicates how the line in the new file
         * was changed compared to the original file
         *
         * @return Value that indicates how the line in the new file
         * was changed compared to the original file
         */
        Change getChange(void) const;
        /**
         * @brief Set the value that indicates how the line in the new file
         * was changed compared to the original file
         *
         * @param change Value that indicates how the line in the new file
         * was changed compared to the original file
         */
        void setChange(Change change);
        /**
         * @brief Get the line in the original file where the change occured
         *
         * @return Line in the original file where the change occured
         */
        unsigned int getLineOld(void) const;
        /**
         * @brief Set the line in the original file where the change occured
         *
         * @param lineOld Line in the original file where the change occured
         */
        void setLineOld(unsigned int lineOld);
        /**
         * @brief Get the line in the new file where the change occured
         *
         * @return Line in the new file where the change occured
         */
        unsigned int getLineNew(void) const;
        /**
         * @brief Set the line in the new file where the change occured
         *
         * @param lineNew Line in the new file where the change occured
         */
        void setLineNew(unsigned int lineNew);
};

#endif // DIFF_ITEM_H