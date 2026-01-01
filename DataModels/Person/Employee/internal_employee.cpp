#include "internal_employee.hpp"

#include "ChangeLog/change_log.hpp"
InternalEmployee::InternalEmployee(
    const BigUint&     id,
    const std::string& name,
    const std::string& surname,
    const OptionalStr& patronymic
)
    : Person(id, name, surname, patronymic)
    , access_role(AccessRole::other)
    , status(EmployeeStatus::other)
    , time_zone(0)
    , is_active(false)
{
}

InternalEmployee::InternalEmployee(
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
    const InternalEmployeePtr&       manager,
    const OptionalStr&               position,
    const OptionalStr&               department,
    const AccessRole&                access_role,
    const OptionalStr&               other_role,
    const EmployeeStatus&            status,
    const OptionalStr&               other_status,
    const OptionalStr&               sales_territory,
    const DatePtr&                   last_login_date,
    const DatePtr&                   last_action_date,
    int                              time_zone,
    const std::optional<double>&     commission_rate,
    const MoneyPtr&                  base_salary,
    const std::optional<double>&     performance_score,
    const DatePtr&                   next_review_date,
    const DatePtr&                   hire_date,
    const DatePtr&                   dismissal_date,
    std::vector<ClientPtr>           leads,
    std::vector<Note>                notes,
    std::vector<Money>               monthly_quota,
    std::vector<TaskPtr>             tasks,
    std::vector<DocumentPtr>         documents,
    std::vector<std::string>         skills,
    std::vector<InternalEmployeePtr> direct_reports,
    std::vector<SocialNetwork>       social_networks,
    std::vector<PhoneNumber>         more_phone_numbers,
    std::vector<Address>             more_addresses,
    std::vector<std::string>         more_emails,
    std::vector<DocumentPtr>         other_documents,
    std::vector<FileMetadataPtr>     other_files,
    std::vector<InteractionPtr>      interaction_history,
    std::vector<std::string>         tags
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
    , manager(manager)
    , position(position)
    , department(department)
    , access_role(access_role)
    , other_role(other_role)
    , status(status)
    , other_status(other_status)
    , sales_territory(sales_territory)
    , last_login_date(last_login_date)
    , last_action_date(last_action_date)
    , time_zone(time_zone)
    , leads(std::move(leads))
    , commission_rate(commission_rate)
    , monthly_quota(std::move(monthly_quota))
    , tasks(std::move(tasks))
    , documents(std::move(documents))
    , base_salary(base_salary)
    , skills(std::move(skills))
    , performance_score(performance_score)
    , direct_reports(std::move(direct_reports))
    , next_review_date(next_review_date)
    , hire_date(hire_date)
    , dismissal_date(dismissal_date)
    , is_active(false)
{
}

auto InternalEmployee::getManager() const -> const InternalEmployeePtr& { return this->manager; }
auto InternalEmployee::getPosition() const -> const OptionalStr& { return this->position; }
auto InternalEmployee::getDepartment() const -> const OptionalStr& { return this->department; }
auto InternalEmployee::getAccessRole() const -> AccessRole { return this->access_role; }
auto InternalEmployee::getOtherRole() const -> const OptionalStr& { return this->other_role; }
auto InternalEmployee::getStatus() const -> EmployeeStatus { return this->status; }
auto InternalEmployee::getOtherStatus() const -> const OptionalStr& { return this->other_status; }
auto InternalEmployee::getSalesTerritory() const -> const OptionalStr&
{
    return this->sales_territory;
}
auto InternalEmployee::getLastLoginDate() const -> const DatePtr& { return this->last_login_date; }
auto InternalEmployee::getLastActionDate() const -> const DatePtr&
{
    return this->last_action_date;
}
auto InternalEmployee::getTimeZone() const -> int { return this->time_zone; }
auto InternalEmployee::getIsActive() const -> bool { return this->is_active; }
auto InternalEmployee::getNextReviewDate() const -> const DatePtr&
{
    return this->next_review_date;
}
auto InternalEmployee::getHireDate() const -> const std::shared_ptr<Date>&
{
    return this->hire_date;
}
auto InternalEmployee::getDismissalDate() const -> const std::shared_ptr<Date>&
{
    return this->dismissal_date;
}
auto InternalEmployee::getManagedDeals() const -> const std::vector<DealPtr>&
{
    return this->managed_deals;
}
auto InternalEmployee::getProposedOffers() const -> const std::vector<OfferPtr>&
{
    return this->proposed_offers;
}
auto InternalEmployee::getCommissionRate() const -> const std::optional<double>&
{
    return this->commission_rate;
}
auto InternalEmployee::getBaseSalary() const -> const MoneyPtr& { return this->base_salary; }
auto InternalEmployee::getPerformanceScore() const -> const std::optional<double>&
{
    return this->performance_score;
}
auto InternalEmployee::getLeads() const -> const std::vector<ClientPtr>& { return this->leads; }
auto InternalEmployee::getMonthlyQuota() const -> const std::vector<Money>&
{
    return this->monthly_quota;
}
auto InternalEmployee::getTasks() const -> const std::vector<TaskPtr>& { return this->tasks; }
auto InternalEmployee::getDocuments() const -> const std::vector<DocumentPtr>&
{
    return this->documents;
}
auto InternalEmployee::getSkills() const -> const std::vector<std::string>& { return this->skills; }
auto InternalEmployee::getDirectReports() const -> const std::vector<InternalEmployeePtr>&
{
    return this->direct_reports;
}
bool InternalEmployee::setManager(
    const InternalEmployeePtr& manager, const InternalEmployeePtr& changer
)
{
    if (this->manager != manager) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->manager),
            PTR_TO_OPTIONAL(manager),
            InternalEmployeeFields::Manager,
            this->manager ? ChangeLog::FieldType::InternalEmployee : ChangeLog::FieldType::null,
            manager ? ChangeLog::FieldType::InternalEmployee : ChangeLog::FieldType::null,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->manager = manager;
        return true;
    }
    return false;
}

bool InternalEmployee::setPosition(const OptionalStr& position, const InternalEmployeePtr& changer)
{
    if (this->position != position) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->position),
            OPTIONAL_STR_TO_VALUE(position),
            InternalEmployeeFields::Position,
            this->position ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            position ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change,
            update
        ));
        this->position = position;
        this->updateAt(update);
        return true;
    }
    return false;
}

bool InternalEmployee::setDepartment(
    const OptionalStr& department, const InternalEmployeePtr& changer
)
{
    if (this->department != department) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->department),
            OPTIONAL_STR_TO_VALUE(department),
            InternalEmployeeFields::Department,
            this->department ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            department ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->department = department;
        return true;
    }
    return false;
}

bool InternalEmployee::setAccessRole(const AccessRole role, const InternalEmployeePtr& changer)
{
    if (this->access_role != role) {
        Date update   = Date();
        auto old_vale = this->other_role
                          ? std::make_optional<ChangeLog::ValueVariant>(
                                std::make_shared<std::string>(this->other_role.value())
                            )
                          : std::make_optional(this->access_role);
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::move(old_vale),
            std::make_optional(role),
            InternalEmployeeFields::Role,
            this->other_role ? ChangeLog::FieldType::String : ChangeLog::FieldType::AccessLevel,
            ChangeLog::FieldType::AccessLevel,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->access_role = role;
        this->other_role  = std::nullopt;
        return true;
    }
    return false;
}

bool InternalEmployee::setOtherRole(
    const OptionalStr& other_role, const InternalEmployeePtr& changer
)
{
    if (this->other_role != other_role) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->other_role ? std::make_optional<ChangeLog::ValueVariant>(
                                   std::make_shared<std::string>(this->other_role.value())
                               )
                             : std::make_optional<ChangeLog::ValueVariant>(this->access_role),
            OPTIONAL_STR_TO_VALUE(other_role),
            InternalEmployeeFields::Role,
            this->other_role ? ChangeLog::FieldType::String : ChangeLog::FieldType::AccessLevel,
            other_role ? ChangeLog::FieldType::String : ChangeLog::FieldType::AccessLevel,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->access_role = AccessRole::other;
        this->other_role  = other_role;
        return true;
    }
    return false;
}

bool InternalEmployee::setStatus(const EmployeeStatus status, const InternalEmployeePtr& changer)
{
    if (this->status != status) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->other_status ? std::make_optional<ChangeLog::ValueVariant>(
                                     std::make_shared<std::string>(this->other_status.value())
                                 )
                               : std::make_optional(this->status),
            std::make_optional(status),
            InternalEmployeeFields::Status,
            this->other_status ? ChangeLog::FieldType::String
                               : ChangeLog::FieldType::EmployeeStatus,
            ChangeLog::FieldType::EmployeeStatus,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->status       = status;
        this->other_status = std::nullopt;
        return true;
    }
    return false;
}

bool InternalEmployee::setOtherStatus(const OptionalStr& status, const InternalEmployeePtr& changer)
{
    if (this->other_status != status) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->other_status ? std::make_optional<ChangeLog::ValueVariant>(
                                     std::make_shared<std::string>(this->other_status.value())
                                 )
                               : std::make_optional<ChangeLog::ValueVariant>(this->status),
            OPTIONAL_STR_TO_VALUE(status),
            InternalEmployeeFields::Status,
            this->other_status ? ChangeLog::FieldType::String
                               : ChangeLog::FieldType::EmployeeStatus,
            status ? ChangeLog::FieldType::String : ChangeLog::FieldType::EmployeeStatus,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->other_status = status;
        this->status       = EmployeeStatus::other;
        return true;
    }
    return false;
}

bool InternalEmployee::setSalesTerritory(
    const OptionalStr& sales_territory, const InternalEmployeePtr& changer
)
{
    if (this->sales_territory != sales_territory) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->sales_territory),
            OPTIONAL_STR_TO_VALUE(sales_territory),
            InternalEmployeeFields::SalesTerritory,
            this->sales_territory ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            sales_territory ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->sales_territory = sales_territory;
        return true;
    }
    return false;
}

bool InternalEmployee::setLastLoginDate(
    const DatePtr& last_login_date, const InternalEmployeePtr& changer
)
{
    bool changed = true;
    if (this->last_login_date == nullptr || last_login_date == nullptr) {
        if (this->last_login_date == last_login_date) changed = false;
    } else if (*this->last_login_date == *last_login_date) {
        changed = false;
    }

    if (!changed) return false;

    Date update = Date();
    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->last_login_date),
        PTR_TO_OPTIONAL(last_login_date),
        InternalEmployeeFields::LastLoginDate,
        this->last_login_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        last_login_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change,
        update
    ));
    this->updateAt(update);
    this->last_login_date = last_login_date;
    return true;
}

bool InternalEmployee::setLastActionDate(
    const DatePtr& last_action_date, const InternalEmployeePtr& changer
)
{
    bool changed = true;
    if (this->last_action_date == nullptr || last_action_date == nullptr) {
        if (this->last_action_date == last_action_date) changed = false;
    } else if (*this->last_action_date == *last_action_date) {
        changed = false;
    }

    if (!changed) return false;

    Date update = Date();
    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->last_action_date),
        PTR_TO_OPTIONAL(last_action_date),
        InternalEmployeeFields::LastActionDate,
        this->last_action_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        last_action_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change,
        update
    ));
    this->updateAt(update);
    this->last_action_date = last_action_date;
    return true;
}

bool InternalEmployee::setIsActive(bool is_active, const InternalEmployeePtr& changer)
{
    if (this->is_active != is_active) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->is_active),
            std::make_optional(is_active),
            InternalEmployeeFields::IsActive,
            ChangeLog::FieldType::Bool,
            ChangeLog::FieldType::Bool,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->is_active = is_active;
        return true;
    }
    return false;
}

bool InternalEmployee::setNextReviewDate(
    const DatePtr& next_review_date, const InternalEmployeePtr& changer
)
{
    bool changed = true;
    if (this->next_review_date == nullptr || next_review_date == nullptr) {
        if (this->next_review_date == next_review_date) changed = false;
    } else if (*this->next_review_date == *next_review_date) {
        changed = false;
    }

    if (!changed) return false;

    Date update = Date();
    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->next_review_date),
        PTR_TO_OPTIONAL(next_review_date),
        InternalEmployeeFields::NextReviewDate,
        this->next_review_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        next_review_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change,
        update
    ));
    this->updateAt(update);
    this->next_review_date = next_review_date;
    return true;
}

bool InternalEmployee::setTimeZone(const int time_zone, const InternalEmployeePtr& changer)
{
    if (this->time_zone != time_zone) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->time_zone),
            std::make_optional(time_zone),
            InternalEmployeeFields::TimeZone,
            ChangeLog::FieldType::Int,
            ChangeLog::FieldType::Int,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->time_zone = time_zone;
        return true;
    }
    return false;
}

bool InternalEmployee::setCommissionRate(
    const std::optional<double>& commission_rate, const InternalEmployeePtr& changer
)
{
    if (this->commission_rate != commission_rate) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->commission_rate,
            commission_rate,
            InternalEmployeeFields::CommissionRate,
            this->commission_rate == std::nullopt ? ChangeLog::FieldType::null
                                                  : ChangeLog::FieldType::Double,
            commission_rate == std::nullopt ? ChangeLog::FieldType::null
                                            : ChangeLog::FieldType::Double,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->commission_rate = commission_rate;
        return true;
    }
    return false;
}

bool InternalEmployee::setBaseSalary(
    const MoneyPtr& base_salary, const InternalEmployeePtr& changer
)
{
    bool changed = true;
    if (this->base_salary == nullptr || base_salary == nullptr) {
        if (this->base_salary == base_salary) changed = false;
    } else if (*this->base_salary == *base_salary) {
        changed = false;
    }

    if (!changed) return false;

    Date update = Date();
    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->base_salary),
        PTR_TO_OPTIONAL(base_salary),
        InternalEmployeeFields::BaseSalary,
        this->base_salary ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        base_salary ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        ChangeLog::Action::Change,
        update
    ));
    this->updateAt(update);
    this->base_salary = base_salary;
    return true;
}

bool InternalEmployee::setPerformanceScore(
    const std::optional<double>& performance_score, const InternalEmployeePtr& changer
)
{
    if (this->performance_score != performance_score) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->performance_score,
            performance_score,
            InternalEmployeeFields::PerformanceScore,
            this->performance_score ? ChangeLog::FieldType::Double : ChangeLog::FieldType::null,
            performance_score ? ChangeLog::FieldType::Double : ChangeLog::FieldType::null,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->performance_score = performance_score;
        return true;
    }
    return false;
}

bool InternalEmployee::setHireDate(const DatePtr& hire_date, const InternalEmployeePtr& changer)
{
    bool changed = true;
    if (this->hire_date == nullptr || hire_date == nullptr) {
        if (this->hire_date == hire_date) changed = false;
    } else if (*this->hire_date == *hire_date) {
        changed = false;
    }

    if (!changed) return false;

    Date update = Date();
    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->hire_date),
        PTR_TO_OPTIONAL(hire_date),
        InternalEmployeeFields::HireDate,
        this->hire_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        hire_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change,
        update
    ));
    this->updateAt(update);
    this->hire_date = hire_date;
    return true;
}

bool InternalEmployee::setDismissalDate(
    const DatePtr& dismissal_date, const InternalEmployeePtr& changer
)
{
    bool changed = true;
    if (this->dismissal_date == nullptr || dismissal_date == nullptr) {
        if (this->dismissal_date == dismissal_date) changed = false;
    } else if (*this->dismissal_date == *dismissal_date) {
        changed = false;
    }

    if (!changed) return false;

    Date update = Date();
    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->dismissal_date),
        PTR_TO_OPTIONAL(dismissal_date),
        InternalEmployeeFields::DismissalDate,
        this->dismissal_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        dismissal_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change,
        update
    ));
    this->updateAt(update);
    this->dismissal_date = dismissal_date;
    return true;
}

bool InternalEmployee::addManagerDeal(const DealPtr& deal, const InternalEmployeePtr& changer)
{
    if (std::find(this->managed_deals.begin(), this->managed_deals.end(), deal) ==
        this->managed_deals.end()) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(deal),
            InternalEmployeeFields::ManagerDeals,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Deal,
            ChangeLog::Action::Add,
            update
        ));
        this->updateAt(update);
        this->addRelatedDeals(deal, changer, update);
        this->managed_deals.push_back(deal);
        return true;
    }
    return false;
}

bool InternalEmployee::delManagerDeal(size_t index, const InternalEmployeePtr& changer)
{
    if (this->managed_deals.size() > index) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->managed_deals[index]),
            std::nullopt,
            InternalEmployeeFields::ManagerDeals,
            ChangeLog::FieldType::Deal,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->updateAt(update);
        this->delRelatedDeals(this->managed_deals[index], changer, update);
        this->managed_deals.erase(this->managed_deals.begin() + index);
        return true;
    }
    return false;
}

bool InternalEmployee::addProposedOffer(const OfferPtr& offer, const InternalEmployeePtr& changer)
{
    if (std::find(this->proposed_offers.begin(), this->proposed_offers.end(), offer) ==
        this->proposed_offers.end()) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(offer),
            InternalEmployeeFields::ProposedOffers,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Offer,
            ChangeLog::Action::Add,
            update
        ));
        this->updateAt(update);
        this->proposed_offers.push_back(offer);
        return true;
    }
    return false;
}

bool InternalEmployee::delProposedOffer(size_t index, const InternalEmployeePtr& changer)
{
    if (this->proposed_offers.size() > index) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->proposed_offers[index]),
            std::nullopt,
            InternalEmployeeFields::ProposedOffers,
            ChangeLog::FieldType::Offer,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->updateAt(update);
        this->proposed_offers.erase(this->proposed_offers.begin() + index);
        return true;
    }
    return false;
}

bool InternalEmployee::addLead(const ClientPtr& lead, const InternalEmployeePtr& changer)
{
    if (std::find(this->leads.begin(), this->leads.end(), lead) == this->leads.end()) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(lead),
            InternalEmployeeFields::Leads,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Client,
            ChangeLog::Action::Add,
            update
        ));
        this->updateAt(update);
        this->leads.push_back(lead);
        return true;
    }
    return false;
}

bool InternalEmployee::delLead(size_t index, const InternalEmployeePtr& changer)
{
    if (this->leads.size() > index) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->leads[index]),
            std::nullopt,
            InternalEmployeeFields::Leads,
            ChangeLog::FieldType::Client,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->updateAt(update);
        this->leads.erase(this->leads.begin() + index);
        return true;
    }
    return false;
}

bool InternalEmployee::addMonthlyQuota(const Money& quota, const InternalEmployeePtr& changer)
{
    if (std::find(this->monthly_quota.begin(), this->monthly_quota.end(), quota) ==
        this->monthly_quota.end()) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(std::make_shared<Money>(quota)),
            InternalEmployeeFields::MonthlyQuota,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Money,
            ChangeLog::Action::Add,
            update
        ));
        this->updateAt(update);
        this->monthly_quota.push_back(quota);
        return true;
    }
    return false;
}

bool InternalEmployee::delMonthlyQuota(size_t index, const InternalEmployeePtr& changer)
{
    if (this->monthly_quota.size() > index) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<Money>(this->monthly_quota[index])),
            std::nullopt,
            InternalEmployeeFields::MonthlyQuota,
            ChangeLog::FieldType::Money,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->updateAt(update);
        this->monthly_quota.erase(this->monthly_quota.begin() + index);
        return true;
    }
    return false;
}

bool InternalEmployee::addTask(const TaskPtr& task, const InternalEmployeePtr& changer)
{
    if (std::find(this->tasks.begin(), this->tasks.end(), task) == this->tasks.end()) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(task),
            InternalEmployeeFields::Tasks,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Task,
            ChangeLog::Action::Add,
            update
        ));
        this->updateAt(update);
        this->tasks.push_back(task);
        return true;
    }
    return false;
}

bool InternalEmployee::delTask(size_t index, const InternalEmployeePtr& changer)
{
    if (this->tasks.size() > index) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->tasks[index]),
            std::nullopt,
            InternalEmployeeFields::Tasks,
            ChangeLog::FieldType::Task,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->updateAt(update);
        this->tasks.erase(this->tasks.begin() + index);
        return true;
    }
    return false;
}

bool InternalEmployee::addDocument(const DocumentPtr& document, const InternalEmployeePtr& changer)
{
    if (std::find(this->documents.begin(), this->documents.end(), document) ==
        this->documents.end()) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(document),
            InternalEmployeeFields::Documents,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Document,
            ChangeLog::Action::Add,
            update
        ));
        this->updateAt(update);
        this->documents.push_back(document);
        return true;
    }
    return false;
}

bool InternalEmployee::delDocument(size_t index, const InternalEmployeePtr& changer)
{
    if (this->documents.size() > index) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->documents[index]),
            std::nullopt,
            InternalEmployeeFields::Documents,
            ChangeLog::FieldType::Document,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->updateAt(update);
        this->documents.erase(this->documents.begin() + index);
        return true;
    }
    return false;
}

bool InternalEmployee::addSkill(const std::string& skill, const InternalEmployeePtr& changer)
{
    if (std::find(this->skills.begin(), this->skills.end(), skill) == this->skills.end()) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(std::make_shared<std::string>(skill)),
            InternalEmployeeFields::Skills,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Add,
            update
        ));
        this->updateAt(update);
        this->skills.push_back(skill);
        return true;
    }
    return false;
}

bool InternalEmployee::delSkill(size_t index, const InternalEmployeePtr& changer)
{
    if (this->skills.size() > index) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<std::string>(this->skills[index])),
            std::nullopt,
            InternalEmployeeFields::Skills,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->updateAt(update);
        this->skills.erase(this->skills.begin() + index);
        return true;
    }
    return false;
}

bool InternalEmployee::addDirectReport(
    const InternalEmployeePtr& report, const InternalEmployeePtr& changer
)
{
    if (std::find(this->direct_reports.begin(), this->direct_reports.end(), report) ==
        this->direct_reports.end()) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(report),
            InternalEmployeeFields::DirectReports,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::InternalEmployee,
            ChangeLog::Action::Add,
            update
        ));
        this->updateAt(update);
        this->direct_reports.push_back(report);
        return true;
    }
    return false;
}

bool InternalEmployee::delDirectReport(size_t index, const InternalEmployeePtr& changer)
{
    if (this->direct_reports.size() > index) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->direct_reports[index]),
            std::nullopt,
            InternalEmployeeFields::DirectReports,
            ChangeLog::FieldType::InternalEmployee,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->updateAt(update);
        this->direct_reports.erase(this->direct_reports.begin() + index);
        return true;
    }
    return false;
}