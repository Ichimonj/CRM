#include "internal_employee_db.hpp"

#include <algorithm>
#include <string>

void InternalEmployeeDataBase::add(const InternalEmployeePtr& person)
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

    this->by_id.erase(person);
}

auto InternalEmployeeDataBase::size() const -> const size_t { return this->by_id.size(); }

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

auto InternalEmployeeDataBase::findByNameSubstr(const std::string& substr) const
    -> const std::vector<InternalEmployeePtr>
{
    if (substr.empty()) return std::vector<InternalEmployeePtr>{};
    std::string key = substr;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    auto first = this->by_name_substr_search.lower_bound(key);
    key.back()++;
    auto second = this->by_name_substr_search.lower_bound(key);

    if (first == second) return std::vector<InternalEmployeePtr>{};
    std::vector<InternalEmployeePtr> result;
    for (auto it = first; it != second; ++it) {
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

auto InternalEmployeeDataBase::findByEmailSubstr(const std::string& substr) const
    -> const std::vector<InternalEmployeePtr>
{
    if (substr.empty()) return std::vector<InternalEmployeePtr>{};
    std::string key = substr;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    auto first = this->by_email_substr_search.lower_bound(key);
    key.back()++;
    auto second = this->by_email_substr_search.lower_bound(key);

    if (first == second) return std::vector<InternalEmployeePtr>{};
    std::vector<InternalEmployeePtr> result;
    for (auto it = first; it != second; ++it) {
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

auto InternalEmployeeDataBase::findByPhoneSubstr(const std::string& substr) const
    -> const std::vector<InternalEmployeePtr>
{
    if (substr.empty()) return std::vector<InternalEmployeePtr>{};
    std::string key = substr;

    auto        first = this->by_phone_substr_search.lower_bound(key);
    key.back()++;
    auto second = this->by_phone_substr_search.lower_bound(key);

    if (first == second) return std::vector<InternalEmployeePtr>{};
    std::vector<InternalEmployeePtr> result;
    for (auto it = first; it != second; ++it) {
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

    InternalEmployeePtr   person = id_it->second;
    std::string old_name = person->getName();

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

void InternalEmployeeDataBase::changeEmail(
    const BigUint& id, const OptionalStr& email, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;
    InternalEmployeePtr person = id_it->second;
    auto      old_email = person->getEmail();

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

void InternalEmployeeDataBase::addMoreEmail(
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

void InternalEmployeeDataBase::delMoreEmail(
    const BigUint& id, size_t index, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    InternalEmployeePtr person = id_it->second;
    if (person->getMoreEmails().size() <= index) return;

    std::string old_email = person->getMoreEmails()[index];

    if (person->delMoreEmails(index, changer)) {
        removeFromMultimap(this->by_email, old_email, person);
        std::transform(old_email.begin(), old_email.end(), old_email.begin(), ::tolower);
        removeFromMultimap(this->by_email_substr_search, old_email, person);
    }
}

void InternalEmployeeDataBase::changePhone(
    const BigUint& id, const PhoneNumberPtr& number, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    InternalEmployeePtr person = id_it->second;

    auto      old_number = person->getPhoneNumber();

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

void InternalEmployeeDataBase::addMorePhone(
    const BigUint& id, const PhoneNumber& number, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    InternalEmployeePtr person = id_it->second;
    if (person->addMorePhoneNumber(number, changer)) {
        this->by_phone.emplace(number.getNumber(), person);
        this->by_phone_substr_search.emplace(number.getNumber(), person);
    }
}

void InternalEmployeeDataBase::delMorePhone(
    const BigUint& id, size_t index, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    InternalEmployeePtr person = id_it->second;
    if (person->getMorePhoneNumbers().size() <= index) return;

    auto old_number = person->getMorePhoneNumbers()[index];

    if (person->delMorePhoneNumber(index, changer)) {
        std::string old_number_str = old_number.getNumber();

        removeFromMultimap(this->by_phone, old_number_str, person);
        removeFromMultimap(this->by_phone_substr_search, old_number_str, person);
    }
}

void InternalEmployeeDataBase::removeFromMultimap(
    auto& map, const auto& key, const InternalEmployeePtr& person
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
