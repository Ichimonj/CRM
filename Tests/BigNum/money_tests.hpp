#include "gtest/gtest.h"
#include "money.hpp"

namespace unit {
    TEST(MoneyTest, Constructor)
    {
        std::string num1 = "1";
        std::string num2 = "1.11";
        std::string num3 = "0";
        Money       money1(num1);
        Money       money2(num2);
        Money       money3(num3);

        EXPECT_EQ(money1.num, num1 + ".00");
        EXPECT_EQ(money2.num, num2);
        EXPECT_EQ(money3.num, num3 + ".00");
    }
    TEST(MoneyTest, Less)
    {
        Money lmoney1("10.10");
        Money rmoney1("20.15");

        Money lmoney2("10");
        Money rmoney2("10");

        EXPECT_TRUE(lmoney1 < rmoney1);
        EXPECT_FALSE(rmoney1 < lmoney1);
        EXPECT_FALSE(rmoney2 < lmoney2);
    }
    TEST(MoneyTest, Addition)
    {
        Money money("10");
        money += "";
        EXPECT_EQ(money.num, "10.00");

        money += "0";
        EXPECT_EQ(money.num, "10.00");
        
        money += "15";
        EXPECT_EQ(money.num, "25.00");

        money += "0.10";
        EXPECT_EQ(money.num, "25.10");

        money += "0.90";
        EXPECT_EQ(money.num, "26.00");
    }
    TEST(MoneyTest, Subtraction)
    {
        Money money("10");
        money -= "";
        EXPECT_EQ(money.num, "10.00");

        money -= "0";
        EXPECT_EQ(money.num, "10.00");

        money -= "5";
        EXPECT_EQ(money.num, "5.00");

        money -= "0.10";
        EXPECT_EQ(money.num, "4.90");

        money -= "6.90";
        EXPECT_EQ(money.num, "0.00");
    }
}  // namespace unit