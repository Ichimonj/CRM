#include "external_employee_db.hpp"

#include "external_company.hpp"
#include "external_employee.hpp"
void ExternalEmployeeDataBase::add(const ExternalEmployeePtr& person)
{
    if (person == nullptr) return;

    if (this->by_id.find(person->getId()) != this->by_id.end()) {
        return;
    }
    this->by_id[person->getId()] = person;
    this->by_name.emplace(person->getName(), person);

    if (person->getEmail()) {
        this->by_email.emplace(person->getEmail().value(), person);
    }
    for (auto& email : person->getMoreEmails()) {
        this->by_email.emplace(email, person);
    }

    if (person->getPhoneNumber()) {
        this->by_phone.emplace(person->getPhoneNumber()->getNumber(), person);
    }
    for (auto& number : person->getMorePhoneNumbers()) {
        this->by_phone.emplace(number.getNumber(), person);
    }

    if (person->getCompany()) {
        this->by_company[person->getCompany()->getId()].push_back(person);
    }
}

void ExternalEmployeeDataBase::remove(const BigUint& id)
{
    auto person = this->by_id.find(id);
    if (person == this->by_id.end()) {
        return;
    }

    auto name_range = this->by_name.equal_range(person->second->getName());
    for (auto it = name_range.first; it != name_range.second; ++it) {
        if (it->second->getId() == id) {
            this->by_name.erase(it);
            break;
        }
    }

    if (person->second->getEmail().has_value()) {
        auto email_range = this->by_email.equal_range(person->second->getEmail().value());
        for (auto it = email_range.first; it != email_range.second; ++it) {
            if (it->second->getId() == id) {
                this->by_email.erase(it);
                break;
            }
        }
    }

    for (auto& email : person->second->getMoreEmails()) {
        auto email_range = this->by_email.equal_range(email);
        for (auto it = email_range.first; it != email_range.second; ++it) {
            if (it->second->getId() == id) {
                this->by_email.erase(it);
                break;
            }
        }
    }

    if (person->second->getPhoneNumber()) {
        auto persons = this->by_phone.equal_range(person->second->getPhoneNumber()->getNumber());

        for (auto it = persons.first; it != persons.second; ++it) {
            if (it->second == person->second) {
                this->by_phone.erase(it);
                break;
            }
        }
    }

    for (auto& phone_number : person->second->getMorePhoneNumbers()) {
        auto persons = this->by_phone.equal_range(phone_number.getNumber());

        for (auto it = persons.first; it != persons.second; ++it) {
            if (it->second == person->second) {
                this->by_phone.erase(it);
                break;
            }
        }
    }

    if (person->second->getCompany()) {
        CompanyId company_id = person->second->getCompany()->getId();

        auto      company_it = this->by_company.find(company_id);
        if (company_it != by_company.end()) {
            auto& vec = company_it->second;
            vec.erase(std::remove(vec.begin(), vec.end(), person->second), vec.end());

            if (vec.empty()) {
                this->by_company.erase(company_it);
            }
        }
    }

    this->by_id.erase(person);
}

auto ExternalEmployeeDataBase::getById() const
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

auto ExternalEmployeeDataBase::findById(const BigUint& id) const -> const ExternalEmployeePtr&
{
    auto person = this->by_id.find(id);
    if (person != this->by_id.end()) {
        return person->second;
    }
    return nullptr;
}

auto ExternalEmployeeDataBase::findByName(const std::string& name) const
    -> const std::vector<ExternalEmployeePtr>
{
    auto persons = this->by_name.equal_range(name);
    if (persons.first == persons.second) {
        return std::vector<ExternalEmployeePtr>{};
    }

    std::vector<ExternalEmployeePtr> result;
    for (auto it = persons.first; it != persons.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto ExternalEmployeeDataBase::findByEmail(const std::string& email) const
    -> const std::vector<ExternalEmployeePtr>
{
    auto persons = this->by_email.equal_range(email);
    if (persons.first == persons.second) {
        return std::vector<ExternalEmployeePtr>{};
    }
    std::vector<ExternalEmployeePtr> result;
    for (auto it = persons.first; it != persons.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto ExternalEmployeeDataBase::findByPhone(const std::string& phone) const
    -> const std::vector<ExternalEmployeePtr>
{
    auto persons = this->by_phone.equal_range(phone);
    if (persons.first == persons.second) {
        return std::vector<ExternalEmployeePtr>{};
    }
    std::vector<ExternalEmployeePtr> result;
    for (auto it = persons.first; it != persons.second; ++it) {
        result.push_back(it->second);
    }

    return result;
}

auto ExternalEmployeeDataBase::findByCompany(const CompanyId& id) const
    -> const std::vector<ExternalEmployeePtr>
{
    auto persons = this->by_company.find(id);
    if (persons != this->by_company.end()) {
        return persons->second;
    }
    return std::vector<ExternalEmployeePtr>{};
}

void ExternalEmployeeDataBase::changeName(
    const BigUint& id, const std::string& name, const InternalEmployeePtr& changer
)
{
    auto person = this->by_id.find(id);
    if (person == this->by_id.end()) return;

    auto old_name = person->second->getName();

    if (person->second->setName(name, changer)) {
        auto persons = this->by_name.equal_range(old_name);
        for (auto it = persons.first; it != persons.second; ++it) {
            if (it->second == person->second) {
                this->by_name.erase(it);
                break;
            }
        }
        this->by_name.emplace(name, person->second);
    }
}

void ExternalEmployeeDataBase::changeEmail(
    const BigUint& id, const OptionalStr& email, const InternalEmployeePtr& changer
)
{
    auto person = this->by_id.find(id);
    if (person == this->by_id.end()) return;

    auto old_email = person->second->getEmail();

    if (person->second->setEmail(email, changer)) {
        if (old_email.has_value()) {
            auto persons = this->by_email.equal_range(old_email.value());
            for (auto it = persons.first; it != persons.second; ++it) {
                if (it->second == person->second) {
                    this->by_email.erase(it);
                    break;
                }
            }
        }
        if (email.has_value()) {
            this->by_email.emplace(email.value(), person->second);
        }
    }
}

void ExternalEmployeeDataBase::addMoreEmail(
    const BigUint& id, const std::string& email, const InternalEmployeePtr& changer
)
{
    auto person = this->by_id.find(id);
    if (person == this->by_id.end()) return;

    if (person->second->addMoreEmails(email, changer)) {
        this->by_email.emplace(email, person->second);
    }
}

void ExternalEmployeeDataBase::delMoreEmail(
    const BigUint& id, size_t index, const InternalEmployeePtr& changer
)
{
    auto person = this->by_id.find(id);
    if (person == this->by_id.end()) return;

    if (person->second->getMoreEmails().size() <= index) return;

    auto old_email = person->second->getMoreEmails()[index];

    if (person->second->delMoreEmails(index, changer)) {
        auto persons = this->by_email.equal_range(old_email);
        for (auto it = persons.first; it != persons.second; ++it) {
            if (it->second == person->second) {
                this->by_email.erase(it);
                break;
            }
        }
    }
}

void ExternalEmployeeDataBase::changePhone(
    const BigUint& id, const PhoneNumberPtr& number, const InternalEmployeePtr& changer
)
{
    auto person = this->by_id.find(id);
    if (person == this->by_id.end()) return;

    auto old_number = person->second->getPhoneNumber();

    if (person->second->setPhoneNumber(number, changer)) {
        if (old_number) {
            auto persons = this->by_phone.equal_range(old_number->getNumber());
            for (auto it = persons.first; it != persons.second; ++it) {
                if (it->second == person->second) {
                    this->by_phone.erase(it);
                    break;
                }
            }
        }
        if (number) {
            this->by_phone.emplace(number->getNumber(), person->second);
        }
    }
}

void ExternalEmployeeDataBase::addMorePhone(
    const BigUint& id, const PhoneNumber& number, const InternalEmployeePtr& changer
)
{
    auto person = this->by_id.find(id);
    if (person == this->by_id.end()) return;

    if (person->second->addMorePhoneNumber(number, changer)) {
        this->by_phone.emplace(number.getNumber(), person->second);
    }
}

void ExternalEmployeeDataBase::delMorePhone(
    const BigUint& id, size_t index, const InternalEmployeePtr& changer
)
{
    auto person = this->by_id.find(id);
    if (person == this->by_id.end()) return;

    if (person->second->getMorePhoneNumbers().size() <= index) return;

    auto old_number = person->second->getMorePhoneNumbers()[index];

    if (person->second->delMorePhoneNumber(index, changer)) {
        auto persons = this->by_phone.equal_range(old_number.getNumber());
        for (auto it = persons.first; it != persons.second; ++it) {
            if (it->second == person->second) {
                this->by_phone.erase(it);
                break;
            }
        }
    }
}

void ExternalEmployeeDataBase::changeCompany(
    const BigUint& id, const ExternalCompanyPtr& company, const InternalEmployeePtr& changer
)
{
    auto person = this->by_id.find(id);
    if (person == this->by_id.end()) return;

    auto old_company = person->second->getCompany();

    if (person->second->setCompany(company, changer)) {
        if (old_company) {
            CompanyId company_id = old_company->getId();

            auto      company_it = this->by_company.find(company_id);
            if (company_it != this->by_company.end()) {
                auto& vec = company_it->second;

                vec.erase(std::remove(vec.begin(), vec.end(), person->second), vec.end());

                if (vec.empty()) {
                    this->by_company.erase(company_id);
                }
            }
        }

        if (company) {
            this->by_company[company->getId()].push_back(person->second);
        }
    }
}
