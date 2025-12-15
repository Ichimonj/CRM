#pragma once
#include "base_interaction.hpp"
#include "employee_enums.hpp"
#include "money.hpp"
#include "person.hpp"
#include "social_network.hpp"

struct Deal;
using DealPtr = std::shared_ptr<Deal>;
class Task;
using TaskPtr = std::shared_ptr<Task>;
struct Date;
using DatePtr = std::shared_ptr<Date>;
class ExternalCompany;
using ExternalCompanyPtr = std::shared_ptr<ExternalCompany>;
class InternalEmployee;
using InternalEmployeePtr = std::shared_ptr<InternalEmployee>;
class Note;
using StringPair = std::pair<std::string, std::string>;
using MoneyPtr   = std::shared_ptr<Money>;
class ExternalEmployee : public Person {
public:
    enum class InfluenceLevel : uint8_t { Critical, High, Medium, Low, VeryLow, COUNT };

    ExternalEmployee(
        const BigUint&     id,
        const std::string& name,
        const std::string& surname,
        const OptionalStr& patronymic
    );
    ExternalEmployee(
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
    );
    virtual ~ExternalEmployee() noexcept = default;

    /// @name Getters
    /// @{
    auto getCompany() const -> const ExternalCompanyPtr&;
    auto getJobTitle() const -> const OptionalStr&;
    auto getDepartment() const -> const OptionalStr&;
    auto getStatus() const -> const EmployeeStatus;
    auto getOtherStatus() const -> const OptionalStr&;
    auto getAccessLevel() const -> AccessLevel;
    auto getOtherRole() const -> const OptionalStr&;
    auto getCurrentInteraction() const -> const InteractionPtr&;
    auto getLastContactDate() const -> const DatePtr&;
    auto getTimeZone() const -> const int;
    auto getPreferredContactTime() const -> const OptionalStr&;

    auto getDecisionInfluence() const -> const std::optional<InfluenceLevel>&;
    auto getInfluenceScore() const -> const std::optional<double>&;
    auto getBudgetAuthority() const -> const MoneyPtr&;
    auto getSalary() const -> const MoneyPtr&;

    auto getPainPoints() const -> const std::vector<std::string>&;
    auto getAssignedDeals() const -> const std::vector<DealPtr>&;
    auto getCompletedDeals() const -> const std::vector<DealPtr>&;
    auto getAssignedTasks() const -> const std::vector<TaskPtr>&;
    auto getCompletedTasks() const -> const std::vector<TaskPtr>&;
    /// @}

    /// @name Change functions
    /// @{
    void setCompany(const ExternalCompanyPtr& company, const InternalEmployeePtr& changer);
    void setJobTitle(const OptionalStr& title, const InternalEmployeePtr& changer);
    void setDepartment(const OptionalStr& department, const InternalEmployeePtr& changer);
    void setStatus(const EmployeeStatus status, const InternalEmployeePtr& changer);
    void setOtherStatus(const OptionalStr& status, const InternalEmployeePtr& changer);
    void setAccessRole(const AccessLevel access_role, const InternalEmployeePtr& changer);
    void setOtherRole(const OptionalStr& other_role, const InternalEmployeePtr& changer);
    void setCurrentInteraction(
        const InteractionPtr& current_interaction, const InternalEmployeePtr& changer
    );
    void setLastContactDate(const DatePtr& last_contact_date, const InternalEmployeePtr& changer);
    void setTimeZone(const int time_zone, const InternalEmployeePtr& changer);
    void setPreferredContactTime(
        const OptionalStr& preferred_contact_time, const InternalEmployeePtr& changer
    );
    void setDecisionInfluence(
        const std::optional<InfluenceLevel>& decision_influence, const InternalEmployeePtr& changer
    );
    void setInfluenceScore(
        const std::optional<double>& influence_score, const InternalEmployeePtr& changer
    );
    void setBudgetAuthority(const MoneyPtr& budget_authority, const InternalEmployeePtr& changer);
    void setSalary(const MoneyPtr& salary, const InternalEmployeePtr& changer);

    void addPainPoint(const std::string& pain_point, const InternalEmployeePtr& changer);
    void delPainPoint(size_t index, const InternalEmployeePtr& changer);

    void addAssignedDeal(const DealPtr& assigned_deal, const InternalEmployeePtr& changer);
    void delAssignedDeal(size_t index, const InternalEmployeePtr& changer);

    void addCompletedDeal(const DealPtr& completed_deal, const InternalEmployeePtr& changer);
    void delCompletedDeal(size_t index, const InternalEmployeePtr& changer);

    void addAssignedTask(const TaskPtr& assigned_task, const InternalEmployeePtr& changer);
    void delAssignedTask(size_t index, const InternalEmployeePtr& changer);

    void addCompletedTask(const TaskPtr& completed_task, const InternalEmployeePtr& changer);
    void delCompletedTask(size_t index, const InternalEmployeePtr& changer);
    /// @}

private:
    ExternalCompanyPtr company;
    OptionalStr        job_title;
    OptionalStr        department;

    EmployeeStatus     status;
    OptionalStr        other_status;
    AccessLevel        access_role;
    OptionalStr        other_role;
    InteractionPtr     current_interaction;
    DatePtr            last_contact_date;
    int                time_zone;               /// UTC +/-
    OptionalStr        preferred_contact_time;  /// 9-12 UTC

    //
    std::optional<InfluenceLevel> decision_influence;
    std::optional<double>         influence_score;
    MoneyPtr                      budget_authority;
    MoneyPtr                      salary;
    std::vector<std::string>      pain_points;

    // deals
    std::vector<DealPtr> assigned_deals;
    std::vector<DealPtr> completed_deals;
    // tasks
    std::vector<TaskPtr> assigned_tasks;
    std::vector<TaskPtr> completed_tasks;
};