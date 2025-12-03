#include "phone_number.hpp"

#include <stdexcept>

#include "location.hpp"

PhoneNumber::PhoneNumber(const std::string& phone_number)
{
    if (phone_number.size() < 11) {
        throw std::runtime_error(errors::phone_number_incorrect);
    }

    for (auto& ch : phone_number) {
        if (!isdigit(ch)) {
            throw std::runtime_error(errors::phone_number_incorrect);
        }
    }

    this->country_code = std::stoi(phone_number.substr(0, phone_number.size() - 10));
    this->area_code    = std::stoi(phone_number.substr(phone_number.size() - 10, 3));
    this->exchange     = std::stoi(phone_number.substr(phone_number.size() - 7, 3));
    this->number       = std::stoi(phone_number.substr(phone_number.size() - 4));
    this->phone_number = phone_number;
}

PhoneNumber::PhoneNumber(const PhoneNumber& phoneNumber)
{
    this->country_code = phoneNumber.country_code;
    this->area_code    = phoneNumber.area_code;
    this->exchange     = phoneNumber.exchange;
    this->number       = phoneNumber.number;
    this->phone_number = phoneNumber.phone_number;
}

void PhoneNumber::setNumber(const std::string& number)
{
    if (number.size() < 11) {
        throw std::runtime_error(errors::phone_number_incorrect);
    }

    for (auto& ch : number) {
        if (!isdigit(ch)) {
            throw std::runtime_error(errors::phone_number_incorrect);
        }
    }

    this->country_code = std::stoi(number.substr(0, number.size() - 10));
    this->area_code    = std::stoi(number.substr(number.size() - 10, 3));
    this->exchange     = std::stoi(number.substr(number.size() - 7, 3));
    this->number       = std::stoi(number.substr(number.size() - 4));
    this->phone_number = number;
}

const std::string& PhoneNumber::getNumber() const { return this->phone_number; }

//
bool PhoneNumber::operator==(const PhoneNumber& other) const
{
    return this->phone_number == other.phone_number;
}

bool PhoneNumber::operator!=(const PhoneNumber& other) const
{
    return this->phone_number != other.phone_number;
}
