#pragma once
#include <string>

/// @brief Storage structure of the physical address
struct Address {
    Address() = default;
    Address(
        const std::string& country,
        const std::string& city,
        const std::string& street,
        const std::string& house,
        const std::string& apartment,
        const std::string& postal_code
    );
    Address(const Address& address);
    bool operator==(const Address& other) const;
    bool operator!=(const Address& other) const;

public:
    /// @name Getters
    /// @{
    const std::string& getCountry() const;
    const std::string& getCity() const;
    const std::string& getStreet() const;
    const std::string& getHouse() const;
    const std::string& getApartment() const;
    const std::string& getPostalCode() const;
    /// @}

    /// @name Setters
    /// @{
    void setCountry(const std::string& country);
    void setCity(const std::string& city);
    void setStreet(const std::string& street);
    void setHouse(const std::string& house);
    void setApartment(const std::string& apartment);
    void setPostalCode(const std::string& postal_code);
    /// @}

private:
    std::string country     = "";
    std::string city        = "";
    std::string street      = "";
    std::string house       = "";
    std::string apartment   = "";
    std::string postal_code = "";
};
