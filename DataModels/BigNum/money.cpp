#include "money.hpp"

#include <stdexcept>
#include "location.hpp"

Money::Money(const std::string& num)
{
    bool point = false;
    for (auto& ex : num) {
        if (!isdigit(ex)) {
            if (ex == '.' && point == false) {
                point = true;
            } else {
                throw std::runtime_error(errors::invalid_currency_format);
            }
        }
    }
    this->num = num;
    if (num.substr(num.find_first_of('.') + 1).size() == 1) {
        this->num.insert(num.size() - 1, "0");
    }
    if (num.substr(num.find_first_of('.') + 1).size() > 2) {
        throw std::runtime_error(errors::invalid_currency_format);
    }
}

bool Money::operator<(const Money& other) const
{
    if (this->num.size() < other.num.size()) return true;
    if (this->num.size() > other.num.size()) return false;
    for (size_t i = 0; i < num.size(); i++) {
        if (this->num[i] < other.num[i]) return true;
        if (this->num[i] > other.num[i]) return false;
    }
    return false;
}

bool   Money::operator==(const Money& other) const { return this->num == other.num; }

bool   Money::operator!=(const Money& other) const { return this->num != other.num; }

Money& Money::operator+=(const std::string& other)
{
    uint8_t leftPenny  = stoi(this->num.substr(this->num.find_first_of('.') + 1));
    uint8_t rigthPenny = stoi(other.substr(other.find_first_of('.') + 1));

    uint8_t pennySum = leftPenny + rigthPenny;

    int     carry            = pennySum > 100 ? 1 : 0;
    pennySum                 = pennySum % 100;
    std::string leftInteger  = this->num.substr(0, this->num.find_first_of('.'));
    std::string rightInteger = other.substr(0, other.find_first_of('.'));

    int         i = leftInteger.length() - 1;
    int         j = rightInteger.length() - 1;
    std::string result;

    while (i >= 0 || j >= 0 || carry != 0) {
        int digit1 = 0;
        if (i >= 0) {
            digit1 = leftInteger[i] - '0';
            i--;
        }

        int digit2 = 0;
        if (j >= 0) {
            digit2 = rightInteger[j] - '0';
            j--;
        }

        int sum = digit1 + digit2 + carry;
        result.push_back((sum % 10) + '0');
        carry = sum / 10;
    }
    std::reverse(result.begin(), result.end());
    num = result + '.' + (pennySum < 10 ? "0" : "") + std::to_string(pennySum);
    return *this;
}

Money& Money::operator-=(const std::string& other)
{
    if (*this < other) {
        this->num = "0.00";
        return *this;
    }
    uint8_t leftPenny  = std::stoi(this->num.substr(this->num.find_first_of('.') + 1));
    uint8_t rightPenny = std::stoi(other.substr(other.find_first_of('.') + 1));

    int     borrow = 0;
    int     pennyResult;

    if (leftPenny < rightPenny) {
        pennyResult = (leftPenny + 100) - rightPenny;
        borrow      = 1;
    } else {
        pennyResult = leftPenny - rightPenny;
        borrow      = 0;
    }

    std::string leftInteger  = this->num.substr(0, this->num.find_first_of('.'));
    std::string rightInteger = other.substr(0, other.find_first_of('.'));

    int         i = leftInteger.length() - 1;
    int         j = rightInteger.length() - 1;
    std::string integerResultReversed;

    while (i >= 0 || j >= 0 || borrow != 0) {
        int digit1 = 0;
        if (i >= 0) {
            digit1 = leftInteger[i] - '0';
            i--;
        }

        int digit2 = 0;
        if (j >= 0) {
            digit2 = rightInteger[j] - '0';
            j--;
        }

        int currentDiff = digit1 - digit2 - borrow;

        if (currentDiff < 0) {
            currentDiff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        integerResultReversed.push_back((currentDiff % 10) + '0');
    }

    std::reverse(integerResultReversed.begin(), integerResultReversed.end());

    std::string finalIntegerResult = integerResultReversed;
    size_t      firstDigit         = finalIntegerResult.find_first_not_of('0');
    if (std::string::npos == firstDigit) {
        finalIntegerResult = "0";
    } else {
        finalIntegerResult = finalIntegerResult.substr(firstDigit);
    }

    std::string formattedPennyResult = std::to_string(pennyResult);
    if (formattedPennyResult.length() < 2) {
        formattedPennyResult = "0" + formattedPennyResult;
    }

    this->num = finalIntegerResult + '.' + formattedPennyResult;
    return *this;
}
