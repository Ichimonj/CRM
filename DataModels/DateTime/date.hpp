#pragma once
#include <string>

#include "time_duration.hpp"
struct Date {
    Date();
    Date(
        const uint16_t year,
        const uint8_t  month,
        const uint8_t  day,
        const uint8_t  hour = 0,
        const uint8_t  min  = 0
    );
    Date(const Date& ex);

    TimeDuration operator-(const Date& other) const;
    Date&        operator=(const Date& other);
    bool         operator!=(const Date& other) const;
    bool         operator==(const Date& other) const;

public:
    auto julian_day() const -> const uint64_t;
    auto getDateStr() const -> const std::string;
    auto getYear() const -> const uint16_t;
    auto getMonth() const -> const uint8_t;
    auto getDay() const -> const uint8_t;
    auto getHour() const -> const uint8_t;
    auto getMin() const -> const uint8_t;

public:
    const std::string toJsonFormat() const;

private:
    const uint8_t     numberDaysInMonth(const uint8_t month) const;
    const std::string monthToStr() const;

    uint16_t          d_year;
    uint8_t           d_month;
    uint8_t           d_day;

    uint8_t           d_hour;
    uint8_t           d_min;
};