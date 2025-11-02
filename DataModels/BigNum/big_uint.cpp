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

bool operator<(const BigUint& uuidL, const BigUint& uuidR)
{
    if (uuidL.num.size() < uuidR.num.size())
        return true;
    else if (uuidL.num.size() > uuidR.num.size())
        return false;

    for (size_t i = uuidL.num.size(); i >= 0; i--) {
        if (uuidL.num[i] != uuidR.num[i]) {
            return (int)uuidL.num[i] - '0' < (int)uuidR.num[i] - '0';
        }
    }
    return false;
}

bool operator==(const BigUint& uuidL, const BigUint& uuidR) { return uuidL.num == uuidR.num; }
