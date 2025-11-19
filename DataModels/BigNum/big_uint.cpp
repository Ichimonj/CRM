
#include "big_uint.hpp"

#include <string>

#include "location.hpp"
#include "stdexcept"
BigUint::BigUint(const std::string& num)
{
    if (num.size() == 0) {
        throw std::invalid_argument(errors::uint_constructor_error);
    }
    for (size_t i = 0; i < num.size(); i++) {
        if (!std::isdigit(num[i])) {
            throw std::invalid_argument(errors::uint_constructor_error);
        }
    }
    this->num = num.substr(num.find_first_not_of('0'), num.back());
}

BigUint::BigUint(const BigUint& other) : num(other.num) {}

BigUint& BigUint::operator=(const BigUint& other)
{
    if (this != &other) {
        this->num = other.num;
    }
    return *this;
}

BigUint& BigUint::operator++()
{
    if (num.find_first_not_of('9') == std::string::npos) {
        std::string newNum = "1";
        newNum.insert(newNum.size(), std::string(this->num.size(), '0'));
        this->num = newNum;
        return (*this);
    }
    int i = static_cast<int>(num.size() - 1);
    while (i >= 0) {
        if (num[i] != '9') {
            // Can increment this digit without carry
            int digit = (num[i] - '0') + 1;
            num[i] = static_cast<char>(digit + '0');
            return *this;
        }
        else {
            // Set to '0' and carry over
            num[i] = '0';
            --i;
        }
    }
    return (*this);
}

bool BigUint::operator<(const BigUint& other) const
{
    if (this->num.size() < other.num.size())
        return true;
    else if (this->num.size() > other.num.size())
        return false;

    for (size_t i = this->num.size(); i >= 0; i--) {
        if (this->num[i] != other.num[i]) {
            return (int)this->num[i] - '0' < (int)other.num[i] - '0';
        }
    }
    return false;
}

bool BigUint::operator==(const BigUint& other) const { return this->num == other.num; }
bool BigUint::operator==(const char* rhs) const { return *this == std::string(rhs); }
bool BigUint::operator!=(const BigUint& other) const { return this->num != other.num; }
bool BigUint::operator!=(const char* rhs) const { return *this != std::string(rhs); }
