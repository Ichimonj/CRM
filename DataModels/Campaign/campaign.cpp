#include "campaign.hpp"

#include "change_log.hpp"

Campaign::Campaign(const BigUint& id) : id(id) {}

Campaign::Campaign(
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
)
    : id(id)
    , name(name)
    , type(type)
    , other_type(other_type)
    , start_date(start_date)
    , end_date(end_date)
    , budget(budget)
    , budget_spent(budget_spent)
    , total_joined(total_joined)
    , total_converted(total_converted)
    , creator(creator)
    , conversion_rate(conversion_rate)
    , notes(std::move(notes))
    , target_leads(std::move(target_leads))
    , change_logs(std::move(change_logs))
{
}
auto Campaign::getId() const -> const BigUint& { return id; }
auto Campaign::getName() const -> const std::string& { return name; }
auto Campaign::getType() const -> const CampaignType { return type; }
auto Campaign::getOtherType() const -> const OptionalStr& { return other_type; }
auto Campaign::getStartDate() const -> const DatePtr& { return start_date; }
auto Campaign::getEndDate() const -> const DatePtr& { return end_date; }
auto Campaign::getBudget() const -> const MoneyPtr& { return budget; }
auto Campaign::getBudgetSpent() const -> const MoneyPtr& { return this->budget_spent; }
auto Campaign::getTotalJoined() const -> const uint32_t& { return total_joined; }
auto Campaign::getTotalConverted() const -> const uint32_t& { return total_converted; }
auto Campaign::getCreator() const -> const InternalEmployeePtr& { return creator; }
auto Campaign::getConversionRate() const -> const std::optional<double>& { return conversion_rate; }
auto Campaign::getNotes() const -> const std::vector<Note>& { return notes; }
auto Campaign::getTargetLeads() const -> const std::vector<CampaignLeadPtr>&
{
    return target_leads;
}
auto Campaign::getChangeLogs() const -> const std::vector<ChangeLogPtr>& { return change_logs; }

void Campaign::setName(const std::string& name, const InternalEmployeePtr& changer)
{
    if (this->name != name) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<std::string>(this->name)),
            std::make_optional(std::make_shared<std::string>(name)),
            CampaignFields::Name,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->name = name;
    }
}

void Campaign::setType(CampaignType type, const InternalEmployeePtr& changer)
{
    if (this->type != type) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->other_type
                ? std::make_optional(std::make_shared<std::string>(this->other_type.value()))
                : std::make_optional<ChangeLog::ValueVariant>(this->type),
            std::make_optional(type),
            CampaignFields::Name,
            this->other_type ? ChangeLog::FieldType::String : ChangeLog::FieldType::CampaignType,
            ChangeLog::FieldType::CampaignType,
            ChangeLog::Action::Change
        ));
        this->type       = type;
        this->other_type = std::nullopt;
    }
}

void Campaign::setOtherType(const OptionalStr& other_type, const InternalEmployeePtr& changer)
{
    if (this->other_type != other_type) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->other_type
                ? std::make_optional(std::make_shared<std::string>(this->other_type.value()))
                : std::make_optional<ChangeLog::ValueVariant>(this->type),
            std::make_optional(std::make_shared<std::string>(other_type.value())),
            CampaignFields::Name,
            this->other_type ? ChangeLog::FieldType::String : ChangeLog::FieldType::CampaignType,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->other_type = other_type;
        this->type       = CampaignType::other;
    }
}

void Campaign::setStartDate(const DatePtr& start_date, const InternalEmployeePtr& changer)
{
    if (this->start_date == nullptr || start_date == nullptr) {
        if (this->start_date == start_date) {
            return;
        }
    } else if (*this->start_date == *start_date) {
        return;
    }
    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->start_date),
        PTR_TO_OPTIONAL(start_date),
        CampaignFields::StartDate,
        this->start_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        start_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->start_date = start_date;
}

void Campaign::setEndDate(const DatePtr& end_date, const InternalEmployeePtr& changer)
{
    if (this->end_date == nullptr || end_date == nullptr) {
        if (this->end_date == end_date) {
            return;
        }
    } else if (*this->end_date == *end_date) {
        return;
    }
    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->end_date),
        PTR_TO_OPTIONAL(end_date),
        CampaignFields::StartDate,
        this->end_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        end_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->end_date = end_date;
}

void Campaign::setBudget(const MoneyPtr& budget, const InternalEmployeePtr& changer)
{
    if (this->budget == nullptr || budget == nullptr) {
        if (this->budget == budget) {
            return;
        }
    } else if (*this->budget == *budget) {
        return;
    }
    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->budget),
        PTR_TO_OPTIONAL(budget),
        CampaignFields::StartDate,
        this->budget ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        budget ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->budget = budget;
}

void Campaign::setBudgetSpent(const MoneyPtr& budget_spent, const InternalEmployeePtr& changer)
{
    if (this->budget_spent == nullptr || budget_spent == nullptr) {
        if (this->budget_spent == budget_spent) {
            return;
        }
    } else if (*this->budget_spent == *budget_spent) {
        return;
    }
    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->budget_spent),
        PTR_TO_OPTIONAL(budget_spent),
        CampaignFields::StartDate,
        this->budget_spent ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        budget_spent ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->budget_spent = budget_spent;
}

void Campaign::setTotalJoined(uint32_t total_joined, const InternalEmployeePtr& changer)
{
    if (this->total_joined != total_joined) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->total_joined),
            std::make_optional(total_joined),
            CampaignFields::TotalJoined,
            ChangeLog::FieldType::Uint,
            ChangeLog::FieldType::Uint,
            ChangeLog::Action::Change
        ));
        this->total_joined = total_joined;
    }
}

void Campaign::setTotalConverted(uint32_t total_converted, const InternalEmployeePtr& changer)
{
    if (this->total_converted != total_converted) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->total_converted),
            std::make_optional(total_converted),
            CampaignFields::TotalConverted,
            ChangeLog::FieldType::Uint,
            ChangeLog::FieldType::Uint,
            ChangeLog::Action::Change
        ));
        this->total_converted = total_converted;
    }
}

void Campaign::setCreator(const InternalEmployeePtr& creator, const InternalEmployeePtr& changer)
{
    if (this->creator != creator) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->creator),
            std::make_optional(creator),
            CampaignFields::Creator,
            ChangeLog::FieldType::InternalEmployee,
            ChangeLog::FieldType::InternalEmployee,
            ChangeLog::Action::Change
        ));
        this->creator = creator;
    }
}

void Campaign::setConversionRate(
    const std::optional<double>& conversion_rate, const InternalEmployeePtr& changer
)
{
    if (this->conversion_rate != conversion_rate) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->conversion_rate,
            conversion_rate,
            CampaignFields::ConversionRate,
            this->conversion_rate ? ChangeLog::FieldType::Double : ChangeLog::FieldType::null,
            conversion_rate ? ChangeLog::FieldType::Double : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->conversion_rate = conversion_rate;
    }
}

void Campaign::addNote(const Note& note, const InternalEmployeePtr& changer)
{
    if (std::find(this->notes.begin(), this->notes.end(), note) == this->notes.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(std::make_shared<Note>(note)),
            CampaignFields::Notes,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Note,
            ChangeLog::Action::Add
        ));
        this->notes.push_back(note);
    }
}

void Campaign::delNote(size_t index, const InternalEmployeePtr& changer)
{
    if (this->notes.size() > index) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<Note>(this->notes[index])),
            std::nullopt,
            CampaignFields::Notes,
            ChangeLog::FieldType::Note,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->notes.erase(this->notes.begin() + index);
    }
}

void Campaign::addTargetLeads(
    const CampaignLeadPtr& target_lead, const InternalEmployeePtr& changer
)
{
    if (std::find(this->target_leads.begin(), this->target_leads.end(), target_lead) ==
        this->target_leads.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(target_lead),
            CampaignFields::TargetLeads,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::CampaignLead,
            ChangeLog::Action::Add
        ));
        this->target_leads.push_back(target_lead);
    }
}

void Campaign::delTargetLeads(size_t index, const InternalEmployeePtr& changer)
{
    if (this->notes.size() > index) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->target_leads[index]),
            std::nullopt,
            CampaignFields::TargetLeads,
            ChangeLog::FieldType::CampaignLead,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->target_leads.erase(this->target_leads.begin() + index);
    }
}