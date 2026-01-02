#pragma once
#include <map>
#include <unordered_map>

#include "Company/company.hpp"

using CompanyId = BigUint;
class ExternalEmployeeDataBase {
public:
    ExternalEmployeeDataBase() = default;

    void add(const ExternalEmployeePtr& employee);
    void remove(const BigUint& id);

    /// @name Getters
    /// @{
    auto size() const -> size_t;
    bool empty() const;
    auto getAll() const -> const std::unordered_map<BigUint, ExternalEmployeePtr>&;
    auto getByName() const -> const std::unordered_multimap<std::string, ExternalEmployeePtr>&;
    auto getByEmail() const -> const std::unordered_multimap<std::string, ExternalEmployeePtr>&;
    auto getByPhone() const -> const std::unordered_multimap<std::string, ExternalEmployeePtr>&;
    auto getByCompany() const
        -> const std::unordered_map<CompanyId, std::vector<ExternalEmployeePtr>>&;
    /// @}

    /// @name Find functions
    /// @{
    auto findById(const BigUint& id) const -> const ExternalEmployeePtr;
    auto findByName(const std::string& name) const -> const std::vector<ExternalEmployeePtr>;
    auto findByNameSubstr(const std::string& substr) const
        -> const std::vector<ExternalEmployeePtr>;
    auto findByEmail(const std::string& email) const -> const std::vector<ExternalEmployeePtr>;
    auto findByEmailSubstr(const std::string& substr) const
        -> const std::vector<ExternalEmployeePtr>;
    auto findByPhone(const std::string& phone) const -> const std::vector<ExternalEmployeePtr>;
    auto findByPhoneSubstr(const std::string& substr) const
        -> const std::vector<ExternalEmployeePtr>;
    auto findByCompany(const CompanyId& id) const -> const std::vector<ExternalEmployeePtr>&;

    auto findByStatus(const EmployeeStatus status) const -> const std::vector<ExternalEmployeePtr>&;
    auto findByOtherStatus(const std::string& status) const
        -> const std::vector<ExternalEmployeePtr>&;
    auto findByAccessRole(const AccessRole role) const -> const std::vector<ExternalEmployeePtr>&;
    auto findByOtherAccessRole(const std::string& role) const
        -> const std::vector<ExternalEmployeePtr>&;
    auto findByInfluence(const ExternalEmployee::InfluenceLevel level) const
        -> const std::vector<ExternalEmployeePtr>&;
    auto findByTimeZone(const int time_zone) const -> const std::vector<ExternalEmployeePtr>&;
    auto findByJobTitle(const std::string& job_title) const
        -> const std::vector<ExternalEmployeePtr>;
    auto findByDepartment(const std::string& department) const
        -> const std::vector<ExternalEmployeePtr>;
    /// @}

    /// @name Change functions
    /// @{
    void changeName(const BigUint& id, const std::string& name, const InternalEmployeePtr& changer);
    void changeEmail(
        const BigUint& id, const OptionalStr& email, const InternalEmployeePtr& changer
    );
    void addMoreEmail(
        const BigUint& id, const std::string& email, const InternalEmployeePtr& changer
    );
    void delMoreEmail(const BigUint& id, size_t index, const InternalEmployeePtr& changer);

    void changePhone(
        const BigUint& id, const PhoneNumberPtr& number, const InternalEmployeePtr& changer
    );

    void addMorePhone(
        const BigUint& id, const PhoneNumber& number, const InternalEmployeePtr& changer
    );
    void delMorePhone(const BigUint& id, size_t index, const InternalEmployeePtr& changer);

    void changeCompany(
        const BigUint& id, const ExternalCompanyPtr& company, const InternalEmployeePtr& changer
    );
    void changeStatus(
        const BigUint& id, const EmployeeStatus status, const InternalEmployeePtr& changer
    );
    void changeOtherStatus(
        const BigUint& id, const OptionalStr& status, const InternalEmployeePtr& changer
    );
    void changeAccessRole(
        const BigUint& id, const AccessRole role, const InternalEmployeePtr& changer
    );
    void changeOtherAccessRole(
        const BigUint& id, const OptionalStr& role, const InternalEmployeePtr& changer
    );
    void changeInfluence(
        const BigUint&                                        id,
        const std::optional<ExternalEmployee::InfluenceLevel> level,
        const InternalEmployeePtr&                            changer
    );
    void changeTimeZone(const BigUint& id, const int time_zone, const InternalEmployeePtr& changer);
    void changeJobTitle(
        const BigUint& id, const OptionalStr& title, const InternalEmployeePtr& changer
    );
    void changeDepartment(
        const BigUint& id, const OptionalStr& department, const InternalEmployeePtr& changer
    );
    /// @}

private:
    static const std::vector<ExternalEmployeePtr>                   empty_vector;
    std::unordered_map<BigUint, ExternalEmployeePtr>                by_id;
    std::unordered_multimap<std::string, ExternalEmployeePtr>       by_name;
    std::multimap<std::string, ExternalEmployeePtr>                 by_name_substr_search;
    std::unordered_multimap<std::string, ExternalEmployeePtr>       by_email;
    std::multimap<std::string, ExternalEmployeePtr>                 by_email_substr_search;
    std::unordered_multimap<std::string, ExternalEmployeePtr>       by_phone;
    std::multimap<std::string, ExternalEmployeePtr>                 by_phone_substr_search;
    std::unordered_map<CompanyId, std::vector<ExternalEmployeePtr>> by_company;
    //
    std::unordered_map<EmployeeStatus, std::vector<ExternalEmployeePtr>> by_status;
    std::unordered_map<std::string, std::vector<ExternalEmployeePtr>>    by_other_status;
    std::unordered_map<AccessRole, std::vector<ExternalEmployeePtr>>     by_access_role;
    std::unordered_map<std::string, std::vector<ExternalEmployeePtr>>    by_other_access_role;
    std::unordered_map<ExternalEmployee::InfluenceLevel, std::vector<ExternalEmployeePtr>>
                                                              by_influence_level;
    std::unordered_map<int, std::vector<ExternalEmployeePtr>> by_time_zone;

    std::unordered_multimap<std::string, ExternalEmployeePtr> by_job_title;
    std::unordered_multimap<std::string, ExternalEmployeePtr> by_department;
    //
    void safeRemoveFromMultimap(
        auto&                      map,
        const auto&                key,
        const ExternalEmployeePtr& employee,
        const size_t               line,
        const std::string&         index_name
    );
    void safeRemoveFromVector(
        auto&                      map,
        const auto&                key,
        const ExternalEmployeePtr& employee,
        const size_t               line,
        const std::string&         index_name
    );

    void logEmptyContainer(
        const std::string& file,
        const size_t       line,
        const std::string& employee_id,
        const std::string& index_name
    );
};