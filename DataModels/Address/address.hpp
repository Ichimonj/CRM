#pragma once
#include <optional>
#include <string>
/// @brief Storage structure of the physical address
struct Address {
    Address() = default;
    Address(
        const std::string& country,
        const std::string& city,
        const std::string& street,
        const std::string& house_number,
        const std::string& apartment,
        const std::string& postal_code
    );
    Address(const Address& address);

    bool operator==(const Address& other) const;
    bool operator!=(const Address& other) const;

public:
    /// @name Getters
    /// @{
    auto getCountry() const -> const std::string&;
    auto getCountryCode() const -> const std::string&;
    auto getRegion() const -> const std::string&;
    auto getRegionCode() const -> const std::string&;
    auto getCity() const -> const std::string&;
    auto getDistrict() const -> const std::string&;
    auto getDependentLocality() const -> const std::string&;
    auto getStreet() const -> const std::string&;
    auto getHouse() const -> const std::string&;
    auto getBuilding() const -> const std::string&;
    auto getApartment() const -> const std::string&;
    auto getFloor() const -> const std::string&;
    auto getEntrance() const -> const std::string&;
    auto getPostalCode() const -> const std::string&;
    auto getPoBox() const -> const std::string&;
    auto getLandmark() const -> const std::string&;
    auto getDirections() const -> const std::string&;
    auto getFormattedAddress() const -> const std::string&;
    auto getLatitude() const -> const std::optional<double>;
    auto getLongitude() const -> const std::optional<double>;
    auto getAltitude() const -> const std::optional<double>;
    auto getIsValidated() const -> bool;
    auto getStandardFormat() const -> const std::string&;
    /// @}

    /// @name Setters
    /// @{
    void setCountry(const std::string& value);
    void setCountryCode(const std::string& value);
    void setRegion(const std::string& value);
    void setRegionCode(const std::string& value);
    void setCity(const std::string& value);
    void setDistrict(const std::string& value);
    void setDependentLocality(const std::string& value);
    void setStreet(const std::string& value);
    void setHouseNumber(const std::string& value);
    void setBuilding(const std::string& value);
    void setApartment(const std::string& value);
    void setFloor(const std::string& value);
    void setEntrance(const std::string& value);
    void setPostalCode(const std::string& value);
    void setPoBox(const std::string& value);
    void setLandmark(const std::string& value);
    void setDirections(const std::string& value);
    void setFormattedAddress(const std::string& value);
    void setStandardFormat(const std::string& value);
    void setLatitude(std::optional<double> value);
    void setLongitude(std::optional<double> value);
    void setAltitude(std::optional<double> value);
    void setIsValidated(bool value);
    /// @}

private:
    // Country
    std::string country;       // "United States"
    std::string country_code;  // "US" (ISO 3166-1 alpha-2)

    // Region, state
    std::string region;
    std::string region_code;

    // City
    std::string city;
    std::string district;  // City area
    std::string dependent_locality;

    // Street, house
    std::string street;
    std::string house_number;
    std::string building;   // "Tower A", "Block B"
    std::string apartment;  // "Apt 4B", "Suite 500"
    std::string floor;      // "5th Floor"
    std::string entrance;   // "Entrance 2"

    std::string postal_code;  // "90028" "SW1A 1AA"
    std::string po_box;       // "PO Box 123"

    std::string landmark;    // "Near Central Park"
    std::string directions;  // "3rd house on the left"
    std::string formatted_address;

    //
    std::optional<double> latitude  = 0.0;
    std::optional<double> longitude = 0.0;
    std::optional<double> altitude  = 0.0;

    bool                  is_validated;
    std::string           standard_format;
};
