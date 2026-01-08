#pragma once
#include "BigNum/money.hpp"
#include "DateTime/date.hpp"
#include "Person/Client/client.hpp"
#include "campaign.hpp"

class CampaignLead {
public:
    CampaignLead(const CampaignPtr& campaign, const WeakClientPtr& lead);
    CampaignLead(
        const CampaignPtr& campaign, const WeakClientPtr& lead, const DatePtr& joined_date
    );

    /// @name Change functions
    /// @{
    void setConvertDate(const DatePtr& date);
    void setConversionValue(const std::optional<Money> value);
    /// @}

    /// @name Getters
    /// @{
    auto getCampaign() const -> const CampaignPtr&;
    auto getLead() const -> const WeakClientPtr&;
    auto getJoinedDate() const -> const DatePtr&;
    auto getConvertedDate() const -> const DatePtr&;
    auto getConversionValue() const -> const std::optional<Money>&;
    /// @}

private:
    CampaignPtr   campaign;
    WeakClientPtr client;
    DatePtr       joined_date;
    DatePtr       converted_date;
    //
    std::optional<Money> conversion_value;
};