#include "client_db.hpp"

#include <algorithm>
#include <string>
void ClientDataBase::add(const ClientPtr& client)
{
    if (client == nullptr) return;

    if (this->by_id.find(client->getId()) != this->by_id.end()) {
        return;
    }
    this->by_id[client->getId()] = client;
    this->by_name.emplace(client->getName(), client);

    std::string lower_name = client->getName();
    std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), ::tolower);

    this->by_name_substr_search.emplace(lower_name, client);

    if (client->getEmail()) {
        this->by_email.emplace(client->getEmail().value(), client);

        std::string lower_email = client->getEmail().value();
        std::transform(lower_email.begin(), lower_email.end(), lower_email.begin(), ::tolower);
        this->by_email_substr_search.emplace(lower_email, client);
    }
    for (auto& email : client->getMoreEmails()) {
        this->by_email.emplace(email, client);

        std::string lower_email = email;
        std::transform(lower_email.begin(), lower_email.end(), lower_email.begin(), ::tolower);
        this->by_email_substr_search.emplace(lower_email, client);
    }

    if (client->getPhoneNumber()) {
        this->by_phone.emplace(client->getPhoneNumber()->getNumber(), client);

        this->by_phone_substr_search.emplace(client->getPhoneNumber()->getNumber(), client);
    }
    for (auto& number : client->getMorePhoneNumbers()) {
        this->by_phone.emplace(number.getNumber(), client);

        this->by_phone_substr_search.emplace(number.getNumber(), client);
    }
}

void ClientDataBase::remove(const BigUint& id)
{
    auto client = this->by_id.find(id);
    if (client == this->by_id.end()) {
        return;
    }

    auto name_range = this->by_name.equal_range(client->second->getName());
    for (auto it = name_range.first; it != name_range.second; ++it) {
        if (it->second->getId() == id) {
            this->by_name.erase(it);
            break;
        }
    }

    std::string lower_name = client->second->getName();
    std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), ::tolower);

    auto name_substr_range = this->by_name_substr_search.equal_range(lower_name);
    for (auto it = name_substr_range.first; it != name_substr_range.second; ++it) {
        if (it->second->getId() == id) {
            this->by_name_substr_search.erase(it);
            break;
        }
    }

    if (client->second->getEmail().has_value()) {
        auto email_range = this->by_email.equal_range(client->second->getEmail().value());
        for (auto it = email_range.first; it != email_range.second; ++it) {
            if (it->second->getId() == id) {
                this->by_email.erase(it);
                break;
            }
        }

        std::string lower_email = client->second->getEmail().value();
        std::transform(lower_email.begin(), lower_email.end(), lower_email.begin(), ::tolower);

        auto email_substr_range = this->by_email_substr_search.equal_range(lower_email);
        for (auto it = email_substr_range.first; it != email_substr_range.second; ++it) {
            if (it->second->getId() == id) {
                this->by_email_substr_search.erase(it);
                break;
            }
        }
    }

    for (auto& email : client->second->getMoreEmails()) {
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

    if (client->second->getPhoneNumber()) {
        auto phone_range =
            this->by_phone.equal_range(client->second->getPhoneNumber()->getNumber());

        for (auto it = phone_range.first; it != phone_range.second; ++it) {
            if (it->second == client->second) {
                this->by_phone.erase(it);
                break;
            }
        }

        auto phone_substr_range =
            this->by_phone_substr_search.equal_range(client->second->getPhoneNumber()->getNumber());

        for (auto it = phone_substr_range.first; it != phone_substr_range.second; ++it) {
            if (it->second == client->second) {
                this->by_phone_substr_search.erase(it);
                break;
            }
        }
    }

    for (auto& phone_number : client->second->getMorePhoneNumbers()) {
        auto clients = this->by_phone.equal_range(phone_number.getNumber());

        for (auto it = clients.first; it != clients.second; ++it) {
            if (it->second == client->second) {
                this->by_phone.erase(it);
                break;
            }
        }

        auto phone_substr_range =
            this->by_phone_substr_search.equal_range(phone_number.getNumber());

        for (auto it = phone_substr_range.first; it != phone_substr_range.second; ++it) {
            if (it->second == client->second) {
                this->by_phone_substr_search.erase(it);
                break;
            }
        }
    }

    this->by_id.erase(client);
}

auto ClientDataBase::size() const -> const size_t { return this->by_id.size(); }

bool ClientDataBase::empty() const { return this->by_id.empty(); }

auto ClientDataBase::getAll() const -> const std::unordered_map<BigUint, ClientPtr>&
{
    return this->by_id;
}

auto ClientDataBase::getByName() const -> const std::unordered_multimap<std::string, ClientPtr>&
{
    return this->by_name;
}

auto ClientDataBase::getByEmail() const -> const std::unordered_multimap<std::string, ClientPtr>&
{
    return this->by_email;
}

auto ClientDataBase::getByPhone() const -> const std::unordered_multimap<std::string, ClientPtr>&
{
    return this->by_phone;
}

auto ClientDataBase::findById(const BigUint& id) const -> const ClientPtr&
{
    auto client = this->by_id.find(id);
    if (client != this->by_id.end()) {
        return client->second;
    }
    return nullptr;
}

auto ClientDataBase::findByName(const std::string& name) const -> const std::vector<ClientPtr>
{
    auto clients = this->by_name.equal_range(name);
    if (clients.first == clients.second) {
        return std::vector<ClientPtr>{};
    }

    std::vector<ClientPtr> result;
    for (auto it = clients.first; it != clients.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto ClientDataBase::findByNameSubstr(const std::string& substr) const
    -> const std::vector<ClientPtr>
{
    if (substr.empty()) return std::vector<ClientPtr>{};
    std::string key = substr;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    auto first = this->by_name_substr_search.lower_bound(key);
    key.back()++;
    auto second = this->by_name_substr_search.lower_bound(key);

    if (first == second) return std::vector<ClientPtr>{};
    std::vector<ClientPtr> result;
    for (auto it = first; it != second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto ClientDataBase::findByEmail(const std::string& email) const -> const std::vector<ClientPtr>
{
    auto clients = this->by_email.equal_range(email);
    if (clients.first == clients.second) {
        return std::vector<ClientPtr>{};
    }
    std::vector<ClientPtr> result;
    for (auto it = clients.first; it != clients.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto ClientDataBase::findByEmailSubstr(const std::string& substr) const
    -> const std::vector<ClientPtr>
{
    if (substr.empty()) return std::vector<ClientPtr>{};
    std::string key = substr;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    auto first = this->by_email_substr_search.lower_bound(key);
    key.back()++;
    auto second = this->by_email_substr_search.lower_bound(key);

    if (first == second) return std::vector<ClientPtr>{};
    std::vector<ClientPtr> result;
    for (auto it = first; it != second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto ClientDataBase::findByPhone(const std::string& phone) const -> const std::vector<ClientPtr>
{
    auto clients = this->by_phone.equal_range(phone);
    if (clients.first == clients.second) {
        return std::vector<ClientPtr>{};
    }
    std::vector<ClientPtr> result;
    for (auto it = clients.first; it != clients.second; ++it) {
        result.push_back(it->second);
    }

    return result;
}

auto ClientDataBase::findByPhoneSubstr(const std::string& substr) const
    -> const std::vector<ClientPtr>
{
    if (substr.empty()) return std::vector<ClientPtr>{};
    std::string key = substr;

    auto        first = this->by_phone_substr_search.lower_bound(key);
    key.back()++;
    auto second = this->by_phone_substr_search.lower_bound(key);

    if (first == second) return std::vector<ClientPtr>{};
    std::vector<ClientPtr> result;
    for (auto it = first; it != second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

void ClientDataBase::changeName(
    const BigUint& id, const std::string& name, const InternalEmployeePtr& changer
)
{
    auto client = this->by_id.find(id);
    if (client == this->by_id.end()) return;

    auto old_name = client->second->getName();

    if (client->second->setName(name, changer)) {
        auto clients = this->by_name.equal_range(old_name);
        for (auto it = clients.first; it != clients.second; ++it) {
            if (it->second == client->second) {
                this->by_name.erase(it);
                break;
            }
        }
        this->by_name.emplace(name, client->second);
    }
}

void ClientDataBase::changeEmail(
    const BigUint& id, const OptionalStr& email, const InternalEmployeePtr& changer
)
{
    auto client = this->by_id.find(id);
    if (client == this->by_id.end()) return;

    auto old_email = client->second->getEmail();

    if (client->second->setEmail(email, changer)) {
        if (old_email.has_value()) {
            auto clients = this->by_email.equal_range(old_email.value());
            for (auto it = clients.first; it != clients.second; ++it) {
                if (it->second == client->second) {
                    this->by_email.erase(it);
                    break;
                }
            }
        }
        if (email.has_value()) {
            this->by_email.emplace(email.value(), client->second);
        }
    }
}

void ClientDataBase::addMoreEmail(
    const BigUint& id, const std::string& email, const InternalEmployeePtr& changer
)
{
    auto client = this->by_id.find(id);
    if (client == this->by_id.end()) return;

    if (client->second->addMoreEmails(email, changer)) {
        this->by_email.emplace(email, client->second);
    }
}

void ClientDataBase::delMoreEmail(
    const BigUint& id, size_t index, const InternalEmployeePtr& changer
)
{
    auto client = this->by_id.find(id);
    if (client == this->by_id.end()) return;

    if (client->second->getMoreEmails().size() <= index) return;

    auto old_email = client->second->getMoreEmails()[index];

    if (client->second->delMoreEmails(index, changer)) {
        auto clients = this->by_email.equal_range(old_email);
        for (auto it = clients.first; it != clients.second; ++it) {
            if (it->second == client->second) {
                this->by_email.erase(it);
                break;
            }
        }
    }
}

void ClientDataBase::changePhone(
    const BigUint& id, const PhoneNumberPtr& number, const InternalEmployeePtr& changer
)
{
    auto client = this->by_id.find(id);
    if (client == this->by_id.end()) return;

    auto old_number = client->second->getPhoneNumber();

    if (client->second->setPhoneNumber(number, changer)) {
        if (old_number) {
            auto clients = this->by_phone.equal_range(old_number->getNumber());
            for (auto it = clients.first; it != clients.second; ++it) {
                if (it->second == client->second) {
                    this->by_phone.erase(it);
                    break;
                }
            }
        }
        if (number) {
            this->by_phone.emplace(number->getNumber(), client->second);
        }
    }
}

void ClientDataBase::addMorePhone(
    const BigUint& id, const PhoneNumber& number, const InternalEmployeePtr& changer
)
{
    auto client = this->by_id.find(id);
    if (client == this->by_id.end()) return;

    if (client->second->addMorePhoneNumber(number, changer)) {
        this->by_phone.emplace(number.getNumber(), client->second);
    }
}

void ClientDataBase::delMorePhone(
    const BigUint& id, size_t index, const InternalEmployeePtr& changer
)
{
    auto client = this->by_id.find(id);
    if (client == this->by_id.end()) return;

    if (client->second->getMorePhoneNumbers().size() <= index) return;

    auto old_number = client->second->getMorePhoneNumbers()[index];

    if (client->second->delMorePhoneNumber(index, changer)) {
        auto clients = this->by_phone.equal_range(old_number.getNumber());
        for (auto it = clients.first; it != clients.second; ++it) {
            if (it->second == client->second) {
                this->by_phone.erase(it);
                break;
            }
        }
    }
}
