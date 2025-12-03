#include "date.hpp"

#include <stdio.h>

#include <ctime>
#include <stdexcept>

#include "location.hpp"
#include "stdexcept"

Date::Date()
{
    std::time_t t = std::time(nullptr);
    std::tm     now;

#ifdef _MSC_VER
    localtime_s(&now, &t);  // Windows
#else
    now = *std::localtime(&t);  // Non-Windows
#endif

    this->d_year  = now.tm_year + 1900;
    this->d_month = now.tm_mon;
    this->d_day   = now.tm_mday;
    this->d_hour  = now.tm_hour;
    this->d_min   = now.tm_min;
}

Date::Date(
    const uint16_t year,
    const uint8_t  month,
    const uint8_t  day,
    const uint8_t  hour,
    const uint8_t  min
)
{
    if (year > 3000) throw std::invalid_argument(errors::year_incorrect);

    if (month < 1 || month > 12) throw std::invalid_argument(errors::month_incorrect);

    if (month == 2) {         // February
        if (year % 4 == 0) {  // Intercalary year
            if (day > 29) throw std::invalid_argument(errors::day_incorrect);
        } else {
            if (day > 28) throw std::invalid_argument(errors::day_incorrect);
        }
    } else {
        if (day > numberDaysInMonth(month)) throw std::invalid_argument(errors::day_incorrect);
    }

    if (hour > 23) throw std::invalid_argument(errors::hour_incorrect);

    if (min > 59) throw std::invalid_argument(errors::min_incorrect);

    this->d_year  = year;
    this->d_month = month;
    this->d_day   = day;
    this->d_hour  = hour;
    this->d_min   = min;
}

Date::Date(const Date& ex)
    : d_year(ex.d_year), d_month(ex.d_month), d_day(ex.d_day), d_hour(ex.d_hour), d_min(ex.d_min)
{
}

TimeDuration Date::operator-(const Date& other) const
{
    if (*this < other) throw std::runtime_error(errors::negative_date_range);
    int min, hour, day, month, year;
    min = hour = day = month = year = 0;

    min += this->d_min - other.d_min;
    if (min < 0) {
        min += 60;
        hour -= 1;
    }

    hour += this->d_hour - other.d_hour;
    if (hour < 0) {
        hour += 24;
        day -= 1;
    }

    day += this->julian_day() - other.julian_day();
    return TimeDuration(0, day, hour, min, 0);
}

Date& Date::operator=(const Date& other)
{
    if (this == &other) return *this;

    this->d_year  = other.d_year;
    this->d_month = other.d_month;
    this->d_day   = other.d_day;
    this->d_hour  = other.d_hour;
    this->d_min   = other.d_min;
    return *this;
}

bool Date::operator<(const Date& other) const
{
    if (this->d_year != other.d_year) return this->d_year < other.d_year;
    if (this->d_month != other.d_month) return this->d_month < other.d_month;
    if (this->d_day != other.d_day) return this->d_day < other.d_day;
    if (this->d_hour != other.d_hour) return this->d_hour < other.d_hour;
    return this->d_min < other.d_min;
}

bool Date::operator!=(const Date& other) const
{
    if (this->d_year != other.d_year) return true;
    if (this->d_month != other.d_month) return true;
    if (this->d_day != other.d_day) return true;
    if (this->d_hour != other.d_hour) return true;
    if (this->d_min != other.d_min) return true;
    return false;
}

bool Date::operator==(const Date& other) const
{
    if (this->d_year != other.d_year) return false;
    if (this->d_month != other.d_month) return false;
    if (this->d_day != other.d_day) return false;
    if (this->d_hour != other.d_hour) return false;
    if (this->d_min != other.d_min) return false;
    return true;
}

auto Date::julian_day() const -> const uint64_t
{
    int y = d_year, m = d_month, d = d_day;
    if (m <= 2) {
        y--;
        m += 12;
    }  // Jan/Feb as 13/14 of prev year
    int a = y / 100;
    int b = 2 - a + a / 4;
    return int(365.25 * (y + 4716)) + int(30.6001 * (m + 1)) + d + b - 1524;
}

const std::string Date::getDateStr() const
{
    return std::string(
        std::to_string(this->d_day) + ' ' + this->monthToStr() + ' ' +
        std::to_string(this->d_year) + ' ' + std::to_string(this->d_hour) + ':' +
        std::to_string(this->d_min)
    );
}

const uint16_t    Date::getYear() const { return this->d_year; }
const uint8_t     Date::getMonth() const { return this->d_month; }
const uint8_t     Date::getDay() const { return this->d_day; }
const uint8_t     Date::getHour() const { return this->d_hour; }
const uint8_t     Date::getMin() const { return this->d_min; }

const std::string Date::toJsonFormat() const
{
    char buffer[20];
    snprintf(
        buffer, sizeof(buffer), "%04d-%02d-%02dT%02d:%02d:00", d_year, d_month, d_day, d_hour, d_min
    );
    return buffer;
}

const uint8_t Date::numberDaysInMonth(const uint8_t month) const
{
    switch (month) {
        case 1:   // January
        case 3:   // March
        case 5:   // May
        case 7:   // July
        case 8:   // August
        case 10:  // October
        case 12:  // December
            return 31;
        case 4:   // April
        case 6:   // June
        case 9:   // September
        case 11:  // November
            return 30;
        case 2:         // February
            return 28;  // Actual validation happens in constructor
        default:
            return 0;  // Invalid month
    }
}

const std::string Date::monthToStr() const
{
    switch (this->d_month) {
        case 1:
            return month_str::january;
            break;
        case 2:
            return month_str::february;
            break;
        case 3:
            return month_str::march;
            break;
        case 4:
            return month_str::april;
            break;
        case 5:
            return month_str::may;
            break;
        case 6:
            return month_str::june;
            break;
        case 7:
            return month_str::july;
            break;
        case 8:
            return month_str::august;
            break;
        case 9:
            return month_str::september;
            break;
        case 10:
            return month_str::october;
            break;
        case 11:
            return month_str::november;
            break;
        case 12:
            return month_str::december;
            break;
        default:
            return "NULL";
            break;
    }
}