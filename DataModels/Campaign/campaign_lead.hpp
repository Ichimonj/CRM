#pragma once
#include "BigNum/money.hpp"
#include "Person/Client/client.hpp"
#include "DateTime/date.hpp"
#include "campaign.hpp"

using CampaignPtr = std::shared_ptr<Campaign>;
using ClientPtr   = std::shared_ptr<Client>;
using DatePtr     = std::shared_ptr<Date>;

class CampaignLead {
public:
    CampaignLead(const CampaignPtr& campaign, const ClientPtr& lead);
    CampaignLead(const CampaignPtr& campaign, const ClientPtr& lead, const DatePtr& joined_date);

    /// @name Change functions
    /// @{
    void setConvertDate(const DatePtr& date);
    void setConversionValue(const std::optional<Money> value);
    /// @}

    /// @name Getters
    /// @{
    auto getCampaign() const -> const CampaignPtr&;
    auto getLead() const -> const ClientPtr&;
    auto getJoinedDate() const -> const DatePtr&;
    auto getConvertedDate() const -> const DatePtr&;
    auto getConversionValue() const -> const std::optional<Money>&;
    /// @}

private:
    CampaignPtr campaign;
    ClientPtr   client;
    DatePtr     joined_date;
    DatePtr     converted_date;
    //
    std::optional<Money> conversion_value;
};