#include "address.hpp"

Address::Address(
    const std::string& country,
    const std::string& city,
    const std::string& street,
    const std::string& house_number,
    const std::string& apartment,
    const std::string& postal_code
)
    : country(country)
    , city(city)
    , street(street)
    , house_number(house_number)
    , apartment(apartment)
    , postal_code(postal_code)
    , is_validated(false)
{
}

Address::Address(const Address& address)
    : country(address.country)
    , country_code(address.country_code)
    , region(address.region)
    , region_code(address.region_code)
    , city(address.city)
    , district(address.district)
    , dependent_locality(address.dependent_locality)
    , street(address.street)
    , house_number(address.house_number)
    , building(address.building)
    , apartment(address.apartment)
    , floor(address.floor)
    , entrance(address.entrance)
    , postal_code(address.postal_code)
    , po_box(address.po_box)
    , landmark(address.landmark)
    , directions(address.directions)
    , formatted_address(address.formatted_address)
    , latitude(address.latitude)
    , longitude(address.longitude)
    , altitude(address.altitude)
    , is_validated(address.is_validated)
    , standard_format(address.standard_format)
{
}

bool Address::operator==(const Address& other) const
{
    return country == other.country && country_code == other.country_code &&
           region == other.region && region_code == other.region_code && city == other.city &&
           district == other.district && dependent_locality == other.dependent_locality &&
           street == other.street && house_number == other.house_number &&
           building == other.building && apartment == other.apartment && floor == other.floor &&
           entrance == other.entrance && postal_code == other.postal_code &&
           po_box == other.po_box && landmark == other.landmark && directions == other.directions &&
           formatted_address == other.formatted_address &&
           standard_format == other.standard_format && latitude == other.latitude &&
           longitude == other.longitude && altitude == other.altitude &&
           is_validated == other.is_validated;
}

bool Address::operator!=(const Address& other) const
{
    return !(*this == other);
}

auto Address::getCountry() const -> const std::string& { return country; }
auto Address::getCountryCode() const -> const std::string& { return country_code; }
auto Address::getRegion() const -> const std::string& { return region; }
auto Address::getRegionCode() const -> const std::string& { return region_code; }
auto Address::getCity() const -> const std::string& { return city; }
auto Address::getDistrict() const -> const std::string& { return district; }
auto Address::getDependentLocality() const -> const std::string& { return dependent_locality; }
auto Address::getStreet() const -> const std::string& { return street; }
auto Address::getHouse() const -> const std::string& { return house_number; }
auto Address::getBuilding() const -> const std::string& { return building; }
auto Address::getApartment() const -> const std::string& { return apartment; }
auto Address::getFloor() const -> const std::string& { return floor; }
auto Address::getEntrance() const -> const std::string& { return entrance; }
auto Address::getPostalCode() const -> const std::string& { return postal_code; }
auto Address::getPoBox() const -> const std::string& { return po_box; }
auto Address::getLandmark() const -> const std::string& { return landmark; }
auto Address::getDirections() const -> const std::string& { return directions; }
auto Address::getFormattedAddress() const -> const std::string& { return formatted_address; }
auto Address::getStandardFormat() const -> const std::string& { return standard_format; }
auto Address::getLatitude() const -> const std::optional<double> { return latitude; }
auto Address::getLongitude() const -> const std::optional<double> { return longitude; }
auto Address::getAltitude() const -> const std::optional<double> { return altitude; }
auto Address::getIsValidated() const -> const bool { return is_validated; }

void Address::setCountry(const std::string& value) { country = value; }
void Address::setCountryCode(const std::string& value) { country_code = value; }
void Address::setRegion(const std::string& value) { region = value; }
void Address::setRegionCode(const std::string& value) { region_code = value; }
void Address::setCity(const std::string& value) { city = value; }
void Address::setDistrict(const std::string& value) { district = value; }
void Address::setDependentLocality(const std::string& value) { dependent_locality = value; }
void Address::setStreet(const std::string& value) { street = value; }
void Address::setHouseNumber(const std::string& value) { house_number = value; }
void Address::setBuilding(const std::string& value) { building = value; }
void Address::setApartment(const std::string& value) { apartment = value; }
void Address::setFloor(const std::string& value) { floor = value; }
void Address::setEntrance(const std::string& value) { entrance = value; }
void Address::setPostalCode(const std::string& value) { postal_code = value; }
void Address::setPoBox(const std::string& value) { po_box = value; }
void Address::setLandmark(const std::string& value) { landmark = value; }
void Address::setDirections(const std::string& value) { directions = value; }
void Address::setFormattedAddress(const std::string& value) { formatted_address = value; }
void Address::setStandardFormat(const std::string& value) { standard_format = value; }
void Address::setLatitude(std::optional<double> value) { latitude = value; }
void Address::setLongitude(std::optional<double> value) { longitude = value; }
void Address::setAltitude(std::optional<double> value) { altitude = value; }
void Address::setIsValidated(bool value) { is_validated = value; }