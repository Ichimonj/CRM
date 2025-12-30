#include "external_employee.hpp"

#include "change_log.hpp"
ExternalEmployee::ExternalEmployee(
    const BigUint&     id,
    const std::string& name,
    const std::string& surname,
    const OptionalStr& patronymic
)
    : Person(id, name, surname, patronymic)
    , access_role(AccessRole::ReadOnly)
    , status(EmployeeStatus::other)
    , time_zone(0)
{
}

ExternalEmployee::ExternalEmployee(
    const BigUint&                       id,
    const std::string&                   name,
    const std::string&                   surname,
    const OptionalStr&                   patronymic,
    const OptionalStr&                   preferred_language,
    const DatePtr&                       birthday,
    const PhoneNumberPtr&                phone_number,
    const AddressPtr&                    address,
    const OptionalStr&                   email,
    const Gender&                        gender,
    const ExternalCompanyPtr&            company,
    const OptionalStr&                   job_title,
    const OptionalStr&                   department,
    const EmployeeStatus&                status,
    const OptionalStr&                   other_status,
    const AccessRole&                    access_role,
    const OptionalStr&                   other_role,
    const InteractionPtr&                current_interaction,
    const DatePtr&                       last_contact_date,
    int                                  time_zone,
    const OptionalStr&                   preferred_contact_time,
    const std::optional<InfluenceLevel>& decision_influence,
    const std::optional<double>&         influence_score,
    const MoneyPtr&                      budget_authority,
    const MoneyPtr&                      salary,
    std::vector<SocialNetwork>           social_networks,
    std::vector<PhoneNumber>             more_phone_numbers,
    std::vector<Address>                 more_addresses,
    std::vector<std::string>             more_emails,
    std::vector<DocumentPtr>             other_documents,
    std::vector<FileMetadataPtr>         other_files,
    std::vector<InteractionPtr>          interaction_history,
    std::vector<std::string>             tags,
    std::vector<Note>                    notes,
    std::vector<std::string>             pain_points,
    std::vector<DealPtr>                 assigned_deals,
    std::vector<DealPtr>                 completed_deals,
    std::vector<TaskPtr>                 assigned_tasks,
    std::vector<TaskPtr>                 completed_tasks
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
    , company(company)
    , job_title(job_title)
    , department(department)
    , status(status)
    , other_status(other_status)
    , access_role(access_role)
    , other_role(other_role)
    , current_interaction(current_interaction)
    , last_contact_date(last_contact_date)
    , time_zone(time_zone)
    , preferred_contact_time(preferred_contact_time)
    , decision_influence(decision_influence)
    , influence_score(influence_score)
    , budget_authority(budget_authority)
    , salary(salary)
    , pain_points(pain_points)
    , assigned_deals(assigned_deals)
    , completed_deals(completed_deals)
    , assigned_tasks(assigned_tasks)
    , completed_tasks(completed_tasks)
{
}

auto ExternalEmployee::getCompany() const -> const ExternalCompanyPtr& { return this->company; }
auto ExternalEmployee::getJobTitle() const -> const OptionalStr& { return this->job_title; }
auto ExternalEmployee::getDepartment() const -> const OptionalStr& { return this->department; }
auto ExternalEmployee::getStatus() const -> EmployeeStatus { return this->status; }
auto ExternalEmployee::getOtherStatus() const -> const OptionalStr& { return this->other_status; }
auto ExternalEmployee::getAccessRole() const -> AccessRole { return this->access_role; }
auto ExternalEmployee::getOtherRole() const -> const OptionalStr& { return this->other_role; }
auto ExternalEmployee::getCurrentInteraction() const -> const InteractionPtr&
{
    return this->current_interaction;
}
auto ExternalEmployee::getLastContactDate() const -> const DatePtr&
{
    return this->last_contact_date;
}
auto ExternalEmployee::getTimeZone() const -> int { return this->time_zone; }
auto ExternalEmployee::getPreferredContactTime() const -> const OptionalStr&
{
    return this->preferred_contact_time;
}

auto ExternalEmployee::getDecisionInfluence() const -> const std::optional<InfluenceLevel>&
{
    return this->decision_influence;
}
auto ExternalEmployee::getInfluenceScore() const -> const std::optional<double>&
{
    return this->influence_score;
}
auto ExternalEmployee::getBudgetAuthority() const -> const MoneyPtr&
{
    return this->budget_authority;
}
auto ExternalEmployee::getSalary() const -> const MoneyPtr& { return this->salary; }
auto ExternalEmployee::getPainPoints() const -> const std::vector<std::string>&
{
    return this->pain_points;
}
auto ExternalEmployee::getAssignedDeals() const -> const std::vector<DealPtr>&
{
    return this->assigned_deals;
}
auto ExternalEmployee::getCompletedDeals() const -> const std::vector<DealPtr>&
{
    return this->completed_deals;
}
auto ExternalEmployee::getAssignedTasks() const -> const std::vector<TaskPtr>&
{
    return this->assigned_tasks;
}
auto ExternalEmployee::getCompletedTasks() const -> const std::vector<TaskPtr>&
{
    return this->completed_tasks;
}

bool ExternalEmployee::setCompany(
    const ExternalCompanyPtr& company, const InternalEmployeePtr& changer
)
{
    if (this->company != company) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->company),
            PTR_TO_OPTIONAL(company),
            ExternalEmployeeFields::Company,
            this->company ? ChangeLog::FieldType::Company : ChangeLog::FieldType::null,
            company ? ChangeLog::FieldType::Company : ChangeLog::FieldType::null,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->company = company;
        return true;
    }
    return false;
}

bool ExternalEmployee::setJobTitle(const OptionalStr& title, const InternalEmployeePtr& changer)
{
    if (this->job_title != title) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->job_title),
            OPTIONAL_STR_TO_VALUE(title),
            ExternalEmployeeFields::JobTitle,
            this->job_title ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            title ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->job_title = title;
        return true;
    }
    return false;
}

bool ExternalEmployee::setDepartment(
    const OptionalStr& department, const InternalEmployeePtr& changer
)
{
    if (this->department != department) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->department),
            OPTIONAL_STR_TO_VALUE(department),
            ExternalEmployeeFields::Department,
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

bool ExternalEmployee::setStatus(const EmployeeStatus status, const InternalEmployeePtr& changer)
{
    if (this->status != status) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->other_status ? std::make_optional<ChangeLog::ValueVariant>(
                                     std::make_shared<std::string>(this->other_status.value())
                                 )
                               : std::make_optional<ChangeLog::ValueVariant>(this->status),
            std::make_optional<ChangeLog::ValueVariant>(status),
            ExternalEmployeeFields::Status,
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

bool ExternalEmployee::setOtherStatus(const OptionalStr& status, const InternalEmployeePtr& changer)
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
            ExternalEmployeeFields::Status,
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

bool ExternalEmployee::setAccessRole(
    const AccessRole access_role, const InternalEmployeePtr& changer
)
{
    if (this->access_role != access_role) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->other_role ? std::make_optional<ChangeLog::ValueVariant>(
                                   std::make_shared<std::string>(this->other_role.value())
                               )
                             : std::make_optional<ChangeLog::ValueVariant>(this->access_role),
            std::make_optional<ChangeLog::ValueVariant>(access_role),
            ExternalEmployeeFields::Role,
            this->other_role ? ChangeLog::FieldType::String : ChangeLog::FieldType::AccessLevel,
            ChangeLog::FieldType::AccessLevel,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->access_role = access_role;
        this->other_role  = std::nullopt;
        return true;
    }
    return false;
}

bool ExternalEmployee::setOtherRole(
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
            ExternalEmployeeFields::Role,
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

bool ExternalEmployee::setCurrentInteraction(
    const InteractionPtr& current_interaction, const InternalEmployeePtr& changer
)
{
    if (this->current_interaction != current_interaction) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->current_interaction),
            PTR_TO_OPTIONAL(current_interaction),
            ExternalEmployeeFields::CurrentInteraction,
            this->current_interaction ? ChangeLog::FieldType::BaseInteraction
                                      : ChangeLog::FieldType::null,
            current_interaction ? ChangeLog::FieldType::BaseInteraction
                                : ChangeLog::FieldType::null,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->current_interaction = current_interaction;
        return true;
    }
    return false;
}

bool ExternalEmployee::setLastContactDate(
    const DatePtr& last_contact_date, const InternalEmployeePtr& changer
)
{
    if (this->last_contact_date == nullptr || last_contact_date == nullptr) {
        if (this->last_contact_date == last_contact_date) return false;
    } else if (*this->last_contact_date == *last_contact_date) {
        return false;
    }
    Date update = Date();

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->last_contact_date),
        PTR_TO_OPTIONAL(last_contact_date),
        ExternalEmployeeFields::LastContactDate,
        this->last_contact_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        last_contact_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change,
        update
    ));
    this->updateAt(update);
    this->last_contact_date = last_contact_date;
    return true;
}

bool ExternalEmployee::setTimeZone(const int time_zone, const InternalEmployeePtr& changer)
{
    if (this->time_zone != time_zone) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->time_zone),
            std::make_optional<ChangeLog::ValueVariant>(time_zone),
            ExternalEmployeeFields::TimeZone,
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

bool ExternalEmployee::setPreferredContactTime(
    const OptionalStr& preferred_contact_time, const InternalEmployeePtr& changer
)
{
    if (this->preferred_contact_time != preferred_contact_time) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->preferred_contact_time),
            OPTIONAL_STR_TO_VALUE(preferred_contact_time),
            ExternalEmployeeFields::PreferredContactTime,
            this->preferred_contact_time ? ChangeLog::FieldType::String
                                         : ChangeLog::FieldType::null,
            preferred_contact_time ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->preferred_contact_time = preferred_contact_time;
        return true;
    }
    return false;
}

bool ExternalEmployee::setDecisionInfluence(
    const std::optional<InfluenceLevel>& decision_influence, const InternalEmployeePtr& changer
)
{
    if (this->decision_influence != decision_influence) {
        Date                                   update = Date();
        std::optional<ChangeLog::ValueVariant> old_value =
            this->decision_influence
                ? std::make_optional<ChangeLog::ValueVariant>(this->decision_influence.value())
                : std::nullopt;

        std::optional<ChangeLog::ValueVariant> new_value =
            decision_influence
                ? std::make_optional<ChangeLog::ValueVariant>(decision_influence.value())
                : std::nullopt;

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::move(old_value),
            std::move(new_value),
            ExternalEmployeeFields::DecisionInfluence,
            old_value ? ChangeLog::FieldType::InfluenceLevel : ChangeLog::FieldType::null,
            new_value ? ChangeLog::FieldType::InfluenceLevel : ChangeLog::FieldType::null,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->decision_influence = decision_influence;
        return true;
    }
    return false;
}

bool ExternalEmployee::setInfluenceScore(
    const std::optional<double>& influence_score, const InternalEmployeePtr& changer
)
{
    if (this->influence_score != influence_score) {
        Date                                   update = Date();

        std::optional<ChangeLog::ValueVariant> old_value =
            this->influence_score
                ? std::make_optional<ChangeLog::ValueVariant>(this->influence_score.value())
                : std::nullopt;
        std::optional<ChangeLog::ValueVariant> new_value =
            influence_score ? std::make_optional<ChangeLog::ValueVariant>(influence_score.value())
                            : std::nullopt;

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::move(old_value),
            std::move(new_value),
            ExternalEmployeeFields::InfluenceScore,
            old_value ? ChangeLog::FieldType::Double : ChangeLog::FieldType::null,
            new_value ? ChangeLog::FieldType::Double : ChangeLog::FieldType::null,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->influence_score = influence_score;
        return true;
    }
    return false;
}

bool ExternalEmployee::setBudgetAuthority(
    const MoneyPtr& budget_authority, const InternalEmployeePtr& changer
)
{
    if (this->budget_authority == nullptr || budget_authority == nullptr) {
        if (this->budget_authority == budget_authority) return false;
    } else if (*this->budget_authority == *budget_authority) {
        return false;
    }
    Date update = Date();

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->budget_authority),
        PTR_TO_OPTIONAL(budget_authority),
        ExternalEmployeeFields::BudgetAuthority,
        this->budget_authority ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        budget_authority ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        ChangeLog::Action::Change,
        update
    ));
    this->updateAt(update);
    this->budget_authority = budget_authority;
    return true;
}

bool ExternalEmployee::setSalary(const MoneyPtr& salary, const InternalEmployeePtr& changer)
{
    if (this->salary == nullptr || salary == nullptr) {
        if (this->salary == salary) return false;
    } else if (*this->salary == *salary) {
        return false;
    }
    Date update = Date();

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->salary),
        PTR_TO_OPTIONAL(salary),
        ExternalEmployeeFields::Salary,
        this->salary ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        salary ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        ChangeLog::Action::Change,
        update
    ));
    this->updateAt(update);
    this->salary = salary;
    return true;
}

bool ExternalEmployee::addPainPoint(
    const std::string& pain_point, const InternalEmployeePtr& changer
)
{
    if (std::find(this->pain_points.begin(), this->pain_points.end(), pain_point) ==
        this->pain_points.end()) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(pain_point)),
            ExternalEmployeeFields::PainPoints,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Add,
            update
        ));
        this->updateAt(update);
        this->pain_points.push_back(pain_point);
        return true;
    }
    return false;
}

bool ExternalEmployee::delPainPoint(size_t index, const InternalEmployeePtr& changer)
{
    if (index < this->pain_points.size()) {
        Date update = Date();
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<std::string>(this->pain_points[index])
            ),
            std::nullopt,
            ExternalEmployeeFields::PainPoints,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->updateAt(update);
        this->pain_points.erase(this->pain_points.begin() + index);
        return true;
    }
    return false;
}

bool ExternalEmployee::addAssignedDeal(
    const DealPtr& assigned_deal, const InternalEmployeePtr& changer
)
{
    if (std::find(this->assigned_deals.begin(), this->assigned_deals.end(), assigned_deal) ==
        this->assigned_deals.end()) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(assigned_deal),
            ExternalEmployeeFields::AssignedDeals,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Deal,
            ChangeLog::Action::Add,
            update
        ));
        this->updateAt(update);
        this->addRelatedDeals(assigned_deal, changer, update);
        this->assigned_deals.push_back(assigned_deal);
        return true;
    }
    return false;
}

bool ExternalEmployee::delAssignedDeal(size_t index, const InternalEmployeePtr& changer)
{
    if (index < this->assigned_deals.size()) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->assigned_deals[index]),
            std::nullopt,
            ExternalEmployeeFields::AssignedDeals,
            ChangeLog::FieldType::Deal,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->updateAt(update);
        this->delRelatedDeals(this->assigned_deals[index], changer, update);
        this->assigned_deals.erase(this->assigned_deals.begin() + index);
        return true;
    }
    return false;
}

bool ExternalEmployee::addCompletedDeal(
    const DealPtr& completed_deal, const InternalEmployeePtr& changer
)
{
    if (std::find(this->completed_deals.begin(), this->completed_deals.end(), completed_deal) ==
        this->completed_deals.end()) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(completed_deal),
            ExternalEmployeeFields::CompletedDeals,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Deal,
            ChangeLog::Action::Add,
            update
        ));
        this->updateAt(update);
        this->addRelatedDeals(completed_deal, changer, update);
        this->completed_deals.push_back(completed_deal);
        return true;
    }
    return false;
}

bool ExternalEmployee::delCompletedDeal(size_t index, const InternalEmployeePtr& changer)
{
    if (index < this->completed_deals.size()) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->completed_deals[index]),
            std::nullopt,
            ExternalEmployeeFields::CompletedDeals,
            ChangeLog::FieldType::Deal,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->updateAt(update);
        this->delRelatedDeals(this->completed_deals[index], changer, update);
        this->completed_deals.erase(this->completed_deals.begin() + index);
        return true;
    }
    return false;
}

bool ExternalEmployee::addAssignedTask(
    const TaskPtr& assigned_task, const InternalEmployeePtr& changer
)
{
    if (std::find(this->assigned_tasks.begin(), this->assigned_tasks.end(), assigned_task) ==
        this->assigned_tasks.end()) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(assigned_task),
            ExternalEmployeeFields::AssignedTasks,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Task,
            ChangeLog::Action::Add,
            update
        ));
        this->updateAt(update);
        this->assigned_tasks.push_back(assigned_task);
        return true;
    }
    return false;
}

bool ExternalEmployee::delAssignedTask(size_t index, const InternalEmployeePtr& changer)
{
    if (index < this->assigned_tasks.size()) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->assigned_tasks[index]),
            std::nullopt,
            ExternalEmployeeFields::AssignedTasks,
            ChangeLog::FieldType::Task,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->updateAt(update);
        this->assigned_tasks.erase(this->assigned_tasks.begin() + index);
        return true;
    }
    return false;
}

bool ExternalEmployee::addCompletedTask(
    const TaskPtr& completed_task, const InternalEmployeePtr& changer
)
{
    if (std::find(this->completed_tasks.begin(), this->completed_tasks.end(), completed_task) ==
        this->completed_tasks.end()) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(completed_task),
            ExternalEmployeeFields::CompletedTasks,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Task,
            ChangeLog::Action::Add,
            update
        ));
        this->updateAt(update);
        this->completed_tasks.push_back(completed_task);
        return true;
    }
    return false;
}

bool ExternalEmployee::delCompletedTask(size_t index, const InternalEmployeePtr& changer)
{
    if (index < this->completed_tasks.size()) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->completed_tasks[index]),
            std::nullopt,
            ExternalEmployeeFields::CompletedTasks,
            ChangeLog::FieldType::Task,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->updateAt(update);
        this->completed_tasks.erase(this->completed_tasks.begin() + index);
        return true;
    }
    return false;
}