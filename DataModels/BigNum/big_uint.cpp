#include "big_uint.hpp"

BigUint::BigUint(const std::string& num) : num(num) {}

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
    if (num[num.size() - 1] != '9') {
        int a = (int)num[num.size() - 1] - '0';
        a++;
        num[num.size() - 1] = (char)a + '0';
        return (*this);
        for (int i = static_cast<int>(num.size() - 2); i >= 0; i--) {
            num[i + 1] = '0';
            if (num[i] != '9') {
                int a = (int)num[i] - '0';
                a++;
                num[i] = (char)a + '0';
                break;
            }
        }
        return (*this);
    }
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
