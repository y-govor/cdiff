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

#include "diff_item.h"

/**
 * @brief Initialize parameters with specified values
 *
 * @param change Value that indicates how the line in the new file
 * was changed compared to the original file
 * @param lineOld Line in the original file where the change occured
 * @param lineNew Line in the new file where the change occured
 */
DiffItem::DiffItem(Change change, unsigned int lineOld, unsigned int lineNew) :
    change(change), lineOld(lineOld), lineNew(lineNew) { }

/**
 * @brief Get the value that indicates how the line in the new file
 * was changed compared to the original file
 *
 * @return Value that indicates how the line in the new file
 * was changed compared to the original file
 */
Change DiffItem::getChange(void) const
{
    return this->change;
}

/**
 * @brief Set the value that indicates how the line in the new file
 * was changed compared to the original file
 *
 * @param change Value that indicates how the line in the new file
 * was changed compared to the original file
 */
void DiffItem::setChange(Change change)
{
    this->change = change;
}

/**
 * @brief Get the line in the original file where the change occured
 *
 * @return Line in the original file where the change occured
 */
unsigned int DiffItem::getLineOld(void) const
{
    return this->lineOld;
}

/**
 * @brief Set the line in the original file where the change occured
 *
 * @param lineOld Line in the original file where the change occured
 */
void DiffItem::setLineOld(unsigned int lineOld)
{
    this->lineOld = lineOld;
}

/**
 * @brief Get the line in the new file where the change occured
 *
 * @return Line in the new file where the change occured
 */
unsigned int DiffItem::getLineNew(void) const
{
    return this->lineNew;
}

/**
 * @brief Set the line in the new file where the change occured
 *
 * @param lineNew Line in the new file where the change occured
 */
void DiffItem::setLineNew(unsigned int lineNew)
{
    this->lineNew = lineNew;
}