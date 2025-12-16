#pragma once
#include <string>

struct PhoneNumber {
    PhoneNumber(const std::string& number);
    PhoneNumber(const PhoneNumber& phone_number);

    void               setNumber(const std::string& number);
    const std::string& getNumber() const;

    bool               operator==(const PhoneNumber& other) const;
    bool               operator!=(const PhoneNumber& other) const;

private:
    uint16_t    country_code;  // 8
    uint16_t    area_code;     // 800
    uint16_t    exchange;      // 555
    uint16_t    number;        // 3535

    std::string phone_number;
};
