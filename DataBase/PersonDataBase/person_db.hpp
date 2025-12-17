#pragma once
#include <unordered_map>

#include "company.hpp"

using CompanyId = BigUint;
class PersonDataBase {
public:
    PersonDataBase() = default;

    void addPerson(const PersonPtr& person);
    void delPerson(const BigUint& id);

    /// @name Getters
    /// @{
    auto getById() const -> const std::unordered_map<BigUint, PersonPtr>&;
    auto getByName() const -> const std::unordered_multimap<std::string, PersonPtr>&;
    auto getByEmail() const -> const std::unordered_multimap<std::string, PersonPtr>&;
    auto getByPhone() const -> const std::unordered_multimap<std::string, PersonPtr>&;
    auto getByCompany() const -> const std::unordered_map<CompanyId, std::vector<PersonPtr>>&;
    /// @}

    /// @name Find functions
    /// @{
    auto findById(const BigUint& id) const -> const PersonPtr&;
    auto findByName(const std::string& name) const -> const std::vector<PersonPtr>;
    auto findByEmail(const std::string& email) const -> const std::vector<PersonPtr>;
    auto findByPhone(const std::string& phone) const -> const std::vector<PersonPtr>;
    auto findByCompany(const CompanyId& id) const -> const std::vector<PersonPtr>;
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
    std::unordered_map<BigUint, PersonPtr>                by_id;
    std::unordered_multimap<std::string, PersonPtr>       by_name;
    std::unordered_multimap<std::string, PersonPtr>       by_email;
    std::unordered_multimap<std::string, PersonPtr>       by_phone;
    std::unordered_map<CompanyId, std::vector<PersonPtr>> by_company;
};