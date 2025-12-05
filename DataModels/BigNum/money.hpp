#pragma once
#include <string>
#include <variant>

#include "currencies.hpp"
class Money {
public:
    Money(const std::string& num, const Currencies currency = ÑountriesCurrencies::USD);

    bool        operator<(const Money& other) const;
    bool        operator==(const Money& other) const;
    bool        operator!=(const Money& other) const;

    Money&      operator+=(const std::string& other);
    Money&      operator-=(const std::string& other);

    std::string num;
    Currencies  currency;
};