#include "internal_employee_db.hpp"

#include <algorithm>
#include <string>

#include "Logger/events_log.hpp"
#include "TenantContext/tenant_context.hpp"

const std::vector<InternalEmployeePtr> InternalEmployeeDataBase::empty_vector;

//
void InternalEmployeeDataBase::add(const InternalEmployeePtr& employee)
{
    if (employee == nullptr) return;

    if (this->by_id.find(employee->getId()) != this->by_id.end()) {
        return;
    }
    this->by_id[employee->getId()] = employee;
    this->by_name.emplace(employee->getName(), employee);

    std::string lower_name = employee->getName();
    std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), ::tolower);

    this->by_name_substr_search.emplace(lower_name, employee);

    if (employee->getEmail()) {
        this->by_email.emplace(employee->getEmail().value(), employee);

        std::string lower_email = employee->getEmail().value();
        std::transform(lower_email.begin(), lower_email.end(), lower_email.begin(), ::tolower);
        this->by_email_substr_search.emplace(lower_email, employee);
    }
    for (auto& email : employee->getMoreEmails()) {
        this->by_email.emplace(email, employee);

        std::string lower_email = email;
        std::transform(lower_email.begin(), lower_email.end(), lower_email.begin(), ::tolower);
        this->by_email_substr_search.emplace(lower_email, employee);
    }

    if (employee->getPhoneNumber()) {
        this->by_phone.emplace(employee->getPhoneNumber()->getNumber(), employee);

        this->by_phone_substr_search.emplace(employee->getPhoneNumber()->getNumber(), employee);
    }
    for (auto& number : employee->getMorePhoneNumbers()) {
        this->by_phone.emplace(number.getNumber(), employee);

        this->by_phone_substr_search.emplace(number.getNumber(), employee);
    }

    if (employee->getDepartment()) {
        this->by_department.emplace(employee->getDepartment().value(), employee);
    }

    if (employee->getStatus() != EmployeeStatus::other) {
        this->by_status[employee->getStatus()].push_back(employee);
    } else if (employee->getOtherStatus()) {
        this->by_other_status[employee->getOtherStatus().value()].push_back(employee);
    }

    if (employee->getAccessRole() != AccessRole::other) {
        this->by_access_role[employee->getAccessRole()].push_back(employee);
    } else if (employee->getOtherRole()) {
        this->by_other_access_role[employee->getOtherRole().value()].push_back(employee);
    }

    this->by_time_zone[employee->getTimeZone()].push_back(employee);

    if (!employee->getManager().expired()) {
        this->by_manager[employee->getManager().lock()->getId()].push_back(employee);
    }
    if (employee->getPosition()) {
        this->by_position.emplace(employee->getPosition().value(), employee);
    }
    this->by_is_active[employee->getIsActive()].push_back(employee);

    if (employee->getSalesTerritory()) {
        this->by_sales_territory.emplace(employee->getSalesTerritory().value(), employee);
    }
}

void InternalEmployeeDataBase::soft_remove(const BigUint& id, const Date& remove_date)
{
    auto employee_it = by_id.find(id);
    if (employee_it == by_id.end()) {
        return;
    }

    InternalEmployeePtr employee = employee_it->second;

    safeRemoveFromMap(by_name, employee->getName(), employee, __LINE__, "by_name");

    std::string lower_name = employee->getName();
    std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), ::tolower);
    safeRemoveFromMap(
        by_name_substr_search, lower_name, employee, __LINE__, "by_name_substr_search"
    );

    if (employee->getEmail().has_value()) {
        const std::string& email = employee->getEmail().value();

        safeRemoveFromMap(by_email, email, employee, __LINE__, "by_email");

        std::string lower_email = email;
        std::transform(lower_email.begin(), lower_email.end(), lower_email.begin(), ::tolower);
        safeRemoveFromMap(
            by_email_substr_search, lower_email, employee, __LINE__, "by_email_substr_search"
        );
    }

    for (const std::string& more_email : employee->getMoreEmails()) {
        safeRemoveFromMap(by_email, more_email, employee, __LINE__, "by_email");

        std::string lower_more_email = more_email;
        std::transform(
            lower_more_email.begin(), lower_more_email.end(), lower_more_email.begin(), ::tolower
        );
        safeRemoveFromMap(
            by_email_substr_search, lower_more_email, employee, __LINE__, "by_email_substr_search"
        );
    }

    if (employee->getPhoneNumber()) {
        const std::string& phone = employee->getPhoneNumber()->getNumber();

        safeRemoveFromMap(by_phone, phone, employee, __LINE__, "by_phone");
        safeRemoveFromMap(
            by_phone_substr_search, phone, employee, __LINE__, "by_phone_substr_search"
        );
    }

    for (const auto& more_phone : employee->getMorePhoneNumbers()) {
        const std::string& phone_str = more_phone.getNumber();

        safeRemoveFromMap(by_phone, phone_str, employee, __LINE__, "by_phone");
        safeRemoveFromMap(
            by_phone_substr_search, phone_str, employee, __LINE__, "by_phone_substr_search"
        );
    }

    if (employee->getDepartment()) {
        const std::string& department = employee->getDepartment().value();
        safeRemoveFromMap(this->by_department, department, employee, __LINE__, "by_department");
    }

    if (employee->getStatus() != EmployeeStatus::other) {
        const auto status = employee->getStatus();
        safeRemoveFromVector(this->by_status, status, employee, __LINE__, "by_status");
    } else if (employee->getOtherStatus()) {
        const std::string& status = employee->getOtherStatus().value();
        safeRemoveFromVector(this->by_other_status, status, employee, __LINE__, "by_other_status");
    }

    if (employee->getAccessRole() != AccessRole::other) {
        const auto role = employee->getAccessRole();
        safeRemoveFromVector(this->by_access_role, role, employee, __LINE__, "by_access_role");
    } else if (employee->getOtherRole()) {
        const std::string& role = employee->getOtherRole().value();
        safeRemoveFromVector(
            this->by_other_access_role, role, employee, __LINE__, "by_other_access_role"
        );
    }
    safeRemoveFromVector(
        this->by_time_zone, employee->getTimeZone(), employee, __LINE__, "by_time_zone"
    );

    this->by_manager.erase(employee->getId());

    if (employee->getPosition()) {
        const std::string& position = employee->getPosition().value();
        safeRemoveFromMap(this->by_position, position, employee, __LINE__, "by_position");
    }

    safeRemoveFromVector(
        this->by_is_active, employee->getIsActive(), employee, __LINE__, "by_is_active"
    );

    if (employee->getSalesTerritory()) {
        const std::string& territory = employee->getSalesTerritory().value();
        safeRemoveFromMap(
            this->by_sales_territory, territory, employee, __LINE__, "by_sales_territory"
        );
    }
    this->removed.push_back({remove_date, employee});

    by_id.erase(employee_it);
}

void InternalEmployeeDataBase::hard_remove(const size_t index, TenantContext& context)
{
    if (index < this->removed.size()) {
        const auto& employee = removed[index].second;
        auto employee_id = employee->getId();
        context.client_data_base.removeOwner(employee_id);
        context.deal_data_base.removeInternalEmployee(employee_id);

        this->removed.erase(this->removed.begin() + index);
    }
}

auto InternalEmployeeDataBase::size() const -> size_t { return this->by_id.size(); }

bool InternalEmployeeDataBase::empty() const { return this->by_id.empty(); }

auto InternalEmployeeDataBase::getAll() const
    -> const std::unordered_map<BigUint, InternalEmployeePtr>&
{
    return this->by_id;
}

auto InternalEmployeeDataBase::getByName() const
    -> const std::unordered_multimap<std::string, InternalEmployeePtr>&
{
    return this->by_name;
}

auto InternalEmployeeDataBase::getByEmail() const
    -> const std::unordered_multimap<std::string, InternalEmployeePtr>&
{
    return this->by_email;
}

auto InternalEmployeeDataBase::getByPhone() const
    -> const std::unordered_multimap<std::string, InternalEmployeePtr>&
{
    return this->by_phone;
}

auto InternalEmployeeDataBase::findById(const BigUint& id) const -> const InternalEmployeePtr
{
    auto employee = this->by_id.find(id);
    if (employee != this->by_id.end()) {
        return employee->second;
    }
    return nullptr;
}

auto InternalEmployeeDataBase::findByName(const std::string& name) const
    -> const std::vector<InternalEmployeePtr>
{
    auto employees = this->by_name.equal_range(name);
    if (employees.first == employees.second) return empty_vector;

    std::vector<InternalEmployeePtr> result;
    for (auto it = employees.first; it != employees.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto InternalEmployeeDataBase::findByNameSubstr(const std::string& substr) const
    -> const std::vector<InternalEmployeePtr>
{
    if (substr.empty()) return empty_vector;
    std::string key = substr;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    auto first = this->by_name_substr_search.lower_bound(key);
    key.back()++;
    auto second = this->by_name_substr_search.lower_bound(key);

    if (first == second) return empty_vector;
    std::vector<InternalEmployeePtr> result;
    for (auto it = first; it != second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto InternalEmployeeDataBase::findByEmail(const std::string& email) const
    -> const std::vector<InternalEmployeePtr>
{
    auto employees = this->by_email.equal_range(email);
    if (employees.first == employees.second) return empty_vector;

    std::vector<InternalEmployeePtr> result;
    for (auto it = employees.first; it != employees.second; ++it) result.push_back(it->second);

    return result;
}

auto InternalEmployeeDataBase::findByEmailSubstr(const std::string& substr) const
    -> const std::vector<InternalEmployeePtr>
{
    if (substr.empty()) return empty_vector;
    std::string key = substr;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    auto first = this->by_email_substr_search.lower_bound(key);
    key.back()++;
    auto second = this->by_email_substr_search.lower_bound(key);

    if (first == second) return empty_vector;
    std::vector<InternalEmployeePtr> result;
    for (auto it = first; it != second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto InternalEmployeeDataBase::findByPhone(const std::string& phone) const
    -> const std::vector<InternalEmployeePtr>
{
    auto employees = this->by_phone.equal_range(phone);
    if (employees.first == employees.second) return empty_vector;

    std::vector<InternalEmployeePtr> result;
    for (auto it = employees.first; it != employees.second; ++it) {
        result.push_back(it->second);
    }

    return result;
}

auto InternalEmployeeDataBase::findByPhoneSubstr(const std::string& substr) const
    -> const std::vector<InternalEmployeePtr>
{
    if (substr.empty()) return empty_vector;
    std::string key = substr;

    auto        first = this->by_phone_substr_search.lower_bound(key);
    key.back()++;
    auto second = this->by_phone_substr_search.lower_bound(key);

    if (first == second) return empty_vector;
    std::vector<InternalEmployeePtr> result;
    for (auto it = first; it != second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto InternalEmployeeDataBase::findByDepartment(const std::string& department) const
    -> const std::vector<InternalEmployeePtr>
{
    auto range = this->by_department.equal_range(department);
    if (range.first == range.second) return empty_vector;

    std::vector<InternalEmployeePtr> result;
    for (auto it = range.first; it != range.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto InternalEmployeeDataBase::findByStatus(const EmployeeStatus status) const
    -> const std::vector<InternalEmployeePtr>&
{
    auto it = this->by_status.find(status);
    if (it == this->by_status.end()) return empty_vector;
    return it->second;
}

auto InternalEmployeeDataBase::findByOtherStatus(const std::string& status) const
    -> const std::vector<InternalEmployeePtr>&
{
    auto it = this->by_other_status.find(status);
    if (it == this->by_other_status.end()) return empty_vector;
    return it->second;
}

auto InternalEmployeeDataBase::findByAccessRole(const AccessRole role) const
    -> const std::vector<InternalEmployeePtr>&
{
    auto it = this->by_access_role.find(role);
    if (it == this->by_access_role.end()) return empty_vector;
    return it->second;
}

auto InternalEmployeeDataBase::findByOtherAccessRole(const std::string& role) const
    -> const std::vector<InternalEmployeePtr>&
{
    auto it = this->by_other_access_role.find(role);
    if (it == this->by_other_access_role.end()) return empty_vector;
    return it->second;
}

auto InternalEmployeeDataBase::findByTimeZone(const int time_zone) const
    -> const std::vector<InternalEmployeePtr>&
{
    auto it = this->by_time_zone.find(time_zone);
    if (it == this->by_time_zone.end()) return empty_vector;
    return it->second;
}

auto InternalEmployeeDataBase::findByManager(const BigUint& id) const
    -> const std::vector<InternalEmployeePtr>&
{
    auto it = this->by_manager.find((id));
    if (it == this->by_manager.end()) return empty_vector;
    return it->second;
}

auto InternalEmployeeDataBase::findByPosition(const std::string& position) const
    -> const std::vector<InternalEmployeePtr>
{
    auto range = this->by_position.equal_range(position);
    if (range.first == range.second) return empty_vector;

    std::vector<InternalEmployeePtr> result;
    for (auto it = range.first; it != range.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto InternalEmployeeDataBase::findByIsActive(const bool is_active) const
    -> const std::vector<InternalEmployeePtr>&
{
    auto it = this->by_is_active.find(is_active);
    if (it == this->by_is_active.end()) return empty_vector;
    return it->second;
}

auto InternalEmployeeDataBase::findBySalesTerritory(const std::string& sales) const
    -> const std::vector<InternalEmployeePtr>
{
    auto range = this->by_sales_territory.equal_range(sales);
    if (range.first == range.second) return empty_vector;

    std::vector<InternalEmployeePtr> result;
    for (auto it = range.first; it != range.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

void InternalEmployeeDataBase::changeName(
    const BigUint& id, const std::string& name, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    InternalEmployeePtr employee = id_it->second;
    std::string         old_name = employee->getName();

    if (employee->setName(name, changer)) {
        // by_name
        safeRemoveFromMap(this->by_name, old_name, employee, __LINE__, "by_name");
        this->by_name.emplace(name, employee);

        // by_name_substr_search
        std::transform(old_name.begin(), old_name.end(), old_name.begin(), ::tolower);
        std::string new_name = name;
        std::transform(new_name.begin(), new_name.end(), new_name.begin(), ::tolower);

        safeRemoveFromMap(
            this->by_name_substr_search, old_name, employee, __LINE__, "by_name_substr_search"
        );
        this->by_name_substr_search.emplace(new_name, employee);
    }
}

void InternalEmployeeDataBase::changeEmail(
    const BigUint& id, const OptionalStr& email, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;
    InternalEmployeePtr employee  = id_it->second;
    auto                old_email = employee->getEmail();

    if (employee->setEmail(email, changer)) {
        if (old_email.has_value()) {
            std::string old_email_str = old_email.value();

            safeRemoveFromMap(this->by_email, old_email_str, employee, __LINE__, "by_email");
            std::transform(
                old_email_str.begin(), old_email_str.end(), old_email_str.begin(), ::tolower
            );
            safeRemoveFromMap(
                this->by_email_substr_search,
                old_email_str,
                employee,
                __LINE__,
                "by_email_substr_search"
            );
        }
        if (email.has_value()) {
            std::string new_email = email.value();
            this->by_email.emplace(new_email, employee);
            std::transform(new_email.begin(), new_email.end(), new_email.begin(), ::tolower);
            this->by_email_substr_search.emplace(new_email, employee);
        }
    }
}

void InternalEmployeeDataBase::addMoreEmail(
    const BigUint& id, const std::string& email, const InternalEmployeePtr& changer
)
{
    auto employee = this->by_id.find(id);
    if (employee == this->by_id.end()) return;

    if (employee->second->addMoreEmails(email, changer)) {
        this->by_email.emplace(email, employee->second);

        std::string lower_email = email;
        std::transform(lower_email.begin(), lower_email.end(), lower_email.begin(), ::tolower);
        this->by_email_substr_search.emplace(lower_email, employee->second);
    }
}

void InternalEmployeeDataBase::delMoreEmail(
    const BigUint& id, size_t index, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    InternalEmployeePtr employee = id_it->second;
    if (employee->getMoreEmails().size() <= index) return;

    std::string old_email = employee->getMoreEmails()[index];

    if (employee->delMoreEmails(index, changer)) {
        safeRemoveFromMap(this->by_email, old_email, employee, __LINE__, "by_email");
        std::transform(old_email.begin(), old_email.end(), old_email.begin(), ::tolower);
        safeRemoveFromMap(
            this->by_email_substr_search, old_email, employee, __LINE__, "by_email_substr_search"
        );
    }
}

void InternalEmployeeDataBase::changePhone(
    const BigUint& id, const PhoneNumberPtr& number, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    InternalEmployeePtr employee = id_it->second;

    auto                old_number = employee->getPhoneNumber();

    if (employee->setPhoneNumber(number, changer)) {
        if (old_number) {
            safeRemoveFromMap(
                this->by_phone, old_number->getNumber(), employee, __LINE__, "by_phone"
            );
            safeRemoveFromMap(
                this->by_phone_substr_search,
                old_number->getNumber(),
                employee,
                __LINE__,
                "by_phone_substr_search"
            );
        }
        if (number) {
            this->by_phone.emplace(number->getNumber(), employee);
            this->by_phone_substr_search.emplace(number->getNumber(), employee);
        }
    }
}

void InternalEmployeeDataBase::addMorePhone(
    const BigUint& id, const PhoneNumber& number, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    InternalEmployeePtr employee = id_it->second;
    if (employee->addMorePhoneNumber(number, changer)) {
        this->by_phone.emplace(number.getNumber(), employee);
        this->by_phone_substr_search.emplace(number.getNumber(), employee);
    }
}

void InternalEmployeeDataBase::delMorePhone(
    const BigUint& id, size_t index, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    InternalEmployeePtr employee = id_it->second;
    if (employee->getMorePhoneNumbers().size() <= index) return;

    auto old_number = employee->getMorePhoneNumbers()[index];

    if (employee->delMorePhoneNumber(index, changer)) {
        std::string old_number_str = old_number.getNumber();

        safeRemoveFromMap(this->by_phone, old_number_str, employee, __LINE__, "by_phone");
        safeRemoveFromMap(
            this->by_phone_substr_search,
            old_number_str,
            employee,
            __LINE__,
            "by_phone_substr_search"
        );
    }
}

void InternalEmployeeDataBase::changeDepartment(
    const BigUint& id, const OptionalStr& department, const InternalEmployeePtr& changer
)
{
    auto id_it = by_id.find(id);
    if (id_it == by_id.end()) return;

    InternalEmployeePtr employee = id_it->second;

    const auto&         old_department = employee->getDepartment();

    if (employee->setDepartment(department, changer)) {
        if (old_department) {
            safeRemoveFromMap(
                this->by_department, old_department.value(), employee, __LINE__, "by_department"
            );
        }
        if (department) {
            this->by_department.emplace(department.value(), employee);
        }
    }
}

void InternalEmployeeDataBase::changeStatus(
    const BigUint& id, const EmployeeStatus status, const InternalEmployeePtr& changer
)
{
    auto id_it = by_id.find(id);
    if (id_it == by_id.end()) return;

    InternalEmployeePtr employee = id_it->second;

    EmployeeStatus      old_status = employee->getStatus();

    if (employee->setStatus(status, changer)) {
        if (old_status != EmployeeStatus::other) {
            safeRemoveFromVector(this->by_status, old_status, employee, __LINE__, "by_status");
        } else if (employee->getOtherStatus()) {
            const std::string& status = employee->getOtherStatus().value();
            safeRemoveFromVector(
                this->by_other_status, status, employee, __LINE__, "by_other_status"
            );
        }
        if (status != EmployeeStatus::other) {
            this->by_status[status].push_back(employee);
        }
    }
}

void InternalEmployeeDataBase::changeOtherStatus(
    const BigUint& id, const OptionalStr& status, const InternalEmployeePtr& changer
)
{
    auto id_it = by_id.find(id);
    if (id_it == by_id.end()) return;

    InternalEmployeePtr employee = id_it->second;

    const auto&         old_status = employee->getOtherStatus();

    if (employee->setOtherStatus(status, changer)) {
        if (old_status) {
            safeRemoveFromVector(
                this->by_other_status, old_status.value(), employee, __LINE__, "by_other_status"
            );
        } else if (employee->getStatus() != EmployeeStatus::other) {
            const auto status = employee->getStatus();
            safeRemoveFromVector(this->by_status, status, employee, __LINE__, "by_status");
        }
        if (status) {
            this->by_other_status[status.value()].push_back(employee);
        }
    }
}

void InternalEmployeeDataBase::changeAccessRole(
    const BigUint& id, const AccessRole role, const InternalEmployeePtr& changer
)
{
    auto id_it = by_id.find(id);
    if (id_it == by_id.end()) return;

    InternalEmployeePtr employee = id_it->second;

    AccessRole          old_role = employee->getAccessRole();

    if (employee->setAccessRole(role, changer)) {
        if (old_role != AccessRole::other) {
            safeRemoveFromVector(
                this->by_access_role, old_role, employee, __LINE__, "by_access_role"
            );
        } else if (employee->getOtherRole()) {
            const std::string& role = employee->getOtherRole().value();
            safeRemoveFromVector(
                this->by_other_access_role, role, employee, __LINE__, "by_other_access_role"
            );
        }
        if (role != AccessRole::other) {
            this->by_access_role[role].push_back(employee);
        }
    }
}

void InternalEmployeeDataBase::changeOtherAccessRole(
    const BigUint& id, const OptionalStr& role, const InternalEmployeePtr& changer
)
{
    auto id_it = by_id.find(id);
    if (id_it == by_id.end()) return;

    InternalEmployeePtr employee = id_it->second;

    const auto&         old_role = employee->getOtherRole();

    if (employee->setOtherRole(role, changer)) {
        if (old_role) {
            safeRemoveFromVector(
                this->by_other_access_role,
                old_role.value(),
                employee,
                __LINE__,
                "by_other_access_role"
            );
        } else if (employee->getAccessRole() != AccessRole::other) {
            const auto role = employee->getAccessRole();
            safeRemoveFromVector(this->by_access_role, role, employee, __LINE__, "by_access_role");
        }
        if (role) {
            this->by_other_access_role[role.value()].push_back(employee);
        }
    }
}

void InternalEmployeeDataBase::changeTimeZone(
    const BigUint& id, const int time_zone, const InternalEmployeePtr& changer
)
{
    auto id_it = by_id.find(id);
    if (id_it == by_id.end()) return;

    InternalEmployeePtr employee = id_it->second;

    const int           old_time_zone = employee->getTimeZone();

    if (employee->setTimeZone(time_zone, changer)) {
        safeRemoveFromVector(this->by_time_zone, old_time_zone, employee, __LINE__, "by_time_zone");
        this->by_time_zone[time_zone].push_back(employee);
    }
}

void InternalEmployeeDataBase::changePosition(
    const BigUint& id, const OptionalStr& position, const InternalEmployeePtr& changer
)
{
    auto id_it = by_id.find(id);
    if (id_it == by_id.end()) return;

    InternalEmployeePtr employee = id_it->second;

    const auto          old_position = employee->getPosition();

    if (employee->setPosition(position, changer)) {
        if (old_position) {
            safeRemoveFromMap(
                this->by_position, old_position.value(), employee, __LINE__, "by_position"
            );
        }
        if (position) {
            this->by_position.emplace(position.value(), employee);
        }
    }
}

void InternalEmployeeDataBase::changeManager(
    const BigUint& id, const WeakInternalEmployee& manager, const InternalEmployeePtr& changer
)
{
    auto id_it = by_id.find(id);
    if (id_it == by_id.end()) return;

    InternalEmployeePtr employee = id_it->second;

    const auto          old_manager = employee->getManager();

    if (employee->setManager(manager, changer)) {
        if (!old_manager.expired()) {
            safeRemoveFromVector(
                this->by_manager, old_manager.lock()->getId(), employee, __LINE__, "by_manager"
            );
        }
        if (!manager.expired()) {
            this->by_manager[manager.lock()->getId()].push_back(employee);
        }
    }
}

void InternalEmployeeDataBase::changeIsActive(
    const BigUint& id, const bool is_active, const InternalEmployeePtr& changer
)
{
    auto id_it = by_id.find(id);
    if (id_it == by_id.end()) return;

    InternalEmployeePtr employee = id_it->second;

    const bool          old_active = employee->getIsActive();

    if (employee->setIsActive(is_active, changer)) {
        safeRemoveFromVector(this->by_is_active, old_active, employee, __LINE__, "by_is_active");
        this->by_is_active[is_active].push_back(employee);
    }
}

void InternalEmployeeDataBase::changeSalesTerritory(
    const BigUint& id, OptionalStr& sales_territory, const InternalEmployeePtr& changer
)
{
    auto id_it = by_id.find(id);
    if (id_it == by_id.end()) return;

    InternalEmployeePtr employee = id_it->second;

    const auto          old_sales = employee->getSalesTerritory();

    if (employee->setSalesTerritory(sales_territory, changer)) {
        if (old_sales) {
            safeRemoveFromMap(
                this->by_sales_territory,
                old_sales.value(),
                employee,
                __LINE__,
                "by_sales_territory"
            );
        }
        if (sales_territory) {
            this->by_sales_territory.emplace(sales_territory.value(), employee);
        }
    }
}

void InternalEmployeeDataBase::safeRemoveFromMap(
    auto&                      map,
    const auto&                key,
    const InternalEmployeePtr& employee,
    const size_t               line,
    const std::string&         index_name
)
{
    auto range = map.equal_range(key);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second == employee) {
            map.erase(it);
            return;
        }
    }
    this->logEmptyContainer(__FILE__, line, employee->getId().num, index_name);
}

void InternalEmployeeDataBase::safeRemoveFromVector(
    auto&                      map,
    const auto&                key,
    const InternalEmployeePtr& employee,
    const size_t               line,
    const std::string&         index_name
)
{
    auto& vec = map[key];
    if (vec.empty()) {
        this->logEmptyContainer(__FILE__, line, employee->getId().num, index_name);

    } else {
        vec.erase(std::remove(vec.begin(), vec.end(), employee), vec.end());
        if (vec.empty()) {
            map.erase(key);
        }
    }
}

void InternalEmployeeDataBase::logEmptyContainer(
    const std::string& file,
    const size_t       line,
    const std::string& employee_id,
    const std::string& index_name
)
{
    EventLog::getInstance().log(
        LOG_LEVEL::ERROR,
        file,
        line,
        "Data inconsistency in " + index_name + "\nInternal Employee: " + employee_id +
            "\nExpected entry is missing."
    );
}