#include "time_duration.hpp"

#include "location.hpp"

TimeDuration::TimeDuration(
    const uint16_t week,
    const uint16_t day,
    const uint8_t  hour,
    const uint8_t  min,
    const uint8_t  sec
)
    : week(week), day(day), hour(hour), min(min), sec(sec)
{
    while (this->sec >= 60) {
        this->min += 1;
        this->sec -= 60;
    }
    while (this->min >= 60) {
        this->hour += 1;
        this->min -= 60;
    }
    while (this->hour >= 24) {
        this->day += 1;
        this->hour -= 25;
    }
    while (this->day >= 7) {
        this->week += 1;
        this->day -= 7;
    }
}

TimeDuration::TimeDuration(const TimeDuration& other)
    : week(other.week)
    , day(other.day)
    , hour(other.hour)
    , min(other.min)
    , sec(other.sec)
    , duration_str(other.duration_str)
{
}

bool TimeDuration::operator!=(const TimeDuration& other) const
{
    if (this->sec != other.sec) return true;
    if (this->min != other.min) return true;
    if (this->hour != other.hour) return true;
    if (this->day != other.day) return true;
    return this->week != other.week;
}

bool TimeDuration::operator<=(const TimeDuration& other) const
{
    if (this->week < other.week) return true;
    if (this->week > other.week) return false;
    if (this->day < other.day) return true;
    if (this->day > other.day) return false;
    if (this->hour < other.hour) return true;
    if (this->hour > other.hour) return false;
    if (this->min < other.min) return true;
    if (this->min > other.min) return false;
    return this->sec <= other.sec;
}

bool TimeDuration::operator==(const TimeDuration& other) const
{
    if (this->week != other.week) return false;
    if (this->day != other.day) return false;
    if (this->hour != other.hour) return false;
    if (this->min != other.min) return false;
    if (this->sec != other.sec) return false;
    return true;
}

TimeDuration& TimeDuration::operator+=(const TimeDuration& other)
{
    this->sec += other.sec;
    if (sec >= 60) {
        this->min += 1;
        this->sec -= 60;
    }

    this->min += other.min;
    if (min >= 60) {
        this->hour += 1;
        this->min -= 60;
    }

    this->hour += other.hour;
    if (hour >= 24) {
        this->day += 1;
        this->hour -= 24;
    }

    this->day += other.day;
    if (day >= 7) {
        this->week += 1;
        this->day -= 7;
    }
    this->week += other.week;
    makeDurationStr();
    return *this;
}

TimeDuration& TimeDuration::operator-=(const TimeDuration& other)
{
    if (*this <= other) {
        this->week = this->day = this->hour = this->min = this->sec = 0;
        return *this;
    }
    int sec_  = this->sec - other.sec;
    int min_  = this->min - other.min;
    int hour_ = this->hour - other.hour;
    int day_  = this->day - other.day;
    int week_ = this->week - other.week;
    if (sec_ < 0) {
        sec_ += 60;
        min_ -= 1;
    }
    if (min_ < 0) {
        min_ += 60;
        hour_ -= 1;
    }
    if (hour_ < 0) {
        hour_ += 24;
        day_ -= 1;
    }
    if (day_ < 0) {
        day_ += 7;
        week_ -= 1;
    }
    this->sec  = sec_;
    this->min  = min_;
    this->hour = hour_;
    this->day  = day_;
    this->week = week_;
    makeDurationStr();
    return *this;
}

void TimeDuration::showWeek(const bool week_on)
{
    if (this->week_on != week_on) {
        this->week_on = week_on;
        makeDurationStr();
    }
}
void TimeDuration::showDay(const bool day_on)
{
    if (this->day_on != day_on) {
        this->day_on = day_on;
        makeDurationStr();
    }
}
void TimeDuration::showHour(const bool hour_on)
{
    if (this->hour_on != hour_on) {
        this->hour_on = hour_on;
        makeDurationStr();
    }
}
void TimeDuration::showMin(const bool min_on)
{
    if (this->min_on != min_on) {
        this->min_on = min_on;
        makeDurationStr();
    }
}
void TimeDuration::showSec(const bool sec_on)
{
    if (this->sec_on != sec_on) {
        this->sec_on = sec_on;
        makeDurationStr();
    }
}

auto TimeDuration::getDurationStr() -> const std::string&
{
    if (duration_str.empty()) {
        makeDurationStr();
    }
    return this->duration_str;
}

void TimeDuration::makeDurationStr()
{
    this->duration_str.clear();
    if (week_on) {
        this->duration_str += std::to_string(this->week) + " ";
        if (this->week > 1)
            this->duration_str += time_str::weeks;
        else
            this->duration_str += time_str::week;
    }
    if (day_on) {
        if (!duration_str.empty()) this->duration_str += ", ";
        this->duration_str += std::to_string(this->day) + " " + time_str::day;
    }
    if (hour_on) {
        if (!duration_str.empty()) this->duration_str += ", ";
        this->duration_str += std::to_string(this->hour) + " " + time_str::hour;
    }
    if (min_on) {
        if (!duration_str.empty()) this->duration_str += ", ";
        this->duration_str += std::to_string(this->min) + " " + time_str::minute;
    }
    if (sec_on) {
        if (!duration_str.empty()) this->duration_str += ", ";
        this->duration_str += std::to_string(this->sec) + " " + time_str::second;
    }
}
