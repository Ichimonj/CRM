#pragma once
#include "DateTime/time_duration.hpp"
#include "Deal/deal.hpp"
#include "Note/note.hpp"
#include "Person/person.hpp"
#include "Usings/type_usings.hpp"

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
        const WeakInternalEmployee&      owner,
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
    auto getOwner() const -> const WeakInternalEmployee&;
    auto getType() const -> ClientType;
    auto getOtherType() const -> const OptionalStr&;
    auto getLeadSource() const -> LeadSource;
    auto getOtherLeadSource() const -> const OptionalStr&;
    auto getMarketingConsent() const -> bool;
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
    // functions called only from the database
private:
    bool setOwner(const WeakInternalEmployee& owner, const InternalEmployeePtr& changer);
    bool setType(const ClientType type, const InternalEmployeePtr& changer);
    bool setOtherType(const std::string& other_type, const InternalEmployeePtr& changer);
    bool setLeadSource(const LeadSource lead_source, const InternalEmployeePtr& changer);
    bool setOtherLeadSource(
        const std::string& other_lead_source, const InternalEmployeePtr& changer
    );
    bool setMarketingConsent(const bool marketing_consent, const InternalEmployeePtr& changer);
    bool setLeadStatus(
        const std::optional<LeadStatus>& lead_status, const InternalEmployeePtr& changer
    );

    // public functions
public:
    bool setCommunicationChannel(const OptionalStr& channel, const InternalEmployeePtr& changer);
    bool setReferralCode(const OptionalStr& code, const InternalEmployeePtr& changer);
    bool setCustomerAcquisitionCost(
        const std::optional<Money>& money, const InternalEmployeePtr& changer
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
    WeakInternalEmployee owner;
    ClientType           type;
    OptionalStr          other_type;

    LeadSource           lead_source;
    OptionalStr          other_lead_source;
    bool                 marketing_consent;
    OptionalStr          preferred_communication_channel;
    OptionalStr          referral_code;
    //
    std::optional<Money>      customer_acquisition_cost;
    std::optional<LeadStatus> lead_status;
    std::optional<double>     lead_score;
    std::optional<Money>      annual_revenue;
    std::optional<Money>      lifetime_value;
    std::vector<DealPtr>      owned_deals;
    std::vector<OfferPtr>     interested_offers;

    friend class ClientDataBase;

#ifdef _TESTING
public:
    bool _setOwner(const InternalEmployeePtr& owner, const InternalEmployeePtr& changer)
    {
        return this->setOwner(owner, changer);
    }
    bool _setType(const ClientType type, const InternalEmployeePtr& changer)
    {
        return this->setType(type, changer);
    }
    bool _setOtherType(const std::string& other_type, const InternalEmployeePtr& changer)
    {
        return this->setOtherType(other_type, changer);
    }
    bool _setLeadSource(const LeadSource lead_source, const InternalEmployeePtr& changer)
    {
        return this->setLeadSource(lead_source, changer);
    }
    bool _setOtherLeadSource(
        const std::string& other_lead_source, const InternalEmployeePtr& changer
    )
    {
        return this->setOtherLeadSource(other_lead_source, changer);
    }
    bool _setMarketingConsent(const bool marketing_consent, const InternalEmployeePtr& changer)
    {
        return this->setMarketingConsent(marketing_consent, changer);
    }
    bool _setLeadStatus(
        const std::optional<LeadStatus>& lead_status, const InternalEmployeePtr& changer
    )
    {
        return this->setLeadStatus(lead_status, changer);
    }
#endif  // _TESTING
};