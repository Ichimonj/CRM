#include "client.hpp"

#include "big_uint.hpp"
#include "change_log.hpp"

Client::Client(
    const BigUint&     id,
    const std::string& name,
    const std::string& surname,
    const OptionalStr& patronymic
)
    : Person(id, name, surname, patronymic), lead_source(LeadSource::other), type(ClientType::other)
{
}
Client::Client(
    const BigUint&                   id,
    const std::string&               name,
    const std::string&               surname,
    const OptionalStr&               patronymic,
    const OptionalStr&               preferred_language,
    const DatePtr&                   birthday,
    const PhoneNumberPtr&            phone_number,
    const AddressPtr&                address,
    const OptionalStr&               email,
    const Gender&                    gender,
    const InternalEmployeePtr&       owner,
    const ClientType&                type,
    const OptionalStr&               other_type,
    const LeadSource&                lead_source,
    const OptionalStr&               other_lead_source,
    bool                             marketing_consent,
    const OptionalStr&               preferred_communication_channel,
    const OptionalStr&               referral_code,
    const std::optional<Money>&      customer_acquisition_cost,
    const std::optional<LeadStatus>& lead_status,
    const std::optional<double>&     lead_score,
    const std::optional<Money>&      annual_revenue,
    const std::optional<Money>&      lifetime_value,
    std::vector<OfferPtr>            interested_offers,
    std::vector<SocialNetwork>       social_networks,
    std::vector<PhoneNumber>         more_phone_numbers,
    std::vector<Address>             more_addresses,
    std::vector<std::string>         more_emails,
    std::vector<DocumentPtr>         other_documents,
    std::vector<FileMetadataPtr>     other_files,
    std::vector<InteractionPtr>      interaction_history,
    std::vector<std::string>         tags,
    std::vector<Note>                notes
)
    : Person(
          id,
          name,
          surname,
          patronymic,
          preferred_language,
          birthday,
          phone_number,
          address,
          email,
          gender,
          std::move(social_networks),
          std::move(more_phone_numbers),
          std::move(more_addresses),
          std::move(more_emails),
          std::move(other_documents),
          std::move(other_files),
          std::move(interaction_history),
          std::move(tags),
          std::move(notes)
      )
    , owner(owner)
    , type(type)
    , other_type(other_type)
    , lead_source(lead_source)
    , other_lead_source(other_lead_source)
    , marketing_consent(marketing_consent)
    , preferred_communication_channel(preferred_communication_channel)
    , referral_code(referral_code)
    , customer_acquisition_cost(customer_acquisition_cost)
    , lead_status(lead_status)
    , lead_score(lead_score)
    , annual_revenue(annual_revenue)
    , lifetime_value(lifetime_value)
    , interested_offers(std::move(interested_offers))
{
}

auto Client::getOwner() const -> const InternalEmployeePtr& { return this->owner; }
auto Client::getType() const -> ClientType { return this->type; }
auto Client::getOtherType() const -> const OptionalStr& { return this->other_type; }
auto Client::getLeadSource() const -> LeadSource { return this->lead_source; }
auto Client::getOtherLeadSource() const -> const OptionalStr& { return this->other_lead_source; }
auto Client::getMarketingConsent() const -> bool { return this->marketing_consent; }
auto Client::getCommunicationChannel() const -> const OptionalStr&
{
    return this->preferred_communication_channel;
}
auto Client::getReferralCode() const -> const OptionalStr& { return this->referral_code; }
auto Client::getCustomerAcquisitionCost() const -> const std::optional<Money>&
{
    return this->customer_acquisition_cost;
}
auto Client::getInterestedOffers() const -> const std::vector<OfferPtr>&
{
    return this->interested_offers;
}
auto Client::getLeadStatus() const -> const std::optional<LeadStatus>& { return this->lead_status; }
auto Client::getLeadScore() const -> const std::optional<double>& { return this->lead_score; }
auto Client::getAnnualRevenue() const -> const std::optional<Money>&
{
    return this->annual_revenue;
}
auto Client::getLifetimeValue() const -> const std::optional<Money>&
{
    return this->lifetime_value;
}

auto Client::getOwnedDeals() const -> const std::vector<DealPtr>& { return this->owned_deals; }

bool Client::setOwner(const InternalEmployeePtr& owner, const InternalEmployeePtr& changer)
{
    if (this->owner != owner) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->owner),
            PTR_TO_OPTIONAL(owner),
            ClientFields::Owner,
            this->owner ? ChangeLog::FieldType::InternalEmployee : ChangeLog::FieldType::null,
            owner ? ChangeLog::FieldType::InternalEmployee : ChangeLog::FieldType::null,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->owner = owner;
        return true;
    }
    return false;
}

bool Client::setType(const ClientType type, const InternalEmployeePtr& changer)
{
    if (this->type != type) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->other_type ? std::make_optional<ChangeLog::ValueVariant>(
                                   std::make_shared<std::string>(this->other_type.value())
                               )
                             : std::make_optional<ChangeLog::ValueVariant>(this->type),
            std::make_optional<ChangeLog::ValueVariant>(type),
            ClientFields::Type,
            this->other_type ? ChangeLog::FieldType::String : ChangeLog::FieldType::ClientType,
            ChangeLog::FieldType::ClientType,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->type       = type;
        this->other_type = std::nullopt;
        return true;
    }
    return false;
}

bool Client::setOtherType(const std::string& other_type, const InternalEmployeePtr& changer)
{
    if (this->other_type != other_type) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->other_type ? std::make_optional<ChangeLog::ValueVariant>(
                                   std::make_shared<std::string>(this->other_type.value())
                               )
                             : std::make_optional<ChangeLog::ValueVariant>(this->type),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(other_type)),
            ClientFields::OtherType,
            this->other_type ? ChangeLog::FieldType::String : ChangeLog::FieldType::ClientType,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->other_type = other_type;
        this->type       = ClientType::other;
        return true;
    }
    return false;
}

bool Client::setLeadSource(const LeadSource lead_source, const InternalEmployeePtr& changer)
{
    if (this->lead_source != lead_source) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->other_lead_source
                ? std::make_optional<ChangeLog::ValueVariant>(
                      std::make_shared<std::string>(this->other_lead_source.value())
                  )
                : std::make_optional<ChangeLog::ValueVariant>(this->lead_source),
            std::make_optional<ChangeLog::ValueVariant>(lead_source),
            ClientFields::LeadSource,
            this->other_lead_source ? ChangeLog::FieldType::String
                                    : ChangeLog::FieldType::LeadSource,
            ChangeLog::FieldType::LeadSource,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->lead_source       = lead_source;
        this->other_lead_source = std::nullopt;
        return true;
    }
    return false;
}

bool Client::setOtherLeadSource(
    const std::string& other_lead_source, const InternalEmployeePtr& changer
)
{
    if (this->other_lead_source != other_lead_source) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->other_lead_source
                ? std::make_optional<ChangeLog::ValueVariant>(
                      std::make_shared<std::string>(this->other_lead_source.value())
                  )
                : std::make_optional<ChangeLog::ValueVariant>(this->lead_source),
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<std::string>(other_lead_source)
            ),
            ClientFields::OtherLeadSource,
            this->other_lead_source ? ChangeLog::FieldType::String
                                    : ChangeLog::FieldType::LeadSource,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->other_lead_source = other_lead_source;
        this->lead_source       = LeadSource::other;
        return true;
    }
    return false;
}

bool Client::setMarketingConsent(const bool marketing_consent, const InternalEmployeePtr& changer)
{
    if (this->marketing_consent != marketing_consent) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->marketing_consent),
            std::make_optional<ChangeLog::ValueVariant>(marketing_consent),
            ClientFields::MarketingConsent,
            ChangeLog::FieldType::Bool,
            ChangeLog::FieldType::Bool,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->marketing_consent = marketing_consent;
        return true;
    }
    return false;
}

bool Client::setCommunicationChannel(const OptionalStr& channel, const InternalEmployeePtr& changer)
{
    if (this->preferred_communication_channel != channel) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->preferred_communication_channel),
            OPTIONAL_STR_TO_VALUE(channel),
            ClientFields::CommunicationChannel,
            this->preferred_communication_channel ? ChangeLog::FieldType::String
                                                  : ChangeLog::FieldType::null,
            channel ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->preferred_communication_channel = channel;
        return true;
    }
    return false;
}

bool Client::setReferralCode(const OptionalStr& code, const InternalEmployeePtr& changer)
{
    if (this->referral_code != code) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->referral_code),
            OPTIONAL_STR_TO_VALUE(code),
            ClientFields::ReferralCode,
            this->referral_code ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            code ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->referral_code = code;
        return true;
    }
    return false;
}

bool Client::setCustomerAcquisitionCost(
    const std::optional<Money>& money, const InternalEmployeePtr& changer
)
{
    if (this->customer_acquisition_cost != money) {
        Date                                   update = Date();
        std::optional<ChangeLog::ValueVariant> old_value =
            this->customer_acquisition_cost
                ? std::make_optional<ChangeLog::ValueVariant>(
                      std::make_shared<Money>(this->customer_acquisition_cost.value())
                  )
                : std::nullopt;

        std::optional<ChangeLog::ValueVariant> new_value =
            money
                ? std::make_optional<ChangeLog::ValueVariant>(std::make_shared<Money>(money.value())
                  )
                : std::nullopt;

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::move(old_value),
            std::move(new_value),
            ClientFields::CustomerAcquisitionCost,
            old_value ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
            new_value ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->customer_acquisition_cost = money;
        return true;
    }
    return false;
}

bool Client::setLeadStatus(
    const std::optional<LeadStatus>& lead_status, const InternalEmployeePtr& changer
)
{
    if (this->lead_status != lead_status) {
        Date                                   update = Date();
        std::optional<ChangeLog::ValueVariant> old_value =
            this->lead_status
                ? std::make_optional<ChangeLog::ValueVariant>(this->lead_status.value())
                : std::nullopt;
        std::optional<ChangeLog::ValueVariant> new_value =
            lead_status ? std::make_optional<ChangeLog::ValueVariant>(lead_status.value())
                        : std::nullopt;

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::move(old_value),
            std::move(new_value),
            ClientFields::LeadStatus,
            old_value ? ChangeLog::FieldType::LeadStatus : ChangeLog::FieldType::null,
            new_value ? ChangeLog::FieldType::LeadStatus : ChangeLog::FieldType::null,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->lead_status = lead_status;
        return true;
    }
    return false;
}

bool Client::setLeadScore(
    const std::optional<double>& lead_score, const InternalEmployeePtr& changer
)
{
    if (this->lead_score != lead_score) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->lead_score ? std::make_optional<ChangeLog::ValueVariant>(this->lead_score.value())
                             : std::nullopt,
            lead_score ? std::make_optional<ChangeLog::ValueVariant>(lead_score.value())
                       : std::nullopt,
            ClientFields::LeadScore,
            this->lead_score ? ChangeLog::FieldType::Double : ChangeLog::FieldType::null,
            lead_score ? ChangeLog::FieldType::Double : ChangeLog::FieldType::null,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->lead_score = lead_score;
        return true;
    }
    return false;
}

bool Client::setAnnualRevenue(
    const std::optional<Money>& annual_revenue, const InternalEmployeePtr& changer
)
{
    if (this->annual_revenue != annual_revenue) {
        Date                                   update = Date();
        std::optional<ChangeLog::ValueVariant> old_value =
            this->annual_revenue ? std::make_optional<ChangeLog::ValueVariant>(
                                       std::make_shared<Money>(this->annual_revenue.value())
                                   )
                                 : std::nullopt;
        std::optional<ChangeLog::ValueVariant> new_value =
            annual_revenue ? std::make_optional<ChangeLog::ValueVariant>(
                                 std::make_shared<Money>(annual_revenue.value())
                             )
                           : std::nullopt;

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::move(old_value),
            std::move(new_value),
            ClientFields::AnnualRevenue,
            old_value ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
            new_value ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->annual_revenue = annual_revenue;
        return true;
    }
    return false;
}

bool Client::setLifetimeValue(
    const std::optional<Money>& lifetime_value, const InternalEmployeePtr& changer
)
{
    if (this->lifetime_value != lifetime_value) {
        Date                                   update = Date();
        std::optional<ChangeLog::ValueVariant> old_value =
            this->lifetime_value ? std::make_optional<ChangeLog::ValueVariant>(
                                       std::make_shared<Money>(this->lifetime_value.value())
                                   )
                                 : std::nullopt;

        std::optional<ChangeLog::ValueVariant> new_value =
            lifetime_value ? std::make_optional<ChangeLog::ValueVariant>(
                                 std::make_shared<Money>(lifetime_value.value())
                             )
                           : std::nullopt;

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::move(old_value),
            std::move(new_value),
            ClientFields::LifetimeValue,
            old_value ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
            new_value ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->lifetime_value = lifetime_value;
        return true;
    }
    return false;
}

bool Client::addOwnedDeal(const DealPtr& deal, const InternalEmployeePtr& changer)
{
    if (std::find(this->owned_deals.begin(), this->owned_deals.end(), deal) ==
        this->owned_deals.end()) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(deal),
            ClientFields::OwnedDeals,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Deal,
            ChangeLog::Action::Add,
            update
        ));

        this->updateAt(update);
        this->addRelatedDeals(deal, changer, update);
        this->owned_deals.push_back(deal);
        return true;
    }
    return false;
}

bool Client::delOwnedDeal(size_t index, const InternalEmployeePtr& changer)
{
    if (index < this->owned_deals.size()) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->owned_deals[index]),
            std::nullopt,
            ClientFields::OwnedDeals,
            ChangeLog::FieldType::Deal,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->updateAt(update);
        this->delRelatedDeals(this->owned_deals[index], changer, update);
        this->owned_deals.erase(this->owned_deals.begin() + index);
        return true;
    }
    return false;
}

bool Client::addInterestedOffer(
    const OfferPtr& interested_offer, const InternalEmployeePtr& changer
)
{
    if (std::find(
            this->interested_offers.begin(), this->interested_offers.end(), interested_offer
        ) == this->interested_offers.end()) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(interested_offer),
            ClientFields::InterestedOffers,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Offer,
            ChangeLog::Action::Add,
            update
        ));
        this->updateAt(update);
        this->interested_offers.push_back(interested_offer);
        return true;
    }
    return false;
}

bool Client::delInterestedOffer(size_t index, const InternalEmployeePtr& changer)
{
    if (index < this->interested_offers.size()) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->interested_offers[index]),
            std::nullopt,
            ClientFields::InterestedOffers,
            ChangeLog::FieldType::Offer,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->updateAt(update);
        this->interested_offers.erase(this->interested_offers.begin() + index);
        return true;
    }
    return false;
}