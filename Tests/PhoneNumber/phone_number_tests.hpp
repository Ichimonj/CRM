#include "gtest/gtest.h"
#include "phone_number.hpp"

namespace unit {
    TEST(PhoneNumberTest, Constructor) {
        std::string number = "88005553535";
        PhoneNumber phone_number(number);
        EXPECT_EQ(phone_number.getNumber(), number);
    }
    TEST(PhoneNumberTest, ConstructorThrows)
    {
        EXPECT_THROW(PhoneNumber("1"), std::runtime_error);
        EXPECT_THROW(PhoneNumber("88a0/5/3535"), std::runtime_error);
    }
    TEST(PhoneNumberTest, Equal) {
        PhoneNumber base_phone_number("88005553535");
        PhoneNumber phone_number("88005553535");

        EXPECT_TRUE(base_phone_number == phone_number);
    }
    TEST(PhoneNumberTest, NotEqual) {
        PhoneNumber base_phone_number("88005553535");
        PhoneNumber phone_number("88115553535");

        EXPECT_TRUE(base_phone_number != phone_number);
    }
}  // namespace unit