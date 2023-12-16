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

#include "date_time.h"

#include <cmath>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>

/**
 * @brief Initialize parameters with default values
 *
 */
DateTime::DateTime(void) : year(1970), month(1), day(1),
    hour(0), minute(0), second(0), nanoseconds(0),
    offset(getTimezoneOffset()) { }

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
DateTime::DateTime(unsigned short year,
                   unsigned short month,
                   unsigned short day,
                   unsigned short hour,
                   unsigned short minute,
                   unsigned short second,
                   unsigned int nanoseconds) :
                   year(year), month(month), day(day),
                   hour(hour), minute(minute), second(second),
                   nanoseconds(nanoseconds),
                   offset(getTimezoneOffset())
{
    // Validate values
    if(!((month >= 1 && month <= 12) ||
         (day >= 1 && day <= 31) ||
         (hour <= 23) ||
         (minute <= 59) ||
         (second <= 60)
    )) throw std::invalid_argument("invalid argument");
}

/**
 * @brief Get year
 *
 * @return Year
 */
unsigned short DateTime::getYear(void)
{
    return this->year;
}

/**
 * @brief Set year
 *
 * @param year Year
 */
void DateTime::setYear(unsigned short year)
{
    this->year = year;
}

/**
 * @brief Get month
 *
 * @return Month
 */
unsigned short DateTime::getMonth(void)
{
    return this->month;
}

/**
 * @brief Set month
 *
 * @param month Month
 */
void DateTime::setMonth(unsigned short month)
{
    if(month >= 1 && month <= 12)
        this->month = month;
}

/**
 * @brief Get day
 *
 * @return Day
 */
unsigned short DateTime::getDay(void)
{
    return this->day;
}

/**
 * @brief Set day
 *
 * @param day Day
 */
void DateTime::setDay(unsigned short day)
{
    if(day >= 1 && day <= 31)
        this->day = day;
}

/**
 * @brief Get hour
 *
 * @return Hour
 */
unsigned short DateTime::getHour(void)
{
    return this->hour;
}

/**
 * @brief Set hour
 *
 * @param hour Hour
 */
void DateTime::setHour(unsigned short hour)
{
    if(hour <= 23)
        this->hour = hour;
}

/**
 * @brief Get minute
 *
 * @return Minute
 */
unsigned short DateTime::getMinute(void)
{
    return this->minute;
}

/**
 * @brief Set minute
 *
 * @param minute Minute
 */
void DateTime::setMinute(unsigned short minute)
{
    if(minute <= 59)
        this->minute = minute;
}

/**
 * @brief Get second
 *
 * @return Second
 */
unsigned short DateTime::getSecond(void)
{
    return this->second;
}

/**
 * @brief Set second
 *
 * @param second Second
 */
void DateTime::setSecond(unsigned short second)
{
    if(second <= 60)
        this->second = second;
}

/**
 * @brief Get nanoseconds
 *
 * @return Nanoseconds
 */
unsigned int DateTime::getNanoseconds(void)
{
    return this->nanoseconds;
}

/**
 * @brief Set nanoseconds
 *
 * @param nanoseconds Nanoseconds
 */
void DateTime::setNanoseconds(unsigned int nanoseconds)
{
    this->nanoseconds = nanoseconds;
}

/**
 * @brief Get UTC Offset
 *
 * @return UTC Offset
 */
long long DateTime::getOffset(void)
{
    return this->offset;
}

/**
 * @brief Set UTC offset
 *
 * @param offset UTC offset
 */
void DateTime::setOffset(long long offset)
{
    this->offset = offset;
}

/**
 * @brief Get the UTC offset of the current timezone in seconds
 *
 * @return UTC offset of the current timezone in seconds
 */
long long DateTime::getTimezoneOffset(void)
{
    // Get current calendar time since the Epoch (Jan 1 1970 00:00) in seconds
    std::time_t now = std::time(nullptr);

#ifdef _USE_32BIT_TIME_T
    long offset;
#else
    long long offset;
#endif // _USE_32BIT_TIME_T

// Use compiler-specific functions
#if defined(_MSC_VER) // Microsoft Visual C++
    std::tm nowUTC, nowLocal;

    // Convert time_t to tm structure
    gmtime_s(&nowUTC, &now);
    // Convert tm structure back to time_t to create a copy
    offset = std::mktime(&nowUTC);

    // Convert UTC time to local time
    localtime_s(&nowLocal, &now);
    // Convert local time back to time_t and calculate the difference
    offset = std::mktime(&nowLocal) - offset;
#else // GCC, MinGW, Clang and other compilers
    // Get current UTC time
    offset = std::mktime(std::gmtime(&now));
    // Get current local time and calculate the difference
    offset = std::mktime(std::localtime(&now)) - offset;
#endif // _MSC_VER

    return offset;
}

/**
 * @brief Return a formatted string with date and time in ISO 8601 format
 *
 * @return Formatted string with date and time in ISO 8601 format
 */
std::string DateTime::format(void) const
{
    std::stringstream ss;

    // Convert seconds to hours and minutes
    long long offsetHours = std::abs(offset) / 3600;
    long long offsetMinutes = (std::abs(offset) - offsetHours * 3600) * 60;

    ss << year << '-'                                           // Year
       << std::setw(2) << std::setfill('0') << month << '-'     // Month
       << std::setw(2) << std::setfill('0') << day << ' '       // Day
       << std::setw(2) << std::setfill('0') << hour << ':'      // Hour
       << std::setw(2) << std::setfill('0') << minute << ':'    // Minute
       << std::setw(2) << std::setfill('0') << second << '.'    // Second
       << nanoseconds << ' '   // Nanoseconds (POSIX) or milliseconds (Windows)
       << ((offset >= 0) ? '+' : '-')                         // Offset sign
       << std::setw(2) << std::setfill('0') << offsetHours    // Offset hours
       << std::setw(2) << std::setfill('0') << offsetMinutes; // Offset minutes

    return ss.str();
}