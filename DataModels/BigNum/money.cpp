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
    this->num        = num;
    size_t point_pos = num.find_first_of('.');
    if (point_pos != std::string::npos) {
        size_t frac_size = num.size() - (point_pos + 1);
        if (frac_size == 1) {
            this->num.insert(num.size() - 1, "0");
        }
        if (frac_size > 2) {
            throw std::runtime_error(errors::invalid_currency_format);
        }
    }
    if (point_pos == std::string::npos) this->num += ".00";
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
    size_t      leftDot = this->num.find_first_of('.');
    std::string leftInteger;
    std::string leftPennyStr = "00";
    if (leftDot != std::string::npos) {
        leftInteger  = this->num.substr(0, leftDot);
        leftPennyStr = this->num.substr(leftDot + 1);
    } else {
        leftInteger = this->num;
    }
    if (leftPennyStr.size() < 2) {
        leftPennyStr += std::string(2 - leftPennyStr.size(), '0');
    } else if (leftPennyStr.size() > 2) {
        leftPennyStr = leftPennyStr.substr(0, 2);
    }
    uint8_t     leftPenny = static_cast<uint8_t>(std::stoi(leftPennyStr));

    size_t      rightDot = other.find_first_of('.');
    std::string rightInteger;
    std::string rightPennyStr = "00";
    if (rightDot != std::string::npos) {
        rightInteger  = other.substr(0, rightDot);
        rightPennyStr = other.substr(rightDot + 1);
    } else {
        rightInteger = other;
    }
    if (rightPennyStr.size() < 2) {
        rightPennyStr += std::string(2 - rightPennyStr.size(), '0');
    } else if (rightPennyStr.size() > 2) {
        rightPennyStr = rightPennyStr.substr(0, 2);
    }
    uint8_t rightPenny = static_cast<uint8_t>(std::stoi(rightPennyStr));

    int     pennySum = leftPenny + rightPenny;
    int     carry    = (pennySum >= 100) ? 1 : 0;
    pennySum %= 100;
    std::string finalPennyStr = std::to_string(pennySum);
    if (finalPennyStr.size() < 2) {
        finalPennyStr = "0" + finalPennyStr;
    }

    int         i = static_cast<int>(leftInteger.length()) - 1;
    int         j = static_cast<int>(rightInteger.length()) - 1;
    std::string result;
    int         intCarry = carry;
    while (i >= 0 || j >= 0 || intCarry != 0) {
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
        int sum = digit1 + digit2 + intCarry;
        result.push_back((sum % 10) + '0');
        intCarry = sum / 10;
    }
    std::reverse(result.begin(), result.end());

    if (result.empty()) {
        result = "0";
    }

    num = result + '.' + finalPennyStr;
    return *this;
}

Money& Money::operator-=(const std::string& other)
{
    size_t      leftDot = this->num.find_first_of('.');
    std::string leftInteger;
    std::string leftPennyStr = "00";
    if (leftDot != std::string::npos) {
        leftInteger  = this->num.substr(0, leftDot);
        leftPennyStr = this->num.substr(leftDot + 1);
    } else {
        leftInteger = this->num;
    }
    if (leftPennyStr.size() < 2) {
        leftPennyStr += std::string(2 - leftPennyStr.size(), '0');
    } else if (leftPennyStr.size() > 2) {
        leftPennyStr = leftPennyStr.substr(0, 2);
    }
    int         leftPenny = std::stoi(leftPennyStr);

    size_t      rightDot = other.find_first_of('.');
    std::string rightInteger;
    std::string rightPennyStr = "00";
    if (rightDot != std::string::npos) {
        rightInteger  = other.substr(0, rightDot);
        rightPennyStr = other.substr(rightDot + 1);
    } else {
        rightInteger = other;
    }
    if (rightPennyStr.size() < 2) {
        rightPennyStr += std::string(2 - rightPennyStr.size(), '0');
    } else if (rightPennyStr.size() > 2) {
        rightPennyStr = rightPennyStr.substr(0, 2);
    }
    int  rightPenny = std::stoi(rightPennyStr);

    bool is_negative = false;
    if (leftInteger.length() < rightInteger.length()) {
        is_negative = true;
    } else if (leftInteger.length() == rightInteger.length()) {
        if (leftInteger < rightInteger) {
            is_negative = true;
        } else if (leftInteger == rightInteger) {
            if (leftPenny < rightPenny) {
                is_negative = true;
            }
        }
    }

    if (is_negative) {
        num = "0.00";
        return *this;
    }

    int pennyResult;
    int borrow = 0;
    if (leftPenny < rightPenny) {
        pennyResult = leftPenny + 100 - rightPenny;
        borrow      = 1;
    } else {
        pennyResult = leftPenny - rightPenny;
        borrow      = 0;
    }
    std::string finalPennyStr = std::to_string(pennyResult);
    if (finalPennyStr.size() < 2) {
        finalPennyStr = "0" + finalPennyStr;
    }

    int         i = static_cast<int>(leftInteger.length()) - 1;
    int         j = static_cast<int>(rightInteger.length()) - 1;
    std::string integerResultReversed;
    int         intBorrow = borrow;
    while (i >= 0 || j >= 0 || intBorrow != 0) {
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
        int currentDiff = digit1 - digit2 - intBorrow;
        if (currentDiff < 0) {
            currentDiff += 10;
            intBorrow = 1;
        } else {
            intBorrow = 0;
        }
        integerResultReversed.push_back(currentDiff + '0');
    }
    std::reverse(integerResultReversed.begin(), integerResultReversed.end());

    std::string finalIntegerResult;
    if (integerResultReversed.empty()) {
        finalIntegerResult = "0";
    } else {
        size_t firstDigit = integerResultReversed.find_first_not_of('0');
        if (firstDigit == std::string::npos) {
            finalIntegerResult = "0";
        } else {
            finalIntegerResult = integerResultReversed.substr(firstDigit);
        }
    }

    num = finalIntegerResult + '.' + finalPennyStr;
    return *this;
}