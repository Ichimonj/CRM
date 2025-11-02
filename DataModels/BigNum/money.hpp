#pragma once
#include <string>

#include "location.hpp"

class Money {
public:
    Money(const std::string& num);

    bool        operator<(const Money& other)const;
    bool        operator==(const Money& other)const;
    bool        operator!=(const Money& other)const;

    Money&      operator+=(const std::string& other);
    Money&      operator-=(const std::string& other);

    std::string num;
};