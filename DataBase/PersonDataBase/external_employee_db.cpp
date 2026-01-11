#include "external_employee_db.hpp"

#include <algorithm>
#include <string>

#include "Company/ExternalCompany/external_company.hpp"
#include "Logger/events_log.hpp"
#include "Person/Employee/external_employee.hpp"
#include "TenantContext/tenant_context.hpp"

const std::vector<ExternalEmployeePtr> ExternalEmployeeDataBase::empty_vector;

//
void ExternalEmployeeDataBase::add(const ExternalEmployeePtr& employee)
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

    if (employee->getCompany()) {
        this->by_company[employee->getCompany()->getId()].push_back(employee);
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

    if (employee->getDecisionInfluence()) {
        this->by_influence_level[employee->getDecisionInfluence().value()].push_back(employee);
    }
    this->by_time_zone[employee->getTimeZone()].push_back(employee);
    if (employee->getJobTitle()) {
        this->by_job_title.emplace(employee->getJobTitle().value(), employee);
    }
    if (employee->getDepartment()) {
        this->by_department.emplace(employee->getDepartment().value(), employee);
    }
}

void ExternalEmployeeDataBase::soft_remove(const BigUint& id, const Date& remove_date)
{
    auto employee_it = by_id.find(id);
    if (employee_it == by_id.end()) {
        return;
    }

    ExternalEmployeePtr employee = employee_it->second;

    safeRemoveFromMap(by_name, employee->getName(), employee, __LINE__, "by_name");

    std::string lower_name = employee->getName();
    std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), ::tolower);
    safeRemoveFromMap(
        this->by_name_substr_search, lower_name, employee, __LINE__, "by_name_substr_search"
    );

    if (employee->getEmail().has_value()) {
        const std::string& email = employee->getEmail().value();
        safeRemoveFromMap(this->by_email, email, employee, __LINE__, "by_email");

        std::string lower_email = email;
        std::transform(lower_email.begin(), lower_email.end(), lower_email.begin(), ::tolower);
        safeRemoveFromMap(
            this->by_email_substr_search, lower_email, employee, __LINE__, "by_email_substr_search"
        );
    }

    for (const std::string& email : employee->getMoreEmails()) {
        safeRemoveFromMap(this->by_email, email, employee, __LINE__, "by_email");

        std::string lower_email = email;
        std::transform(lower_email.begin(), lower_email.end(), lower_email.begin(), ::tolower);
        safeRemoveFromMap(
            this->by_email_substr_search, lower_email, employee, __LINE__, "by_email_substr_search"
        );
    }

    if (employee->getPhoneNumber()) {
        const std::string& phone = employee->getPhoneNumber()->getNumber();
        safeRemoveFromMap(this->by_phone, phone, employee, __LINE__, "by_phone");
        safeRemoveFromMap(
            this->by_phone_substr_search, phone, employee, __LINE__, "by_phone_substr_search"
        );
    }

    for (const auto& phone : employee->getMorePhoneNumbers()) {
        const std::string& phone_str = phone.getNumber();
        safeRemoveFromMap(this->by_phone, phone_str, employee, __LINE__, "by_phone");
        safeRemoveFromMap(
            this->by_phone_substr_search, phone_str, employee, __LINE__, "by_phone_substr_search"
        );
    }

    if (employee->getCompany()) {
        const CompanyId& company_id = employee->getCompany()->getId();
        safeRemoveFromVector(this->by_company, company_id, employee, __LINE__, "by_company");
    }

    if (employee->getStatus() != EmployeeStatus::other) {
        const auto& status = employee->getStatus();
        safeRemoveFromVector(this->by_status, status, employee, __LINE__, "by_status");
    } else if (employee->getOtherStatus()) {
        const std::string& status = employee->getOtherStatus().value();
        safeRemoveFromVector(this->by_other_status, status, employee, __LINE__, "by_other_status");
    }

    if (employee->getAccessRole() != AccessRole::other) {
        const auto& role = employee->getAccessRole();
        safeRemoveFromVector(this->by_access_role, role, employee, __LINE__, "by_access_role");
    } else if (employee->getOtherRole()) {
        const std::string& role = employee->getOtherRole().value();
        safeRemoveFromVector(
            this->by_other_access_role, role, employee, __LINE__, "by_other_access_role"
        );
    }

    if (employee->getDecisionInfluence()) {
        const auto& influence = employee->getDecisionInfluence().value();
        safeRemoveFromVector(
            this->by_influence_level, influence, employee, __LINE__, "by_decision_influence"
        );
    }
    safeRemoveFromVector(
        this->by_time_zone, employee->getTimeZone(), employee, __LINE__, "by_time_zone"
    );

    if (employee->getJobTitle()) {
        const std::string& job_title = employee->getJobTitle().value();
        safeRemoveFromMap(this->by_job_title, job_title, employee, __LINE__, "by_job_title");
    }

    if (employee->getDepartment()) {
        const std::string& department = employee->getDepartment().value();
        safeRemoveFromMap(this->by_department, department, employee, __LINE__, "by_department");
    }
    this->removed.push_back({remove_date, employee});

    by_id.erase(employee_it);
}

void ExternalEmployeeDataBase::hard_remove(const size_t index, TenantContext& context)
{
    if (index < this->removed.size()) {
        const auto& employee    = removed[index].second;
        auto        employee_id = employee->getId();

        context.task_data_base.removeParty(employee_id);

        this->removed.erase(this->removed.begin() + index);
    }
}

auto ExternalEmployeeDataBase::size() const -> size_t { return this->by_id.size(); }

bool ExternalEmployeeDataBase::empty() const { return this->by_id.empty(); }

auto ExternalEmployeeDataBase::getAll() const
    -> const std::unordered_map<BigUint, ExternalEmployeePtr>&
{
    return this->by_id;
}

auto ExternalEmployeeDataBase::getByName() const
    -> const std::unordered_multimap<std::string, ExternalEmployeePtr>&
{
    return this->by_name;
}

auto ExternalEmployeeDataBase::getByEmail() const
    -> const std::unordered_multimap<std::string, ExternalEmployeePtr>&
{
    return this->by_email;
}

auto ExternalEmployeeDataBase::getByPhone() const
    -> const std::unordered_multimap<std::string, ExternalEmployeePtr>&
{
    return this->by_phone;
}

auto ExternalEmployeeDataBase::getByCompany() const
    -> const std::unordered_map<CompanyId, std::vector<ExternalEmployeePtr>>&
{
    return this->by_company;
}

auto ExternalEmployeeDataBase::getByStatus() const
    -> const std::unordered_map<EmployeeStatus, std::vector<ExternalEmployeePtr>>&
{
    return this->by_status;
}

auto ExternalEmployeeDataBase::getByOtherStatus() const
    -> const std::unordered_map<std::string, std::vector<ExternalEmployeePtr>>&
{
    return this->by_other_status;
}

auto ExternalEmployeeDataBase::getByAccessRole() const
    -> const std::unordered_map<AccessRole, std::vector<ExternalEmployeePtr>>&
{
    return this->by_access_role;
}

auto ExternalEmployeeDataBase::getByOtherAccessRole() const
    -> const std::unordered_map<std::string, std::vector<ExternalEmployeePtr>>&
{
    return this->by_other_access_role;
}

auto ExternalEmployeeDataBase::getByInfluenceLevel() const
    -> const std::unordered_map<ExternalEmployee::InfluenceLevel, std::vector<ExternalEmployeePtr>>&
{
    return this->by_influence_level;
}

auto ExternalEmployeeDataBase::getByTimeZone() const
    -> const std::unordered_map<int, std::vector<ExternalEmployeePtr>>&
{
    return this->by_time_zone;
}

auto ExternalEmployeeDataBase::getByJobTitle() const
    -> const std::unordered_multimap<std::string, ExternalEmployeePtr>&
{
    return this->by_job_title;
}

auto ExternalEmployeeDataBase::getByDepartment() const
    -> const std::unordered_multimap<std::string, ExternalEmployeePtr>&
{
    return this->by_department;
}

auto ExternalEmployeeDataBase::getRemoved() const
    -> const std::vector<std::pair<Date, ExternalEmployeePtr>>&
{
    return this->removed;
}

auto ExternalEmployeeDataBase::findById(const BigUint& id) const -> const ExternalEmployeePtr
{
    auto employee = this->by_id.find(id);
    if (employee != this->by_id.end()) {
        return employee->second;
    }
    return nullptr;
}

auto ExternalEmployeeDataBase::findByName(const std::string& name) const
    -> const std::vector<ExternalEmployeePtr>
{
    auto employees = this->by_name.equal_range(name);
    if (employees.first == employees.second) return empty_vector;

    std::vector<ExternalEmployeePtr> result;
    for (auto it = employees.first; it != employees.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto ExternalEmployeeDataBase::findByNameSubstr(const std::string& substr) const
    -> const std::vector<ExternalEmployeePtr>
{
    if (substr.empty()) return empty_vector;
    std::string key = substr;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    auto first = this->by_name_substr_search.lower_bound(key);
    key.back()++;
    auto second = this->by_name_substr_search.lower_bound(key);

    if (first == second) return empty_vector;

    std::vector<ExternalEmployeePtr> result;
    for (auto it = first; it != second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto ExternalEmployeeDataBase::findByEmail(const std::string& email) const
    -> const std::vector<ExternalEmployeePtr>
{
    auto employees = this->by_email.equal_range(email);
    if (employees.first == employees.second) return empty_vector;

    std::vector<ExternalEmployeePtr> result;
    for (auto it = employees.first; it != employees.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto ExternalEmployeeDataBase::findByEmailSubstr(const std::string& substr) const
    -> const std::vector<ExternalEmployeePtr>
{
    if (substr.empty()) return empty_vector;
    std::string key = substr;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    auto first = this->by_email_substr_search.lower_bound(key);
    key.back()++;
    auto second = this->by_email_substr_search.lower_bound(key);

    if (first == second) return empty_vector;

    std::vector<ExternalEmployeePtr> result;
    for (auto it = first; it != second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto ExternalEmployeeDataBase::findByPhone(const std::string& phone) const
    -> const std::vector<ExternalEmployeePtr>
{
    auto employees = this->by_phone.equal_range(phone);
    if (employees.first == employees.second) return empty_vector;

    std::vector<ExternalEmployeePtr> result;
    for (auto it = employees.first; it != employees.second; ++it) {
        result.push_back(it->second);
    }

    return result;
}

auto ExternalEmployeeDataBase::findByPhoneSubstr(const std::string& substr) const
    -> const std::vector<ExternalEmployeePtr>
{
    if (substr.empty()) return empty_vector;
    std::string key = substr;

    auto        first = this->by_phone_substr_search.lower_bound(key);
    key.back()++;
    auto second = this->by_phone_substr_search.lower_bound(key);

    if (first == second) return empty_vector;

    std::vector<ExternalEmployeePtr> result;
    for (auto it = first; it != second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto ExternalEmployeeDataBase::findByCompany(const CompanyId& id) const
    -> const std::vector<ExternalEmployeePtr>&
{
    auto employees = this->by_company.find(id);
    if (employees != this->by_company.end()) {
        return employees->second;
    }
    return empty_vector;
}

auto ExternalEmployeeDataBase::findByStatus(const EmployeeStatus status) const
    -> const std::vector<ExternalEmployeePtr>&
{
    auto it = this->by_status.find(status);
    if (it == this->by_status.end()) return empty_vector;
    return it->second;
}

auto ExternalEmployeeDataBase::findByOtherStatus(const std::string& status) const
    -> const std::vector<ExternalEmployeePtr>&
{
    auto it = this->by_other_status.find(status);
    if (it == this->by_other_status.end()) return empty_vector;
    return it->second;
}

auto ExternalEmployeeDataBase::findByAccessRole(const AccessRole role) const
    -> const std::vector<ExternalEmployeePtr>&
{
    auto it = this->by_access_role.find(role);
    if (it == this->by_access_role.end()) return empty_vector;
    return it->second;
}

auto ExternalEmployeeDataBase::findByOtherAccessRole(const std::string& role) const
    -> const std::vector<ExternalEmployeePtr>&
{
    auto it = this->by_other_access_role.find(role);
    if (it == this->by_other_access_role.end()) return empty_vector;
    return it->second;
}

auto ExternalEmployeeDataBase::findByInfluence(const ExternalEmployee::InfluenceLevel level) const
    -> const std::vector<ExternalEmployeePtr>&
{
    auto it = this->by_influence_level.find(level);
    if (it == this->by_influence_level.end()) return empty_vector;
    return it->second;
}

auto ExternalEmployeeDataBase::findByTimeZone(const int time_zone) const
    -> const std::vector<ExternalEmployeePtr>&
{
    auto it = this->by_time_zone.find(time_zone);
    if (it == this->by_time_zone.end()) return empty_vector;
    return it->second;
}

auto ExternalEmployeeDataBase::findByJobTitle(const std::string& job_title) const
    -> const std::vector<ExternalEmployeePtr>
{
    auto range = this->by_job_title.equal_range(job_title);
    if (range.first == range.second) return empty_vector;
    std::vector<ExternalEmployeePtr> result;
    for (auto it = range.first; it != range.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto ExternalEmployeeDataBase::findByDepartment(const std::string& department) const
    -> const std::vector<ExternalEmployeePtr>
{
    auto range = this->by_department.equal_range(department);
    if (range.first == range.second) return empty_vector;
    std::vector<ExternalEmployeePtr> result;
    for (auto it = range.first; it != range.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

void ExternalEmployeeDataBase::changeName(
    const BigUint& id, const std::string& name, const InternalEmployeePtr& changer
)
{
    auto id_it = by_id.find(id);
    if (id_it == by_id.end()) return;

    ExternalEmployeePtr employee = id_it->second;
    std::string         old_name = employee->getName();

    if (employee->setName(name, changer)) {
        safeRemoveFromMap(by_name, old_name, employee, __LINE__, "by_name");

        std::string old_lower = old_name;
        std::transform(old_lower.begin(), old_lower.end(), old_lower.begin(), ::tolower);
        safeRemoveFromMap(
            by_name_substr_search, old_lower, employee, __LINE__, "by_name_substr_search"
        );

        by_name.emplace(name, employee);

        std::string new_lower = name;
        std::transform(new_lower.begin(), new_lower.end(), new_lower.begin(), ::tolower);
        by_name_substr_search.emplace(new_lower, employee);
    }
}

void ExternalEmployeeDataBase::changeEmail(
    const BigUint& id, const OptionalStr& email, const InternalEmployeePtr& changer
)
{
    auto id_it = by_id.find(id);
    if (id_it == by_id.end()) return;

    ExternalEmployeePtr employee  = id_it->second;
    OptionalStr         old_email = employee->getEmail();

    if (employee->setEmail(email, changer)) {
        if (old_email.has_value()) {
            const std::string& old_str = old_email.value();
            safeRemoveFromMap(by_email, old_str, employee, __LINE__, "by_email");

            std::string old_lower = old_str;
            std::transform(old_lower.begin(), old_lower.end(), old_lower.begin(), ::tolower);
            safeRemoveFromMap(
                by_email_substr_search, old_lower, employee, __LINE__, "by_email_substr_search"
            );
        }

        if (email.has_value()) {
            const std::string& new_str = email.value();
            by_email.emplace(new_str, employee);

            std::string new_lower = new_str;
            std::transform(new_lower.begin(), new_lower.end(), new_lower.begin(), ::tolower);
            by_email_substr_search.emplace(new_lower, employee);
        }
    }
}

void ExternalEmployeeDataBase::addMoreEmail(
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

void ExternalEmployeeDataBase::delMoreEmail(
    const BigUint& id, size_t index, const InternalEmployeePtr& changer
)
{
    auto id_it = by_id.find(id);
    if (id_it == by_id.end()) return;

    ExternalEmployeePtr employee = id_it->second;
    if (index >= employee->getMoreEmails().size()) return;

    std::string old_email = employee->getMoreEmails()[index];

    if (employee->delMoreEmails(index, changer)) {
        safeRemoveFromMap(by_email, old_email, employee, __LINE__, "by_email");

        std::string lower_email = old_email;
        std::transform(lower_email.begin(), lower_email.end(), lower_email.begin(), ::tolower);
        safeRemoveFromMap(
            by_email_substr_search, lower_email, employee, __LINE__, "by_email_substr_search"
        );
    }
}

void ExternalEmployeeDataBase::changePhone(
    const BigUint& id, const PhoneNumberPtr& number, const InternalEmployeePtr& changer
)
{
    auto id_it = by_id.find(id);
    if (id_it == by_id.end()) return;

    ExternalEmployeePtr employee   = id_it->second;
    PhoneNumberPtr      old_number = employee->getPhoneNumber();

    if (employee->setPhoneNumber(number, changer)) {
        if (old_number) {
            const std::string& old_phone = old_number->getNumber();
            safeRemoveFromMap(by_phone, old_phone, employee, __LINE__, "by_phone");
            safeRemoveFromMap(
                by_phone_substr_search, old_phone, employee, __LINE__, "by_phone_substr_search"
            );
        }

        if (number) {
            const std::string& new_phone = number->getNumber();
            by_phone.emplace(new_phone, employee);
            by_phone_substr_search.emplace(new_phone, employee);
        }
    }
}

void ExternalEmployeeDataBase::addMorePhone(
    const BigUint& id, const PhoneNumber& number, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    ExternalEmployeePtr employee = id_it->second;
    if (employee->addMorePhoneNumber(number, changer)) {
        this->by_phone.emplace(number.getNumber(), employee);
        this->by_phone_substr_search.emplace(number.getNumber(), employee);
    }
}

void ExternalEmployeeDataBase::delMorePhone(
    const BigUint& id, size_t index, const InternalEmployeePtr& changer
)
{
    auto id_it = by_id.find(id);
    if (id_it == by_id.end()) return;

    ExternalEmployeePtr employee = id_it->second;
    if (index >= employee->getMorePhoneNumbers().size()) return;

    PhoneNumber old_number = employee->getMorePhoneNumbers()[index];

    if (employee->delMorePhoneNumber(index, changer)) {
        const std::string& phone_str = old_number.getNumber();
        safeRemoveFromMap(by_phone, phone_str, employee, __LINE__, "by_phone");
        safeRemoveFromMap(
            by_phone_substr_search, phone_str, employee, __LINE__, "by_phone_substr_search"
        );
    }
}

void ExternalEmployeeDataBase::changeCompany(
    const BigUint& id, const ExternalCompanyPtr& company, const InternalEmployeePtr& changer
)
{
    auto id_it = by_id.find(id);
    if (id_it == by_id.end()) return;

    ExternalEmployeePtr employee    = id_it->second;
    ExternalCompanyPtr  old_company = employee->getCompany();

    if (employee->setCompany(company, changer)) {
        if (old_company) {
            CompanyId old_id = old_company->getId();
            safeRemoveFromVector(by_company, old_id, employee, __LINE__, "by_company");
        }

        if (company) {
            CompanyId new_id = company->getId();
            by_company[new_id].push_back(employee);
        }
    }
}

void ExternalEmployeeDataBase::changeStatus(
    const BigUint& id, const EmployeeStatus status, const InternalEmployeePtr& changer
)
{
    auto id_it = by_id.find(id);
    if (id_it == by_id.end()) return;

    ExternalEmployeePtr employee = id_it->second;

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

void ExternalEmployeeDataBase::changeOtherStatus(
    const BigUint& id, const OptionalStr& status, const InternalEmployeePtr& changer
)
{
    auto id_it = by_id.find(id);
    if (id_it == by_id.end()) return;

    ExternalEmployeePtr employee = id_it->second;

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

void ExternalEmployeeDataBase::changeAccessRole(
    const BigUint& id, const AccessRole role, const InternalEmployeePtr& changer
)
{
    auto id_it = by_id.find(id);
    if (id_it == by_id.end()) return;

    ExternalEmployeePtr employee = id_it->second;

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

void ExternalEmployeeDataBase::changeOtherAccessRole(
    const BigUint& id, const OptionalStr& role, const InternalEmployeePtr& changer
)
{
    auto id_it = by_id.find(id);
    if (id_it == by_id.end()) return;

    ExternalEmployeePtr employee = id_it->second;

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

void ExternalEmployeeDataBase::changeInfluence(
    const BigUint&                                        id,
    const std::optional<ExternalEmployee::InfluenceLevel> level,
    const InternalEmployeePtr&                            changer
)
{
    auto id_it = by_id.find(id);
    if (id_it == by_id.end()) return;

    ExternalEmployeePtr employee = id_it->second;

    const auto          old_level = employee->getDecisionInfluence();

    if (employee->setDecisionInfluence(level, changer)) {
        if (old_level) {
            safeRemoveFromVector(
                this->by_influence_level,
                old_level.value(),
                employee,
                __LINE__,
                "by_decision_influence"
            );
        }
        if (level) {
            this->by_influence_level[level.value()].push_back(employee);
        }
    }
}

void ExternalEmployeeDataBase::changeTimeZone(
    const BigUint& id, const int time_zone, const InternalEmployeePtr& changer
)
{
    auto id_it = by_id.find(id);
    if (id_it == by_id.end()) return;

    ExternalEmployeePtr employee = id_it->second;

    const int           old_time_zone = employee->getTimeZone();

    if (employee->setTimeZone(time_zone, changer)) {
        safeRemoveFromVector(this->by_time_zone, old_time_zone, employee, __LINE__, "by_time_zone");
        this->by_time_zone[time_zone].push_back(employee);
    }
}

void ExternalEmployeeDataBase::changeJobTitle(
    const BigUint& id, const OptionalStr& title, const InternalEmployeePtr& changer
)
{
    auto id_it = by_id.find(id);
    if (id_it == by_id.end()) return;

    ExternalEmployeePtr employee = id_it->second;

    const auto&         old_title = employee->getJobTitle();

    if (employee->setJobTitle(title, changer)) {
        if (old_title) {
            safeRemoveFromMap(
                this->by_job_title, old_title.value(), employee, __LINE__, "by_job_title"
            );
        }
        if (title) {
            this->by_job_title.emplace(title.value(), employee);
        }
    }
}

void ExternalEmployeeDataBase::changeDepartment(
    const BigUint& id, const OptionalStr& department, const InternalEmployeePtr& changer
)
{
    auto id_it = by_id.find(id);
    if (id_it == by_id.end()) return;

    ExternalEmployeePtr employee = id_it->second;

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

void ExternalEmployeeDataBase::removeCompany(const BigUint& id) { this->by_company.erase(id); }

void ExternalEmployeeDataBase::safeRemoveFromMap(
    auto&                      map,
    const auto&                key,
    const ExternalEmployeePtr& employee,
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

void ExternalEmployeeDataBase::safeRemoveFromVector(
    auto&                      map,
    const auto&                key,
    const ExternalEmployeePtr& employee,
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

void ExternalEmployeeDataBase::logEmptyContainer(
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
        "Data inconsistency in " + index_name + "\nExternal Employee: " + employee_id +
            "\nExpected entry is missing."
    );
}