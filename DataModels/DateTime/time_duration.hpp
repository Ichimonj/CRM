#pragma once
#include <stdint.h>

#include <string>
class TimeDuration {
public:
    TimeDuration() = default;
    TimeDuration(
        const uint16_t week,
        const uint16_t day,
        const uint8_t  hour,
        const uint8_t  min,
        const uint8_t  sec
    );
    TimeDuration(const TimeDuration& other);

    bool          operator!=(const TimeDuration& other) const;
    bool          operator<=(const TimeDuration& other) const;
    bool          operator==(const TimeDuration& other) const;
    TimeDuration& operator+=(const TimeDuration& other);
    TimeDuration& operator-=(const TimeDuration& other);

    uint16_t      getWeek() const;
    uint8_t       getDay() const;
    uint8_t       getHour() const;
    uint8_t       getMin() const;
    uint8_t       getSec() const;

    void          showWeek(const bool week_on);
    void          showDay(const bool day_on);
    void          showHour(const bool hour_on);
    void          showMin(const bool min_on);
    void          showSec(const bool sec_on);

    auto          getDurationStr() -> const std::string&;

private:
    bool        week_on = true;
    bool        day_on  = true;
    bool        hour_on = true;
    bool        min_on  = true;
    bool        sec_on  = true;

    uint16_t    week = 0;
    uint8_t     day  = 0;
    uint8_t     hour = 0;
    uint8_t     min  = 0;
    uint8_t     sec  = 0;

    std::string duration_str;
    void        makeDurationStr();
};