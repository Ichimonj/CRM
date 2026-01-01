#include "gtest/gtest.h"
#include "time_duration.hpp"

namespace unit {
    TEST(TimeDurationTest, Constructor)
    {
        // transfer sec
        TimeDuration duration1(0, 0, 0, 0, 66);
        EXPECT_EQ(duration1.getSec(), 6);
        EXPECT_EQ(duration1.getMin(), 1);

        // transfer min
        TimeDuration duration2(0, 0, 0, 66, 0);
        EXPECT_EQ(duration2.getMin(), 6);
        EXPECT_EQ(duration2.getHour(), 1);

        // transfer hour
        TimeDuration duration3(0, 0, 40, 0, 0);
        EXPECT_EQ(duration3.getDay(), 1);
        EXPECT_EQ(duration3.getHour(), 15);

        // transfer day
        TimeDuration duration4(0, 10, 0, 0, 0);
        EXPECT_EQ(duration4.getWeek(), 1);
        EXPECT_EQ(duration4.getDay(), 3);
    }
    TEST(TimeDurationTest, Addition)
    {
        TimeDuration duration1(0, 0, 0, 0, 40);
        duration1 += TimeDuration(0, 0, 0, 0, 55);
        EXPECT_EQ(duration1, TimeDuration(0, 0, 0, 1, 35));

        TimeDuration duration2(0, 0, 0, 40, 0);
        duration2 += TimeDuration(0, 0, 0, 55, 0);
        EXPECT_EQ(duration2, TimeDuration(0, 0, 1, 35, 0));

        TimeDuration duration3(0, 0, 20, 0, 0);
        duration3 += TimeDuration(0, 0, 14, 0, 0);
        EXPECT_EQ(duration3, TimeDuration(0, 1, 10, 0, 0));

        TimeDuration duration4(0, 5, 0, 0, 0);
        duration4 += TimeDuration(0, 4, 0, 0, 0);
        EXPECT_EQ(duration4, TimeDuration(1, 2, 0, 0, 0));

        TimeDuration duration5(0, 5, 12, 50, 24);
        duration5 += TimeDuration(0, 4, 20, 50, 20);
        EXPECT_EQ(duration5, TimeDuration(1, 3, 9, 40, 44));

        TimeDuration duration6(0, 0, 0, 0, 0);
        duration6 += TimeDuration(0, 0, 0, 0, 0);
        EXPECT_EQ(duration6, duration6);

        duration6 += TimeDuration(1, 11, 30, 70, 70);
        EXPECT_EQ(duration6, TimeDuration(2, 5, 6, 11, 10));
    }
    TEST(TimeDurationTest, Subtraction)
    {
        TimeDuration duration1(0, 0, 0, 1, 35);
        duration1 -= TimeDuration(0, 0, 0, 0, 55);
        EXPECT_EQ(duration1, TimeDuration(0, 0, 0, 0, 40));

        TimeDuration duration2(0, 0, 1, 35, 0);
        duration2 -= TimeDuration(0, 0, 0, 55, 0);
        EXPECT_EQ(duration2, TimeDuration(0, 0, 0, 40, 0));

        TimeDuration duration3(0, 1, 10, 0, 0);
        duration3 -= TimeDuration(0, 0, 14, 0, 0);
        EXPECT_EQ(duration3, TimeDuration(0, 0, 20, 0, 0));

        TimeDuration duration4(1, 2, 0, 0, 0);
        duration4 -= TimeDuration(0, 4, 0, 0, 0);
        EXPECT_EQ(duration4, TimeDuration(0, 5, 0, 0, 0));

        TimeDuration duration5(1, 3, 9, 40, 44);
        duration5 -= TimeDuration(0, 4, 20, 50, 20);
        EXPECT_EQ(duration5, TimeDuration(0, 5, 12, 50, 24));

        TimeDuration duration6(0, 0, 0, 0, 0);
        duration6 -= TimeDuration(0, 0, 0, 0, 0);
        EXPECT_EQ(duration6, duration6);

        duration6 = TimeDuration(2, 5, 6, 11, 10);
        duration6 -= TimeDuration(1, 11, 30, 70, 70);
        EXPECT_EQ(duration6, TimeDuration(0, 0, 0, 0, 0));
    }
}  // namespace unit