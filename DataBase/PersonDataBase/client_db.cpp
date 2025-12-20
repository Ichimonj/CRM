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
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    ClientPtr   client   = id_it->second;
    std::string old_name = client->getName();

    if (client->setName(name, changer)) {
        // by_name
        removeFromMultimap(this->by_name, old_name, client);
        this->by_name.emplace(name, client);

        // by_name_substr_search
        std::transform(old_name.begin(), old_name.end(), old_name.begin(), ::tolower);
        std::string new_name = name;
        std::transform(new_name.begin(), new_name.end(), new_name.begin(), ::tolower);

        removeFromMultimap(this->by_name_substr_search, old_name, client);
        this->by_name_substr_search.emplace(new_name, client);
    }
}

void ClientDataBase::changeEmail(
    const BigUint& id, const OptionalStr& email, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;
    ClientPtr client    = id_it->second;
    auto      old_email = client->getEmail();

    if (client->setEmail(email, changer)) {
        if (old_email.has_value()) {
            std::string old_email_str = old_email.value();

            removeFromMultimap(this->by_email, old_email_str, client);
            std::transform(
                old_email_str.begin(), old_email_str.end(), old_email_str.begin(), ::tolower
            );
            removeFromMultimap(this->by_email_substr_search, old_email_str, client);
        }
        if (email.has_value()) {
            std::string new_email = email.value();
            this->by_email.emplace(new_email, client);
            std::transform(new_email.begin(), new_email.end(), new_email.begin(), ::tolower);
            this->by_email_substr_search.emplace(new_email, client);
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

        std::string lower_email = email;
        std::transform(lower_email.begin(), lower_email.end(), lower_email.begin(), ::tolower);
        this->by_email_substr_search.emplace(lower_email, client->second);
    }
}

void ClientDataBase::delMoreEmail(
    const BigUint& id, size_t index, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    ClientPtr client = id_it->second;
    if (client->getMoreEmails().size() <= index) return;

    std::string old_email = client->getMoreEmails()[index];

    if (client->delMoreEmails(index, changer)) {
        removeFromMultimap(this->by_email, old_email, client);
        std::transform(old_email.begin(), old_email.end(), old_email.begin(), ::tolower);
        removeFromMultimap(this->by_email_substr_search, old_email, client);
    }
}

void ClientDataBase::changePhone(
    const BigUint& id, const PhoneNumberPtr& number, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    ClientPtr client = id_it->second;

    auto      old_number = client->getPhoneNumber();

    if (client->setPhoneNumber(number, changer)) {
        if (old_number) {
            removeFromMultimap(this->by_phone, old_number->getNumber(), client);
            removeFromMultimap(this->by_phone_substr_search, old_number->getNumber(), client);
        }
        if (number) {
            this->by_phone.emplace(number->getNumber(), client);
            this->by_phone_substr_search.emplace(number->getNumber(), client);
        }
    }
}

void ClientDataBase::addMorePhone(
    const BigUint& id, const PhoneNumber& number, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    ClientPtr client = id_it->second;
    if (client->addMorePhoneNumber(number, changer)) {
        this->by_phone.emplace(number.getNumber(), client);
        this->by_phone_substr_search.emplace(number.getNumber(), client);
    }
}

void ClientDataBase::delMorePhone(
    const BigUint& id, size_t index, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    ClientPtr client = id_it->second;
    if (client->getMorePhoneNumbers().size() <= index) return;

    auto old_number = client->getMorePhoneNumbers()[index];

    if (client->delMorePhoneNumber(index, changer)) {
        std::string old_number_str = old_number.getNumber();

        removeFromMultimap(this->by_phone, old_number_str, client);
        removeFromMultimap(this->by_phone_substr_search, old_number_str, client);
    }
}

void ClientDataBase::removeFromMultimap(auto& map, const auto& key, const ClientPtr& client)
{
    auto range = map.equal_range(key);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second == client) {
            map.erase(it);
            return;
        }
    }
}
