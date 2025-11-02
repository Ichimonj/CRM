#include "external_employee.hpp"

#include "change_log.hpp"
ExternalEmployee::ExternalEmployee(
    const std::string& name, const std::string& surname, const OptionalStr& patronymic
)
    : Person(name, surname, patronymic), access_role(AccessLevel::ReadOnly), time_zone(0)
{
}

ExternalEmployee::ExternalEmployee(
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
    const AccessLevel&                   access_level,
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
    , access_role(access_level)
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
auto ExternalEmployee::getStatus() const -> const EmployeeStatus { return this->status; }
auto ExternalEmployee::getAccessLevel() const -> AccessLevel { return this->access_role; }
auto ExternalEmployee::getOtherRole() const -> const OptionalStr& { return this->other_role; }
auto ExternalEmployee::getCurrentInteraction() const -> const InteractionPtr&
{
    return this->current_interaction;
}
auto ExternalEmployee::getLastContactDate() const -> const DatePtr&
{
    return this->last_contact_date;
}
auto ExternalEmployee::getTimeZone() const -> const int { return this->time_zone; }
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

void ExternalEmployee::setCompany(
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
    }
}

void ExternalEmployee::setJobTitle(const OptionalStr& title, const InternalEmployeePtr& changer)
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
    }
}

void ExternalEmployee::setDepartment(
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
    }
}

void ExternalEmployee::setStatus(const EmployeeStatus status, const InternalEmployeePtr& changer)
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
    }
}

void ExternalEmployee::setOtherStatus(const OptionalStr& status, const InternalEmployeePtr& changer)
{
    if (this->other_status != status) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->other_status ? std::make_optional<ChangeLog::ValueVariant>(
                                     std::make_shared<std::string>(this->other_status.value())
                                 )
                               : std::make_optional(this->status),
            OPTIONAL_STR_TO_VALUE(status),
            ExternalEmployeeFields::Status,
            this->other_status ? ChangeLog::FieldType::String
                               : ChangeLog::FieldType::EmployeeStatus,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->other_status = status;
        this->status       = EmployeeStatus::other;
    }
}

void ExternalEmployee::setAccessRole(
    const AccessLevel access_role, const InternalEmployeePtr& changer
)
{
    if (this->access_role != access_role) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->other_role ? std::make_optional<ChangeLog::ValueVariant>(
                                   std::make_shared<std::string>(this->other_role.value())
                               )
                             : std::make_optional(this->access_role),
            std::make_optional(access_role),
            ExternalEmployeeFields::Role,
            this->other_role ? ChangeLog::FieldType::String : ChangeLog::FieldType::AccessLevel,
            ChangeLog::FieldType::AccessLevel,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->access_role = access_role;
        this->other_role  = std::nullopt;
    }
}

void ExternalEmployee::setOtherRole(
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
                             : std::make_optional(this->access_role),
            OPTIONAL_STR_TO_VALUE(other_role),
            ExternalEmployeeFields::OtherRole,
            this->other_role ? ChangeLog::FieldType::String : ChangeLog::FieldType::AccessLevel,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->access_role = AccessLevel::other;
        this->other_role  = other_role;
    }
}

void ExternalEmployee::setCurrentInteraction(
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
    }
}

void ExternalEmployee::setLastContactDate(
    const DatePtr& last_contact_date, const InternalEmployeePtr& changer
)
{
    if (this->last_contact_date == nullptr || last_contact_date == nullptr) {
        if (this->last_contact_date == last_contact_date) return;
    } else if (*this->last_contact_date == *last_contact_date) {
        return;
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
}

void ExternalEmployee::setTimeZone(const int time_zone, const InternalEmployeePtr& changer)
{
    if (this->time_zone != time_zone) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->time_zone),
            std::make_optional(time_zone),
            ExternalEmployeeFields::TimeZone,
            ChangeLog::FieldType::Int,
            ChangeLog::FieldType::Int,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->time_zone = time_zone;
    }
}

void ExternalEmployee::setPreferredContactTime(
    const OptionalStr& preferred_contact_time, const InternalEmployeePtr& changer
)
{
    if (this->preferred_contact_time != preferred_contact_time) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->preferred_contact_time),
            OPTIONAL_STR_TO_VALUE(preferred_contact_time),
            ExternalEmployeeFields::JobTitle,
            this->preferred_contact_time ? ChangeLog::FieldType::String
                                         : ChangeLog::FieldType::null,
            preferred_contact_time ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change,
            update
        ));
        this->updateAt(update);
        this->preferred_contact_time = preferred_contact_time;
    }
}

void ExternalEmployee::setDecisionInfluence(
    const std::optional<InfluenceLevel>& decision_influence, const InternalEmployeePtr& changer
)
{
    if (this->decision_influence != decision_influence) {
        Date          update    = Date();
        std::optional old_value = this->decision_influence
                                    ? std::make_optional(this->decision_influence.value())
                                    : std::nullopt;

        std::optional new_value =
            decision_influence ? std::make_optional(decision_influence.value()) : std::nullopt;

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
    }
}

void ExternalEmployee::setInfluenceScore(
    const std::optional<double>& influence_score, const InternalEmployeePtr& changer
)
{
    if (this->influence_score != influence_score) {
        Date          update = Date();

        std::optional old_value = this->influence_score
                                    ? std::make_optional(this->influence_score.value())
                                    : std::nullopt;
        std::optional new_value =
            influence_score ? std::make_optional(influence_score.value()) : std::nullopt;

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
    }
}

void ExternalEmployee::setBudgetAuthority(
    const MoneyPtr& budget_authority, const InternalEmployeePtr& changer
)
{
    if (this->budget_authority == nullptr || budget_authority == nullptr) {
        if (this->budget_authority == budget_authority) return;
    } else if (*this->budget_authority == *budget_authority) {
        return;
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
}

void ExternalEmployee::setSalary(const MoneyPtr& salary, const InternalEmployeePtr& changer)
{
    if (this->salary == nullptr || salary == nullptr) {
        if (this->salary == salary) return;
    } else if (*this->salary == *salary) {
        return;
    }
    Date          update = Date();

    std::optional old_value = this->salary ? std::make_optional(this->salary) : std::nullopt;
    std::optional new_value = salary ? std::make_optional(salary) : std::nullopt;

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        std::move(old_value),
        std::move(new_value),
        ExternalEmployeeFields::Salary,
        old_value ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        new_value ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        ChangeLog::Action::Change,
        update
    ));
    this->updateAt(update);
    this->salary = salary;
}

void ExternalEmployee::addPainPoint(
    const std::string& pain_point, const InternalEmployeePtr& changer
)
{
    if (std::find(this->pain_points.begin(), this->pain_points.end(), pain_point) ==
        this->pain_points.end()) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(std::make_shared<std::string>(pain_point)),
            ExternalEmployeeFields::PainPoints,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Add,
            update
        ));
        this->updateAt(update);
        this->pain_points.push_back(pain_point);
    }
}

void ExternalEmployee::delPainPoint(size_t index, const InternalEmployeePtr& changer)
{
    if (index < this->pain_points.size()) {
        Date        update             = Date();
        std::string removed_pain_point = this->pain_points[index];
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<std::string>(removed_pain_point)),
            std::nullopt,
            ExternalEmployeeFields::PainPoints,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->updateAt(update);
        this->pain_points.erase(this->pain_points.begin() + index);
    }
}

void ExternalEmployee::addAssignedDeal(
    const DealPtr& assigned_deal, const InternalEmployeePtr& changer
)
{
    if (std::find(this->assigned_deals.begin(), this->assigned_deals.end(), assigned_deal) !=
        this->assigned_deals.end()) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(assigned_deal),
            ExternalEmployeeFields::AssignedDeals,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Deal,
            ChangeLog::Action::Add,
            update
        ));
        this->updateAt(update);
        this->addRelatedDeals(assigned_deal, changer, update);
        this->assigned_deals.push_back(assigned_deal);
    }
}

void ExternalEmployee::delAssignedDeal(size_t index, const InternalEmployeePtr& changer)
{
    if (index < this->assigned_deals.size()) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->assigned_deals[index]),
            std::nullopt,
            ExternalEmployeeFields::AssignedDeals,
            ChangeLog::FieldType::Deal,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->updateAt(update);
        this->addRelatedDeals(this->assigned_deals[index], changer, update);
        this->assigned_deals.erase(this->assigned_deals.begin() + index);
    }
}

void ExternalEmployee::addCompletedDeal(
    const DealPtr& completed_deal, const InternalEmployeePtr& changer
)
{
    if (std::find(this->completed_deals.begin(), this->completed_deals.end(), completed_deal) !=
        this->completed_deals.end()) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(completed_deal),
            ExternalEmployeeFields::CompletedDeals,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Deal,
            ChangeLog::Action::Add,
            update
        ));
        this->updateAt(update);
        this->addRelatedDeals(completed_deal, changer, update);
        this->completed_deals.push_back(completed_deal);
    }
}

void ExternalEmployee::delCompletedDeal(size_t index, const InternalEmployeePtr& changer)
{
    if (index < this->completed_deals.size()) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->completed_deals[index]),
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
    }
}

void ExternalEmployee::addAssignedTask(
    const TaskPtr& assigned_task, const InternalEmployeePtr& changer
)
{
    if (std::find(this->assigned_tasks.begin(), this->assigned_tasks.end(), assigned_task) !=
        this->assigned_tasks.end()) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(assigned_task),
            ExternalEmployeeFields::AssignedTasks,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Task,
            ChangeLog::Action::Add,
            update
        ));
        this->updateAt(update);
        this->assigned_tasks.push_back(assigned_task);
    }
}

void ExternalEmployee::delAssignedTask(size_t index, const InternalEmployeePtr& changer)
{
    if (index < this->assigned_tasks.size()) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->assigned_tasks[index]),
            std::nullopt,
            ExternalEmployeeFields::AssignedTasks,
            ChangeLog::FieldType::Task,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->updateAt(update);
        this->assigned_tasks.erase(this->assigned_tasks.begin() + index);
    }
}

void ExternalEmployee::addCompletedTask(
    const TaskPtr& completed_task, const InternalEmployeePtr& changer
)
{
    if (std::find(this->completed_tasks.begin(), this->completed_tasks.end(), completed_task) !=
        this->completed_tasks.end()) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(completed_task),
            ExternalEmployeeFields::CompletedTasks,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Task,
            ChangeLog::Action::Add,
            update
        ));
        this->updateAt(update);
        this->completed_tasks.push_back(completed_task);
    }
}

void ExternalEmployee::delCompletedTask(size_t index, const InternalEmployeePtr& changer)
{
    if (index < this->completed_tasks.size()) {
        Date update = Date();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->completed_tasks[index]),
            std::nullopt,
            ExternalEmployeeFields::CompletedTasks,
            ChangeLog::FieldType::Task,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->updateAt(update);
        this->completed_tasks.erase(this->completed_tasks.begin() + index);
    }
}