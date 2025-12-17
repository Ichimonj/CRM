#pragma once
#include <unordered_map>

#include "internal_employee.hpp"
using InternalEmployeePtr = std::shared_ptr<InternalEmployee>;

class InternalEmployeeDataBase {
public:
    void add(const InternalEmployeePtr& client);
    void remove(const BigUint& id);

    /// @name Getters
    /// @{
    auto getById() const -> const std::unordered_map<BigUint, InternalEmployeePtr>&;
    auto getByName() const -> const std::unordered_multimap<std::string, InternalEmployeePtr>&;
    auto getByEmail() const -> const std::unordered_multimap<std::string, InternalEmployeePtr>&;
    auto getByPhone() const -> const std::unordered_multimap<std::string, InternalEmployeePtr>&;
    /// @}

    /// @name Find functions
    /// @{
    auto findById(const BigUint& id) const -> const InternalEmployeePtr&;
    auto findByName(const std::string& name) const -> const std::vector<InternalEmployeePtr>;
    auto findByEmail(const std::string& email) const -> const std::vector<InternalEmployeePtr>;
    auto findByPhone(const std::string& phone) const -> const std::vector<InternalEmployeePtr>;
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
    /// @}

private:
    std::unordered_map<BigUint, InternalEmployeePtr>          by_id;
    std::unordered_multimap<std::string, InternalEmployeePtr> by_name;
    std::unordered_multimap<std::string, InternalEmployeePtr> by_email;
    std::unordered_multimap<std::string, InternalEmployeePtr> by_phone;
};