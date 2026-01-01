#pragma once
#include <memory>
#include <optional>
#include <vector>

#include "BigNum/big_uint.hpp"
#include "Note/note.hpp"

class Money;
class Client;
struct Date;
class InternalEmployee;
class ChangeLog;
class CampaignLead;

using OptionalStr         = std::optional<std::string>;
using MoneyPtr            = std::shared_ptr<Money>;
using DatePtr             = std::shared_ptr<Date>;
using CampaignLeadPtr     = std::shared_ptr<CampaignLead>;
using InternalEmployeePtr = std::shared_ptr<InternalEmployee>;
using ChangeLogPtr        = std::shared_ptr<ChangeLog>;

enum class CampaignType : uint8_t { Email, SocialAds, Webinar, Event, other, COUNT };

class Campaign {
public:
    Campaign(const BigUint& id);

    Campaign(
        const BigUint&               id,
        const std::string&           name,
        const CampaignType&          type,
        const OptionalStr&           other_type,
        const DatePtr&               start_date,
        const DatePtr&               end_date,
        const MoneyPtr&              budget,
        const MoneyPtr&              budget_spent,
        const uint32_t&              total_joined,
        const uint32_t&              total_converted,
        const InternalEmployeePtr&   creator,
        const std::optional<double>& conversion_rate,
        std::vector<Note>            notes,
        std::vector<CampaignLeadPtr> target_leads,
        std::vector<ChangeLogPtr>    change_logs
    );

    /// @name Getters
    /// @{
    auto getId() const -> const BigUint&;
    auto getName() const -> const std::string&;
    auto getType() const -> CampaignType;
    auto getOtherType() const -> const OptionalStr&;
    auto getStartDate() const -> const DatePtr&;
    auto getEndDate() const -> const DatePtr&;
    auto getBudget() const -> const MoneyPtr&;
    auto getBudgetSpent() const -> const MoneyPtr&;
    auto getTotalJoined() const -> const uint32_t&;
    auto getTotalConverted() const -> const uint32_t&;
    auto getCreator() const -> const InternalEmployeePtr&;
    auto getConversionRate() const -> const std::optional<double>&;
    auto getNotes() const -> const std::vector<Note>&;
    auto getTargetLeads() const -> const std::vector<CampaignLeadPtr>&;
    auto getChangeLogs() const -> const std::vector<ChangeLogPtr>&;
    /// @}

    /// @name Setters
    /// @{
    bool setName(const std::string& name, const InternalEmployeePtr& changer);
    bool setType(CampaignType type, const InternalEmployeePtr& changer);
    bool setOtherType(const OptionalStr& other_type, const InternalEmployeePtr& changer);
    bool setStartDate(const DatePtr& start_date, const InternalEmployeePtr& changer);
    bool setEndDate(const DatePtr& end_date, const InternalEmployeePtr& changer);
    bool setBudget(const MoneyPtr& budget, const InternalEmployeePtr& changer);
    bool setBudgetSpent(const MoneyPtr& budget_spent, const InternalEmployeePtr& changer);
    bool setTotalJoined(uint32_t total_joined, const InternalEmployeePtr& changer);
    bool setTotalConverted(uint32_t total_converted, const InternalEmployeePtr& changer);
    bool setCreator(const InternalEmployeePtr& creator, const InternalEmployeePtr& changer);
    bool setConversionRate(
        const std::optional<double>& conversion_rate, const InternalEmployeePtr& changer
    );

    bool addNote(const Note& note, const InternalEmployeePtr& changer);
    bool delNote(size_t index, const InternalEmployeePtr& changer);

    bool addTargetLeads(const CampaignLeadPtr& target_lead, const InternalEmployeePtr& changer);
    bool delTargetLeads(size_t index, const InternalEmployeePtr& changer);
    /// @}

private:
    BigUint             id;
    std::string         name;
    CampaignType        type;
    OptionalStr         other_type;
    DatePtr             start_date;
    DatePtr             end_date;
    MoneyPtr            budget;
    MoneyPtr            budget_spent;
    uint32_t            total_joined    = 0;
    uint32_t            total_converted = 0;
    InternalEmployeePtr creator;
    //
    std::optional<double>        conversion_rate;
    std::vector<Note>            notes;
    std::vector<CampaignLeadPtr> target_leads;
    std::vector<ChangeLogPtr>    change_logs;
};