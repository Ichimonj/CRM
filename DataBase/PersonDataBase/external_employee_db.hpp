#pragma once
#include <unordered_map>

#include "company.hpp"

using CompanyId = BigUint;
class ExternalEmployeeDataBase {
public:
    ExternalEmployeeDataBase() = default;

    void addExternalEmployee(const ExternalEmployeePtr& person);
    void delExternalEmployee(const BigUint& id);

    /// @name Getters
    /// @{
    auto getById() const -> const std::unordered_map<BigUint, ExternalEmployeePtr>&;
    auto getByName() const -> const std::unordered_multimap<std::string, ExternalEmployeePtr>&;
    auto getByEmail() const -> const std::unordered_multimap<std::string, ExternalEmployeePtr>&;
    auto getByPhone() const -> const std::unordered_multimap<std::string, ExternalEmployeePtr>&;
    auto getByCompany() const
        -> const std::unordered_map<CompanyId, std::vector<ExternalEmployeePtr>>&;
    /// @}

    /// @name Find functions
    /// @{
    auto findById(const BigUint& id) const -> const ExternalEmployeePtr&;
    auto findByName(const std::string& name) const -> const std::vector<ExternalEmployeePtr>;
    auto findByEmail(const std::string& email) const -> const std::vector<ExternalEmployeePtr>;
    auto findByPhone(const std::string& phone) const -> const std::vector<ExternalEmployeePtr>;
    auto findByCompany(const CompanyId& id) const -> const std::vector<ExternalEmployeePtr>;
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
    /// @}

private:
    std::unordered_map<BigUint, ExternalEmployeePtr>                by_id;
    std::unordered_multimap<std::string, ExternalEmployeePtr>       by_name;
    std::unordered_multimap<std::string, ExternalEmployeePtr>       by_email;
    std::unordered_multimap<std::string, ExternalEmployeePtr>       by_phone;
    std::unordered_map<CompanyId, std::vector<ExternalEmployeePtr>> by_company;
};