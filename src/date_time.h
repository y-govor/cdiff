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

#ifndef DATE_TIME_H
#define DATE_TIME_H

#include <string>

/**
 * @brief Class representing date and time
 *
 */
class DateTime
{
    private:
        /**
         * @brief Year
         */
        unsigned short year;
        /**
         * @brief Month
         */
        unsigned short month;
        /**
         * @brief Day
         */
        unsigned short day;
        /**
         * @brief Hour
         */
        unsigned short hour;
        /**
         * @brief Minute
         */
        unsigned short minute;
        /**
         * @brief Second
         */
        unsigned short second;
        /**
         * @brief Nanoseconds
         */
        unsigned int nanoseconds;
        /**
         * @brief UTC offset
         */
        long long offset;

    public:
        /**
         * @brief Initialize parameters with default values
         *
         */
        DateTime(void);
        /**
         * @brief Initialize parameters with specified values
         *
         * @param year Year
         * @param month Month
         * @param day Day
         * @param hour Hour
         * @param minute Minute
         * @param second Second
         * @param nanoseconds Nanoseconds
         */
        DateTime(unsigned short year,
                 unsigned short month,
                 unsigned short day,
                 unsigned short hour,
                 unsigned short minute,
                 unsigned short second,
                 unsigned int nanoseconds);
        /**
         * @brief Get year
         *
         * @return Year
         */
        unsigned short getYear(void);
        /**
         * @brief Set year
         *
         * @param year Year
         */
        void setYear(unsigned short year);
        /**
         * @brief Get month
         *
         * @return Month
         */
        unsigned short getMonth(void);
        /**
         * @brief Set month
         *
         * @param month Month
         */
        void setMonth(unsigned short month);
        /**
         * @brief Get day
         *
         * @return Day
         */
        unsigned short getDay(void);
        /**
         * @brief Set day
         *
         * @param day Day
         */
        void setDay(unsigned short day);
        /**
         * @brief Get hour
         *
         * @return Hour
         */
        unsigned short getHour(void);
        /**
         * @brief Set hour
         *
         * @param hour Hour
         */
        void setHour(unsigned short hour);
        /**
         * @brief Get minute
         *
         * @return Minute
         */
        unsigned short getMinute(void);
        /**
         * @brief Set minute
         *
         * @param minute Minute
         */
        void setMinute(unsigned short minute);
        /**
         * @brief Get second
         *
         * @return Second
         */
        unsigned short getSecond(void);
        /**
         * @brief Set second
         *
         * @param second Second
         */
        void setSecond(unsigned short second);
        /**
         * @brief Get nanoseconds
         *
         * @return Nanoseconds
         */
        unsigned int getNanoseconds(void);
        /**
         * @brief Set nanoseconds
         *
         * @param nanoseconds Nanoseconds
         */
        void setNanoseconds(unsigned int nanoseconds);
        /**
         * @brief Get UTC Offset
         *
         * @return UTC Offset
         */
        long long getOffset(void);
        /**
         * @brief Set UTC offset
         *
         * @param offset UTC offset
         */
        void setOffset(long long offset);
        /**
         * @brief Get the UTC offset of the current timezone in seconds
         *
         * @return UTC offset of the current timezone in seconds
         */
        static long long getTimezoneOffset(void);
        /**
         * @brief Return a formatted string with date and time in ISO 8601 format
         *
         * @return Formatted string with date and time in ISO 8601 format
         */
        std::string format(void) const;
};

#endif // DATE_TIME_H