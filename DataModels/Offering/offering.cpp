#include "offering.hpp"

#include <stdexcept>

#include "location.hpp"

Offer::Offer(
    const BigUint&     id,
    const std::string& name,
    const OptionalStr& description,
    const OptionalStr& type,
    const uint32_t     amount,
    const double       discount,
    const double       price
)
    : id(id), amount(amount), discount(discount), price(price)
{
    this->name        = name;
    this->description = description;
    this->type        = type;
}

Offer::Offer(const Offer& offer)
    : id(offer.id)
    , name(offer.name)
    , description(offer.description)
    , type(offer.type)
    , amount(offer.amount)
    , discount(offer.discount)
    , price(offer.price)
{
}

// Getters
auto Offer::getId() const -> const BigUint { return this->id; }
auto Offer::getName() const -> const std::string& { return this->name; }
auto Offer::getDescription() const -> const OptionalStr& { return this->description; }
auto Offer::getType() const -> const OptionalStr& { return this->type; }
auto Offer::getAmount() const -> uint32_t { return this->amount; }
auto Offer::getDiscount() const -> double { return this->discount; }
auto Offer::getPrice() const -> double { return this->price; }

// Setters
void Offer::setName(const std::string& name) { this->name = name; }
void Offer::setDescription(const OptionalStr& description) { this->description = description; }
void Offer::setType(const OptionalStr& type) { this->type = type; }
void Offer::setAmount(const uint32_t amount) { this->amount = amount; }
void Offer::setDiscount(const double discount) { this->discount = discount; }
void Offer::setPrice(const double price) { this->price = price; }

// Oerators
Offer& Offer::operator--()
{
    this->amount--;
    return *this;
}
Offer& Offer::operator++()
{
    this->amount++;
    return *this;
}

Offer& Offer::operator+(int i)
{
    this->amount += i;
    return *this;
}

Offer& Offer::operator-(int i)
{
    if (static_cast<uint32_t>(i) > this->amount)
        throw std::runtime_error(errors::not_enough_products);

    this->amount -= i;
    return *this;
}