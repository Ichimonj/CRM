#include "offer_deal.hpp"

OfferDeal::OfferDeal(const OfferPtr& offer, const DealPtr& deal) : offer(offer), deal(deal) {}

OfferDeal::OfferDeal(
    const OfferPtr&              offer,
    const WeakDealPtr&           deal,
    const BigUint&               quantity,
    const Money&                 price_per_unit,
    const std::optional<double>& discount
)
    : offer(offer)
    , deal(deal)
    , quantity(quantity)
    , price_per_unit(price_per_unit)
    , discount(discount)
{
}

auto OfferDeal::getOffer() const -> const OfferPtr& { return this->offer; }
auto OfferDeal::getDeal() const -> const WeakDealPtr& { return this->deal; }
auto OfferDeal::getQuantity() const -> const BigUint& { return this->quantity; }
auto OfferDeal::getPricePerUnit() const -> const Money& { return this->price_per_unit; }
auto OfferDeal::getDiscount() const -> const std::optional<double>& { return this->discount; }

void OfferDeal::setQuantity(const BigUint& quantity)
{
    if (this->quantity != quantity) this->quantity = quantity;
}

void OfferDeal::setPricePerUnit(const Money& price_per_unit)
{
    if (this->price_per_unit != price_per_unit) this->price_per_unit = price_per_unit;
}

void OfferDeal::setDiscount(const std::optional<double>& discount)
{
    if (this->discount != discount) this->discount = discount;
}
