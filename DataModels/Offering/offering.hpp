#pragma once
#include <stdint.h>

#include <memory>
#include <optional>
#include <string>

#include "big_uint.hpp"
using OptionalStr = std::optional<std::string>;

struct Offer {
    Offer(
        const BigUint&     id,
        const std::string& name,
        const OptionalStr& description,
        const OptionalStr& type,
        const uint32_t     amount,
        const double       discount,
        const double       price
    );
    Offer(const Offer& offer);

public:
    /// @name Getters
    /// @{
    auto getId() const -> const BigUint;
    auto getName() const -> const std::string&;
    auto getDescription() const -> const OptionalStr&;
    auto getType() const -> const OptionalStr&;
    auto getAmount() const -> uint32_t;
    auto getDiscount() const -> double;
    auto getPrice() const -> double;
    /// @}

    /// @name Setters
    /// @{
    void setName(const std::string& name);
    void setDescription(const OptionalStr& description);
    void setType(const OptionalStr& type);
    void setAmount(const uint32_t amount);
    void setDiscount(const double discount);
    void setPrice(const double price);
    /// @}

public:
    /// @name Operators
    /// @{
    Offer& operator--();
    Offer& operator++();
    Offer& operator+(int);
    Offer& operator-(int);
    /// @}

private:
    BigUint     id;
    std::string name;
    OptionalStr description;
    OptionalStr type;

    // The transaction will be copied amount, discount, price
    // This is data at the time of purchase
    uint32_t amount;
    double   discount;
    double   price;
};
