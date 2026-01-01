#include "big_uint.hpp"
#include "gtest/gtest.h"
#include "location.hpp"
namespace unit {
    TEST(BigUintTest, ValidConstructor)
    {
        std::string a = "1198432";
        std::string b = "999999999999999999999";
        std::string c = "000000004312";

        BigUint     uint1(a);
        BigUint     uint2(b);
        BigUint     uint3(c);

        EXPECT_EQ(uint1.num, a);
        EXPECT_EQ(uint2.num, b);
        EXPECT_EQ(uint3.num, "4312");
    }

    TEST(BigUintTest, InvalidConstructors)
    {
        EXPECT_THROW(BigUint(""), std::invalid_argument);
        EXPECT_THROW(BigUint("-321"), std::invalid_argument);
        EXPECT_THROW(BigUint("321.1"), std::invalid_argument);
        EXPECT_THROW(BigUint("321af"), std::invalid_argument);
    }
    TEST(BigUintTest, Increment)
    {
        std::string simple_val     = "1";
        std::string border_val1    = "999";
        std::string border_val2    = "1999";
        std::string big_border_val = "99999999999999";

        BigUint     uint1(simple_val);
        BigUint     uint2(border_val1);
        BigUint     uint3(border_val2);
        BigUint     uint4(big_border_val);

        EXPECT_EQ(++uint1, "2");
        EXPECT_EQ(++uint2, "1000");
        EXPECT_EQ(++uint3, "2000");
        EXPECT_EQ(++uint4, "100000000000000");
    }
    TEST(BigUintTest, Less)
    {
        BigUint lint1("10");
        BigUint rint1("100");

        BigUint lint2("10");
        BigUint rint2("20");

        BigUint lint3("20");
        BigUint rint3("10");
        EXPECT_TRUE(lint1 < rint1);
        EXPECT_TRUE(lint2 < rint2);
        EXPECT_FALSE(lint3 < rint3);
    }
}  // namespace unit