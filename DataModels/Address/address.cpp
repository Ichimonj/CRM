#include "address.hpp"

Address::Address(
    const std::string& country,
    const std::string& city,
    const std::string& street,
    const std::string& house,
    const std::string& apartment,
    const std::string& postal_code
)
    : country(country)
    , city(city)
    , street(street)
    , house(house)
    , apartment(apartment)
    , postal_code(postal_code)
{
}

Address::Address(const Address& address)
    : country(address.country)
    , city(address.city)
    , street(address.street)
    , house(address.house)
    , apartment(address.apartment)
    , postal_code(address.postal_code)
{
}

bool Address::operator==(const Address& other) const
{
    if (this->country != other.country) return false;
    if (this->city != other.city) return false;
    if (this->street != other.street) return false;
    if (this->apartment != other.apartment) return false;
    if (this->postal_code != other.postal_code) return false;
    return true;
}

bool Address::operator!=(const Address& other) const
{
    if (this->country != other.country) return true;
    if (this->city != other.city) return true;
    if (this->street != other.street) return true;
    if (this->apartment != other.apartment) return true;
    if (this->postal_code != other.postal_code) return true;
    return false;
}

void Address::setCountry(const std::string& country) { this->country = country; }
void Address::setCity(const std::string& city) { this->city = city; }
void Address::setStreet(const std::string& street) { this->street = street; }
void Address::setHouse(const std::string& house) { this->house = house; }
void Address::setApartment(const std::string& apartment) { this->apartment = apartment; }
void Address::setPostalCode(const std::string& postal_code) { this->postal_code = postal_code; }

const std::string& Address::getCountry() const { return this->country; }
const std::string& Address::getCity() const { return this->city; }
const std::string& Address::getStreet() const { return this->street; }
const std::string& Address::getHouse() const { return this->house; }
const std::string& Address::getApartment() const { return this->apartment; }
const std::string& Address::getPostalCode() const { return this->postal_code; }
