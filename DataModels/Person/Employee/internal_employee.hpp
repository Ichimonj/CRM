#pragma once
#include <optional>
#include <string>

#include "big_uint.hpp"
#include "date.hpp"
#include "deal.hpp"
#include "employee_enums.hpp"
#include "money.hpp"
#include "note.hpp"
#include "person.hpp"
#include "task.hpp"
struct Document;
struct Deal;

class InternalEmployee;
class InternalEmployeeDataBase;
using DatePtr             = std::shared_ptr<Date>;
using DocumentPtr         = std::shared_ptr<Document>;
using TaskPtr             = std::shared_ptr<Task>;
using DealPtr             = std::shared_ptr<Deal>;
using ClientPtr           = std::shared_ptr<Client>;
using InternalEmployeePtr = std::shared_ptr<InternalEmployee>;
using MoneyPtr            = std::shared_ptr<Money>;

class InternalEmployee : public Person {
public:
    InternalEmployee(
        const BigUint&     id,
        const std::string& name,
        const std::string& surname,
        const OptionalStr& patronymic
    );
    InternalEmployee(
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
    );
    virtual ~InternalEmployee() noexcept = default;

    /// @name Getters
    /// @{
    auto getManager() const -> const InternalEmployeePtr&;
    auto getPosition() const -> const OptionalStr&;
    auto getDepartment() const -> const OptionalStr&;
    auto getAccessRole() const -> AccessRole;
    auto getOtherRole() const -> const OptionalStr&;
    auto getStatus() const -> EmployeeStatus;
    auto getOtherStatus() const -> const OptionalStr&;
    auto getSalesTerritory() const -> const OptionalStr&;
    auto getLastLoginDate() const -> const DatePtr&;
    auto getLastActionDate() const -> const DatePtr&;
    auto getTimeZone() const -> int;
    auto getIsActive() const -> bool;
    auto getNextReviewDate() const -> const DatePtr&;
    auto getHireDate() const -> const DatePtr&;
    auto getDismissalDate() const -> const DatePtr&;

    auto getManagedDeals() const -> const std::vector<DealPtr>&;
    auto getProposedOffers() const -> const std::vector<OfferPtr>&;
    auto getCommissionRate() const -> const std::optional<double>&;
    auto getBaseSalary() const -> const MoneyPtr&;
    auto getPerformanceScore() const -> const std::optional<double>&;
    auto getLeads() const -> const std::vector<ClientPtr>&;
    auto getMonthlyQuota() const -> const std::vector<Money>&;
    auto getTasks() const -> const std::vector<TaskPtr>&;
    auto getDocuments() const -> const std::vector<DocumentPtr>&;
    auto getSkills() const -> const std::vector<std::string>&;
    auto getDirectReports() const -> const std::vector<InternalEmployeePtr>&;
    /// @}

    /// @name Change functions
    /// @{
    // functions called only from the database
private:
    bool setDepartment(const OptionalStr& department, const InternalEmployeePtr& changer);
    bool setStatus(const EmployeeStatus status, const InternalEmployeePtr& changer);
    bool setOtherStatus(const OptionalStr& status, const InternalEmployeePtr& changer);
    bool setAccessRole(const AccessRole role, const InternalEmployeePtr& changer);
    bool setOtherRole(const OptionalStr& role, const InternalEmployeePtr& changer);
    bool setTimeZone(const int time_zone, const InternalEmployeePtr& changer);
    bool setManager(const InternalEmployeePtr& manager, const InternalEmployeePtr& changer);
    bool setPosition(const OptionalStr& position, const InternalEmployeePtr& changer);
    bool setIsActive(bool is_active, const InternalEmployeePtr& changer);
    bool setSalesTerritory(const OptionalStr& sales_territory, const InternalEmployeePtr& changer);

    // public functions
public:
    bool setLastLoginDate(const DatePtr& last_login_date, const InternalEmployeePtr& changer);
    bool setLastActionDate(const DatePtr& last_action_date, const InternalEmployeePtr& changer);
    bool setNextReviewDate(const DatePtr& next_review_date, const InternalEmployeePtr& changer);
    bool setHireDate(const DatePtr& hire_date, const InternalEmployeePtr& changer);
    bool setDismissalDate(const DatePtr& dismissal_date, const InternalEmployeePtr& changer);

    bool setCommissionRate(
        const std::optional<double>& commission_rate, const InternalEmployeePtr& changer
    );
    bool setBaseSalary(const MoneyPtr& base_salary, const InternalEmployeePtr& changer);
    bool setPerformanceScore(
        const std::optional<double>& performance_score, const InternalEmployeePtr& changer
    );

    bool addManagerDeal(const DealPtr& deal, const InternalEmployeePtr& changer);
    bool delManagerDeal(size_t index, const InternalEmployeePtr& changer);

    bool addProposedOffer(const OfferPtr& offer, const InternalEmployeePtr& changer);
    bool delProposedOffer(size_t index, const InternalEmployeePtr& changer);

    bool addLead(const ClientPtr& lead, const InternalEmployeePtr& changer);
    bool delLead(size_t index, const InternalEmployeePtr& changer);

    bool addMonthlyQuota(const Money& quota, const InternalEmployeePtr& changer);
    bool delMonthlyQuota(size_t index, const InternalEmployeePtr& changer);

    bool addTask(const TaskPtr& task, const InternalEmployeePtr& changer);
    bool delTask(size_t index, const InternalEmployeePtr& changer);

    bool addDocument(const DocumentPtr& document, const InternalEmployeePtr& changer);
    bool delDocument(size_t index, const InternalEmployeePtr& changer);

    bool addSkill(const std::string& skill, const InternalEmployeePtr& changer);
    bool delSkill(size_t index, const InternalEmployeePtr& changer);

    bool addDirectReport(const InternalEmployeePtr& report, const InternalEmployeePtr& changer);
    bool delDirectReport(size_t index, const InternalEmployeePtr& changer);
    /// @}

private:
    InternalEmployeePtr manager;
    OptionalStr         position;
    OptionalStr         department;
    AccessRole          access_role;
    OptionalStr         other_role;
    EmployeeStatus      status;
    OptionalStr         other_status;
    OptionalStr         sales_territory;
    DatePtr             last_login_date;
    DatePtr             last_action_date;
    int                 time_zone;  /// UTC +/-
    bool                is_active;
    DatePtr             next_review_date;
    DatePtr             hire_date;
    DatePtr             dismissal_date;
    MoneyPtr            base_salary;

    //
    std::vector<DealPtr>             managed_deals;
    std::vector<OfferPtr>            proposed_offers;
    std::optional<double>            commission_rate;
    std::optional<double>            performance_score;
    std::vector<ClientPtr>           leads;
    std::vector<Money>               monthly_quota;
    std::vector<TaskPtr>             tasks;
    std::vector<DocumentPtr>         documents;
    std::vector<std::string>         skills;
    std::vector<InternalEmployeePtr> direct_reports;

    friend InternalEmployeeDataBase;

#ifdef _TESTING
public:
    bool _setDepartment(const OptionalStr& department, const InternalEmployeePtr& changer) {
        return this->setDepartment(department, changer);
    }
    bool _setStatus(const EmployeeStatus status, const InternalEmployeePtr& changer) {
        return this->setStatus(status, changer);
    }
    bool _setOtherStatus(const OptionalStr& status, const InternalEmployeePtr& changer) {
        return this->setOtherStatus(status, changer);
    }
    bool _setAccessRole(const AccessRole role, const InternalEmployeePtr& changer) {
        return this->setAccessRole(role, changer);
    }
    bool _setOtherRole(const OptionalStr& role, const InternalEmployeePtr& changer) {
        return this->setOtherRole(role, changer);
    }
    bool _setTimeZone(const int time_zone, const InternalEmployeePtr& changer) {
        return this->setTimeZone(time_zone, changer);
    }
    bool _setManager(const InternalEmployeePtr& manager, const InternalEmployeePtr& changer) {
        return this->setManager(manager, changer);
    }
    bool _setPosition(const OptionalStr& position, const InternalEmployeePtr& changer) {
        return this->setPosition(position, changer);
    }
    bool _setIsActive(bool is_active, const InternalEmployeePtr& changer) {
        return this->setIsActive(is_active, changer);
    }
    bool _setSalesTerritory(const OptionalStr& sales_territory, const InternalEmployeePtr& changer) {
        return this->setSalesTerritory(sales_territory, changer);
    }
#endif // _TESTING

};