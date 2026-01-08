#include "campaign_lead.hpp"

CampaignLead::CampaignLead(const CampaignPtr& campaign, const WeakClientPtr& lead)
    : campaign(campaign), client(lead)
{
}

CampaignLead::CampaignLead(
    const CampaignPtr& campaign, const WeakClientPtr& lead, const DatePtr& joined_date
)
    : campaign(campaign), client(lead), joined_date(joined_date)
{
}

void CampaignLead::setConvertDate(const DatePtr& date)
{
    if (this->converted_date != date) this->converted_date = date;
}

void CampaignLead::setConversionValue(const std::optional<Money> value)
{
    if (this->conversion_value != value) this->conversion_value = value;
}

auto CampaignLead::getCampaign() const -> const CampaignPtr& { return this->campaign; }
auto CampaignLead::getLead() const -> const WeakClientPtr& { return this->client; }
auto CampaignLead::getJoinedDate() const -> const DatePtr& { return this->joined_date; }
auto CampaignLead::getConvertedDate() const -> const DatePtr& { return this->converted_date; }
auto CampaignLead::getConversionValue() const -> const std::optional<Money>&
{
    return this->conversion_value;
}
