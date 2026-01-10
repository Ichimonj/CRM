#pragma once
#include "BigNum/big_uint.hpp"
#include "BigNum/money.hpp"
#include "Usings/type_usings.hpp"

class OfferDeal {
public:
    OfferDeal(const OfferPtr& offer, const DealPtr& deal);
    OfferDeal(
        const OfferPtr&              offer,
        const WeakDealPtr&           deal,
        const BigUint&               quantity,
        const Money&                 price_per_unit,
        const std::optional<double>& discount = std::nullopt
    );

    /// @name Getters
    /// @{
    auto getOffer() const -> const OfferPtr&;
    auto getDeal() const -> const WeakDealPtr&;
    auto getQuantity() const -> const BigUint&;
    auto getPricePerUnit() const -> const Money&;
    auto getDiscount() const -> const std::optional<double>&;
    /// @}

    /// @name Change functions
    /// @{
    void setQuantity(const BigUint& quantity);
    void setPricePerUnit(const Money& price_per_unit);
    void setDiscount(const std::optional<double>& discount);
    /// @}

private:
    OfferPtr    offer;
    WeakDealPtr deal;
    BigUint     quantity;
    Money       price_per_unit = Money("0");
    //
    std::optional<double> discount;
};