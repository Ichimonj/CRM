#include "person_db.hpp"

#include "external_company.hpp"

void PersonDataBase::addPerson(const PersonPtr& person)
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

    if (auto ext = std::dynamic_pointer_cast<ExternalEmployee>(person)) {
        if (ext->getCompany()) {
            this->by_company[ext->getCompany()->getId()].push_back(person);
        }
    }
}

void PersonDataBase::delPerson(const BigUint& id)
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

    if (auto ext = std::dynamic_pointer_cast<ExternalEmployee>(person->second)) {
        if (ext->getCompany()) {
            CompanyId company_id = ext->getCompany()->getId();

            auto      company_it = this->by_company.find(company_id);
            if (company_it != by_company.end()) {
                auto& vec = company_it->second;
                vec.erase(std::remove(vec.begin(), vec.end(), person->second), vec.end());

                if (vec.empty()) {
                    this->by_company.erase(company_it);
                }
            }
        }
    }

    this->by_id.erase(person);
}

auto PersonDataBase::getById() const -> const std::unordered_map<BigUint, PersonPtr>&
{
    return this->by_id;
}

auto PersonDataBase::getByName() const -> const std::unordered_multimap<std::string, PersonPtr>&
{
    return this->by_name;
}

auto PersonDataBase::getByEmail() const -> const std::unordered_multimap<std::string, PersonPtr>&
{
    return this->by_email;
}

auto PersonDataBase::getByPhone() const -> const std::unordered_multimap<std::string, PersonPtr>&
{
    return this->by_phone;
}

auto PersonDataBase::getByCompany() const
    -> const std::unordered_map<CompanyId, std::vector<PersonPtr>>&
{
    return this->by_company;
}

auto PersonDataBase::findById(const BigUint& id) const -> const PersonPtr&
{
    auto person = this->by_id.find(id);
    if (person != this->by_id.end()) {
        return person->second;
    }
    return nullptr;
}

auto PersonDataBase::findByName(const std::string& name) const -> const std::vector<PersonPtr>
{
    auto persons = this->by_name.equal_range(name);
    if (persons.first == persons.second) {
        return std::vector<PersonPtr>{};
    }

    std::vector<PersonPtr> result;
    for (auto it = persons.first; it != persons.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto PersonDataBase::findByEmail(const std::string& email) const -> const std::vector<PersonPtr>
{
    auto persons = this->by_email.equal_range(email);
    if (persons.first == persons.second) {
        return std::vector<PersonPtr>{};
    }
    std::vector<PersonPtr> result;
    for (auto it = persons.first; it != persons.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto PersonDataBase::findByPhone(const std::string& phone) const -> const std::vector<PersonPtr>
{
    auto persons = this->by_phone.equal_range(phone);
    if (persons.first == persons.second) {
        return std::vector<PersonPtr>{};
    }
    std::vector<PersonPtr> result;
    for (auto it = persons.first; it != persons.second; ++it) {
        result.push_back(it->second);
    }

    return result;
}

auto PersonDataBase::findByCompany(const CompanyId& id) const -> const std::vector<PersonPtr>
{
    auto persons = this->by_company.find(id);
    if (persons != this->by_company.end()) {
        return persons->second;
    }
    return std::vector<PersonPtr>{};
}

void PersonDataBase::changeName(
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

void PersonDataBase::changeEmail(
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

void PersonDataBase::addMoreEmail(
    const BigUint& id, const std::string& email, const InternalEmployeePtr& changer
)
{
    auto person = this->by_id.find(id);
    if (person == this->by_id.end()) return;

    if (person->second->addMoreEmails(email, changer)) {
        this->by_email.emplace(email, person->second);
    }
}

void PersonDataBase::delMoreEmail(
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

void PersonDataBase::changePhone(
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

void PersonDataBase::addMorePhone(
    const BigUint& id, const PhoneNumber& number, const InternalEmployeePtr& changer
)
{
    auto person = this->by_id.find(id);
    if (person == this->by_id.end()) return;

    if (person->second->addMorePhoneNumber(number, changer)) {
        this->by_phone.emplace(number.getNumber(), person->second);
    }
}

void PersonDataBase::delMorePhone(
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

void PersonDataBase::changeCompany(
    const BigUint& id, const ExternalCompanyPtr& company, const InternalEmployeePtr& changer
)
{
    auto person = this->by_id.find(id);
    if (person == this->by_id.end()) return;

    if (auto ext = std::dynamic_pointer_cast<ExternalEmployee>(person->second)) {
        auto old_company = ext->getCompany();

        if (ext->setCompany(company, changer)) {
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
}
