#include "internal_employee_db.hpp"

void InternalEmployeeDataBase::add(const InternalEmployeePtr& person)
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
}

void InternalEmployeeDataBase::remove(const BigUint& id)
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

    this->by_id.erase(person);
}

auto InternalEmployeeDataBase::getById() const
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

auto InternalEmployeeDataBase::findById(const BigUint& id) const -> const InternalEmployeePtr&
{
    auto person = this->by_id.find(id);
    if (person != this->by_id.end()) {
        return person->second;
    }
    return nullptr;
}

auto InternalEmployeeDataBase::findByName(const std::string& name) const
    -> const std::vector<InternalEmployeePtr>
{
    auto persons = this->by_name.equal_range(name);
    if (persons.first == persons.second) {
        return std::vector<InternalEmployeePtr>{};
    }

    std::vector<InternalEmployeePtr> result;
    for (auto it = persons.first; it != persons.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto InternalEmployeeDataBase::findByEmail(const std::string& email) const
    -> const std::vector<InternalEmployeePtr>
{
    auto persons = this->by_email.equal_range(email);
    if (persons.first == persons.second) {
        return std::vector<InternalEmployeePtr>{};
    }
    std::vector<InternalEmployeePtr> result;
    for (auto it = persons.first; it != persons.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto InternalEmployeeDataBase::findByPhone(const std::string& phone) const
    -> const std::vector<InternalEmployeePtr>
{
    auto persons = this->by_phone.equal_range(phone);
    if (persons.first == persons.second) {
        return std::vector<InternalEmployeePtr>{};
    }
    std::vector<InternalEmployeePtr> result;
    for (auto it = persons.first; it != persons.second; ++it) {
        result.push_back(it->second);
    }

    return result;
}

void InternalEmployeeDataBase::changeName(
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

void InternalEmployeeDataBase::changeEmail(
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

void InternalEmployeeDataBase::addMoreEmail(
    const BigUint& id, const std::string& email, const InternalEmployeePtr& changer
)
{
    auto person = this->by_id.find(id);
    if (person == this->by_id.end()) return;

    if (person->second->addMoreEmails(email, changer)) {
        this->by_email.emplace(email, person->second);
    }
}

void InternalEmployeeDataBase::delMoreEmail(
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

void InternalEmployeeDataBase::changePhone(
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

void InternalEmployeeDataBase::addMorePhone(
    const BigUint& id, const PhoneNumber& number, const InternalEmployeePtr& changer
)
{
    auto person = this->by_id.find(id);
    if (person == this->by_id.end()) return;

    if (person->second->addMorePhoneNumber(number, changer)) {
        this->by_phone.emplace(number.getNumber(), person->second);
    }
}

void InternalEmployeeDataBase::delMorePhone(
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
