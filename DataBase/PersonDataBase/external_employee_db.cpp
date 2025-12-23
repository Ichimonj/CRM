#include "external_employee_db.hpp"

#include <algorithm>
#include <string>

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

    std::string lower_name = person->getName();
    std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), ::tolower);

    this->by_name_substr_search.emplace(lower_name, person);

    if (person->getEmail()) {
        this->by_email.emplace(person->getEmail().value(), person);

        std::string lower_email = person->getEmail().value();
        std::transform(lower_email.begin(), lower_email.end(), lower_email.begin(), ::tolower);
        this->by_email_substr_search.emplace(lower_email, person);
    }
    for (auto& email : person->getMoreEmails()) {
        this->by_email.emplace(email, person);

        std::string lower_email = email;
        std::transform(lower_email.begin(), lower_email.end(), lower_email.begin(), ::tolower);
        this->by_email_substr_search.emplace(lower_email, person);
    }

    if (person->getPhoneNumber()) {
        this->by_phone.emplace(person->getPhoneNumber()->getNumber(), person);

        this->by_phone_substr_search.emplace(person->getPhoneNumber()->getNumber(), person);
    }
    for (auto& number : person->getMorePhoneNumbers()) {
        this->by_phone.emplace(number.getNumber(), person);

        this->by_phone_substr_search.emplace(number.getNumber(), person);
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

    std::string lower_name = person->second->getName();
    std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), ::tolower);

    auto name_substr_range = this->by_name_substr_search.equal_range(lower_name);
    for (auto it = name_substr_range.first; it != name_substr_range.second; ++it) {
        if (it->second->getId() == id) {
            this->by_name_substr_search.erase(it);
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

        std::string lower_email = person->second->getEmail().value();
        std::transform(lower_email.begin(), lower_email.end(), lower_email.begin(), ::tolower);

        auto email_substr_range = this->by_email_substr_search.equal_range(lower_email);
        for (auto it = email_substr_range.first; it != email_substr_range.second; ++it) {
            if (it->second->getId() == id) {
                this->by_email_substr_search.erase(it);
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

        std::string lower_email = email;
        std::transform(lower_email.begin(), lower_email.end(), lower_email.begin(), ::tolower);

        auto email_substr_range = this->by_email_substr_search.equal_range(lower_email);
        for (auto it = email_substr_range.first; it != email_substr_range.second; ++it) {
            if (it->second->getId() == id) {
                this->by_email_substr_search.erase(it);
                break;
            }
        }
    }

    if (person->second->getPhoneNumber()) {
        auto phone_range =
            this->by_phone.equal_range(person->second->getPhoneNumber()->getNumber());

        for (auto it = phone_range.first; it != phone_range.second; ++it) {
            if (it->second == person->second) {
                this->by_phone.erase(it);
                break;
            }
        }

        auto phone_substr_range =
            this->by_phone_substr_search.equal_range(person->second->getPhoneNumber()->getNumber());

        for (auto it = phone_substr_range.first; it != phone_substr_range.second; ++it) {
            if (it->second == person->second) {
                this->by_phone_substr_search.erase(it);
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

        auto phone_substr_range =
            this->by_phone_substr_search.equal_range(phone_number.getNumber());

        for (auto it = phone_substr_range.first; it != phone_substr_range.second; ++it) {
            if (it->second == person->second) {
                this->by_phone_substr_search.erase(it);
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

auto ExternalEmployeeDataBase::findById(const BigUint& id) const -> const ExternalEmployeePtr
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

auto ExternalEmployeeDataBase::findByNameSubstr(const std::string& substr) const
    -> const std::vector<ExternalEmployeePtr>
{
    if (substr.empty()) return std::vector<ExternalEmployeePtr>{};
    std::string key = substr;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    auto first = this->by_name_substr_search.lower_bound(key);
    key.back()++;
    auto second = this->by_name_substr_search.lower_bound(key);

    if (first == second) return std::vector<ExternalEmployeePtr>{};
    std::vector<ExternalEmployeePtr> result;
    for (auto it = first; it != second; ++it) {
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

auto ExternalEmployeeDataBase::findByEmailSubstr(const std::string& substr) const
    -> const std::vector<ExternalEmployeePtr>
{
    if (substr.empty()) return std::vector<ExternalEmployeePtr>{};
    std::string key = substr;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    auto first = this->by_email_substr_search.lower_bound(key);
    key.back()++;
    auto second = this->by_email_substr_search.lower_bound(key);

    if (first == second) return std::vector<ExternalEmployeePtr>{};
    std::vector<ExternalEmployeePtr> result;
    for (auto it = first; it != second; ++it) {
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

auto ExternalEmployeeDataBase::findByPhoneSubstr(const std::string& substr) const
    -> const std::vector<ExternalEmployeePtr>
{
    if (substr.empty()) return std::vector<ExternalEmployeePtr>{};
    std::string key = substr;

    auto        first = this->by_phone_substr_search.lower_bound(key);
    key.back()++;
    auto second = this->by_phone_substr_search.lower_bound(key);

    if (first == second) return std::vector<ExternalEmployeePtr>{};
    std::vector<ExternalEmployeePtr> result;
    for (auto it = first; it != second; ++it) {
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
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    ExternalEmployeePtr person   = id_it->second;
    std::string         old_name = person->getName();

    if (person->setName(name, changer)) {
        // by_name
        removeFromMultimap(this->by_name, old_name, person);
        this->by_name.emplace(name, person);

        // by_name_substr_search
        std::transform(old_name.begin(), old_name.end(), old_name.begin(), ::tolower);
        std::string new_name = name;
        std::transform(new_name.begin(), new_name.end(), new_name.begin(), ::tolower);
        removeFromMultimap(this->by_name_substr_search, old_name, person);
        this->by_name_substr_search.emplace(new_name, person);
    }
}

void ExternalEmployeeDataBase::changeEmail(
    const BigUint& id, const OptionalStr& email, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;
    ExternalEmployeePtr person    = id_it->second;
    auto                old_email = person->getEmail();

    if (person->setEmail(email, changer)) {
        if (old_email.has_value()) {
            std::string old_email_str = old_email.value();

            removeFromMultimap(this->by_email, old_email_str, person);
            std::transform(
                old_email_str.begin(), old_email_str.end(), old_email_str.begin(), ::tolower
            );
            removeFromMultimap(this->by_email_substr_search, old_email_str, person);
        }
        if (email.has_value()) {
            std::string new_email = email.value();
            this->by_email.emplace(new_email, person);
            std::transform(new_email.begin(), new_email.end(), new_email.begin(), ::tolower);
            this->by_email_substr_search.emplace(new_email, person);
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

        std::string lower_email = email;
        std::transform(lower_email.begin(), lower_email.end(), lower_email.begin(), ::tolower);
        this->by_email_substr_search.emplace(lower_email, person->second);
    }
}

void ExternalEmployeeDataBase::delMoreEmail(
    const BigUint& id, size_t index, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    ExternalEmployeePtr person = id_it->second;
    if (person->getMoreEmails().size() <= index) return;

    std::string old_email = person->getMoreEmails()[index];

    if (person->delMoreEmails(index, changer)) {
        removeFromMultimap(this->by_email, old_email, person);
        std::transform(old_email.begin(), old_email.end(), old_email.begin(), ::tolower);
        removeFromMultimap(this->by_email_substr_search, old_email, person);
    }
}

void ExternalEmployeeDataBase::changePhone(
    const BigUint& id, const PhoneNumberPtr& number, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    ExternalEmployeePtr person = id_it->second;

    auto                old_number = person->getPhoneNumber();

    if (person->setPhoneNumber(number, changer)) {
        if (old_number) {
            removeFromMultimap(this->by_phone, old_number->getNumber(), person);
            removeFromMultimap(this->by_phone_substr_search, old_number->getNumber(), person);
        }
        if (number) {
            this->by_phone.emplace(number->getNumber(), person);
            this->by_phone_substr_search.emplace(number->getNumber(), person);
        }
    }
}

void ExternalEmployeeDataBase::addMorePhone(
    const BigUint& id, const PhoneNumber& number, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    ExternalEmployeePtr person = id_it->second;
    if (person->addMorePhoneNumber(number, changer)) {
        this->by_phone.emplace(number.getNumber(), person);
        this->by_phone_substr_search.emplace(number.getNumber(), person);
    }
}

void ExternalEmployeeDataBase::delMorePhone(
    const BigUint& id, size_t index, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    ExternalEmployeePtr person = id_it->second;
    if (person->getMorePhoneNumbers().size() <= index) return;

    auto old_number = person->getMorePhoneNumbers()[index];

    if (person->delMorePhoneNumber(index, changer)) {
        std::string old_number_str = old_number.getNumber();

        removeFromMultimap(this->by_phone, old_number_str, person);
        removeFromMultimap(this->by_phone_substr_search, old_number_str, person);
    }
}

void ExternalEmployeeDataBase::changeCompany(
    const BigUint& id, const ExternalCompanyPtr& company, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    ExternalEmployeePtr person = id_it->second;

    auto                old_company = person->getCompany();

    if (person->setCompany(company, changer)) {
        if (old_company) {
            CompanyId company_id = old_company->getId();

            auto      company_it = this->by_company.find(company_id);
            if (company_it != this->by_company.end()) {
                auto& vec = company_it->second;

                vec.erase(std::remove(vec.begin(), vec.end(), person), vec.end());

                if (vec.empty()) {
                    this->by_company.erase(company_id);
                }
            }
        }

        if (company) {
            this->by_company[company->getId()].push_back(person);
        }
    }
}

void ExternalEmployeeDataBase::removeFromMultimap(
    auto& map, const auto& key, const ExternalEmployeePtr& person
)
{
    auto range = map.equal_range(key);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second == person) {
            map.erase(it);
            return;
        }
    }
}
