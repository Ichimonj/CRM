#include "date.hpp"
#include "gtest/gtest.h"

namespace unit {
    TEST(DateTest, FullConstructor)
    {
        Date a(2024, 11, 20, 10, 12);
        EXPECT_EQ(a.getYear(), 2024);
        EXPECT_EQ(a.getMonth(), 11);
        EXPECT_EQ(a.getDay(), 20);
        EXPECT_EQ(a.getHour(), 10);
        EXPECT_EQ(a.getMin(), 12);
    }
    TEST(DateTest, ConstructorFebruary)
    {
        EXPECT_NO_THROW(Date(2024, 2, 29, 10, 10));
        EXPECT_NO_THROW(Date(2025, 2, 28, 10, 10));
    }
    TEST(DateTest, ConstructorThrows)
    {
        EXPECT_THROW(Date(9999, 11, 20, 10, 12), std::invalid_argument);  // big year

        // Month tests
        EXPECT_THROW(Date(2024, 13, 20, 10, 12), std::invalid_argument);
        EXPECT_THROW(Date(2024, 0, 20, 10, 12), std::invalid_argument);

        // Day tests
        EXPECT_THROW(Date(2024, 1, 32, 10, 12), std::invalid_argument);
        EXPECT_THROW(Date(2024, 2, 30, 10, 12), std::invalid_argument);
        EXPECT_THROW(Date(2025, 2, 29, 10, 12), std::invalid_argument);
        EXPECT_THROW(Date(2024, 4, 31, 10, 12), std::invalid_argument);

        // hour, min tests
        EXPECT_THROW(Date(2024, 11, 20, 24, 12), std::invalid_argument);
        EXPECT_THROW(Date(2024, 11, 20, 20, 60), std::invalid_argument);
    }

    TEST(DateTest, Subtraction)
    {
        EXPECT_EQ(Date(2024, 1, 10) - Date(2024, 1, 10), TimeDuration(0, 0, 0, 0, 0));  // 0

        EXPECT_EQ(
            Date(2024, 1, 1, 10, 20) - Date(2024, 1, 1, 10, 5), TimeDuration(0, 0, 0, 15, 0)
        );  // Min

        EXPECT_EQ(
            Date(2024, 1, 10, 20, 5) - Date(2024, 1, 10, 10, 5), TimeDuration(0, 0, 10, 0, 0)
        );  // Hour

        EXPECT_EQ(Date(2024, 1, 20) - Date(2024, 1, 10), TimeDuration(0, 10, 0, 0, 0));  // Day;

        EXPECT_EQ(Date(2025, 1, 1) - Date(2024, 1, 1), TimeDuration(52,2, 0, 0, 0)); //leap year
        EXPECT_EQ(Date(2024, 1, 1) - Date(2023, 1, 1), TimeDuration(52, 1, 0, 0, 0)); //no leap year
    }
}  // namespace unit