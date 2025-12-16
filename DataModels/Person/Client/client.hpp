#pragma once
#include "deal.hpp"
#include "note.hpp"
#include "person.hpp"
#include "time_duration.hpp"
struct BaseInteraction;
using InteractionPtr = std::shared_ptr<BaseInteraction>;
using StringPair     = std::pair<std::string, std::string>;
using DealPtr        = std::shared_ptr<Deal>;
class Client : public Person {
public:
    enum class ClientType : uint8_t {
        Visitor,
        Lead,
        Prospect,
        Costomer,
        LoyalCostomer,
        Panter,
        PetentialClient,
        LostCostomer,
        Analytical,
        Emotional,
        other,
        COUNT
    };
    enum class LeadStatus : uint8_t {
        New,
        Open,
        Working,
        Qualified,
        Unqualified,
        Converted,
        Closed,
        Disqualified,
        Nurturing,
        Lost,
        COUNT
    };
    enum class LeadSource { Website, Referral, EmailCampaing, SocialMedia, other, COUNT };
    Client(
        const BigUint&     id,
        const std::string& name,
        const std::string& surname,
        const OptionalStr& patronymic
    );
    Client(
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
    );
    virtual ~Client() noexcept = default;

    /// @name Getters
    /// @{
    auto getOwner() const -> const InternalEmployeePtr&;
    auto getType() const -> const ClientType;
    auto getOtherType() const -> const OptionalStr&;
    auto getLeadSource() const -> const LeadSource;
    auto getOtherLeadSource() const -> const OptionalStr&;
    auto getMarketingConsent() const -> const bool;
    auto getCommunicationChannel() const -> const OptionalStr&;
    auto getReferralCode() const -> const OptionalStr&;
    auto getCustomerAcquisitionCost() const -> const std::optional<Money>&;
    auto getLeadStatus() const -> const std::optional<LeadStatus>&;
    auto getLeadScore() const -> const std::optional<double>&;
    auto getAnnualRevenue() const -> const std::optional<Money>&;
    auto getLifetimeValue() const -> const std::optional<Money>&;
    auto getOwnedDeals() const -> const std::vector<DealPtr>&;
    auto getInterestedOffers() const -> const std::vector<OfferPtr>&;
    /// @}

    /// @name Change functions
    /// @{
    bool setOwner(const InternalEmployeePtr& owner, const InternalEmployeePtr& changer);
    bool setType(const ClientType type, const InternalEmployeePtr& changer);
    bool setOtherType(const std::string& other_type, const InternalEmployeePtr& changer);
    bool setLeadSource(const LeadSource lead_source, const InternalEmployeePtr& changer);
    bool setOtherLeadSource(
        const std::string& other_lead_source, const InternalEmployeePtr& changer
    );
    bool setMarketingConsent(const bool marketing_consent, const InternalEmployeePtr& changer);
    bool setCommunicationChannel(const OptionalStr& channel, const InternalEmployeePtr& changer);
    bool setReferralCode(const OptionalStr& code, const InternalEmployeePtr& changer);
    bool setCustomerAcquisitionCost(
        const std::optional<Money>& money, const InternalEmployeePtr& changer
    );
    bool setLeadStatus(
        const std::optional<LeadStatus>& lead_status, const InternalEmployeePtr& changer
    );
    bool setLeadScore(const std::optional<double>& lead_score, const InternalEmployeePtr& changer);
    bool setAnnualRevenue(
        const std::optional<Money>& annual_revenue, const InternalEmployeePtr& changer
    );
    bool setLifetimeValue(
        const std::optional<Money>& lifetime_value, const InternalEmployeePtr& changer
    );

    bool addOwnedDeal(const DealPtr& deal, const InternalEmployeePtr& changer);
    bool delOwnedDeal(size_t index, const InternalEmployeePtr& changer);

    bool addInterestedOffer(const OfferPtr& interested_offer, const InternalEmployeePtr& changer);
    bool delInterestedOffer(size_t index, const InternalEmployeePtr& changer);
    /// @}

private:
    InternalEmployeePtr owner;
    ClientType          type;
    OptionalStr         other_type;

    LeadSource          lead_source;
    OptionalStr         other_lead_source;
    bool                marketing_consent;
    OptionalStr         preferred_communication_channel;
    OptionalStr         referral_code;
    //
    std::optional<Money>      customer_acquisition_cost;
    std::optional<LeadStatus> lead_status;
    std::optional<double>     lead_score;
    std::optional<Money>      annual_revenue;
    std::optional<Money>      lifetime_value;
    std::vector<DealPtr>      owned_deals;
    std::vector<OfferPtr>     interested_offers;
};