#include "client_db.hpp"

#include <algorithm>
#include <string>
#include <vector>

#include "events_log.hpp"
#include "internal_employee.hpp"
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

    if (client->getOwner()) {
        this->by_owner[client->getOwner()->getId()].push_back(client);
    }

    if (client->getType() != Client::ClientType::other) {
        this->by_type[client->getType()].push_back(client);
    } else {
        if (client->getOtherType().has_value()) {
            this->by_other_type[client->getOtherType().value()].push_back(client);
        }
    }

    if (client->getLeadSource() != Client::LeadSource::other) {
        this->by_lead_source[client->getLeadSource()].push_back(client);
    } else {
        if (client->getOtherLeadSource().has_value()) {
            this->by_other_lead_source[client->getOtherLeadSource().value()].push_back(client);
        }
    }

    this->by_marketing_consent[client->getMarketingConsent()].push_back(client);

    if (client->getLeadStatus().has_value()) {
        this->by_lead_status.emplace(client->getLeadStatus().value(), client);
    }
}

void ClientDataBase::remove(const BigUint& id)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) {
        return;
    }
    ClientPtr client = id_it->second;

    removeFromMultimap(this->by_name, client->getName(), client);

    std::string lower_name = client->getName();
    std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), ::tolower);

    removeFromMultimap(this->by_name_substr_search, lower_name, client);

    if (client->getEmail().has_value()) {
        removeFromMultimap(this->by_email, client->getEmail().value(), client);

        std::string lower_email = client->getEmail().value();
        std::transform(lower_email.begin(), lower_email.end(), lower_email.begin(), ::tolower);

        removeFromMultimap(this->by_email_substr_search, lower_email, client);
    }

    for (auto& email : client->getMoreEmails()) {
        removeFromMultimap(this->by_email, email, client);

        std::string lower_email = email;
        std::transform(lower_email.begin(), lower_email.end(), lower_email.begin(), ::tolower);

        removeFromMultimap(this->by_email_substr_search, lower_email, client);
    }

    if (client->getPhoneNumber()) {
        removeFromMultimap(this->by_phone, client->getPhoneNumber()->getNumber(), client);
        removeFromMultimap(
            this->by_phone_substr_search, client->getPhoneNumber()->getNumber(), client
        );
    }

    for (auto& phone_number : client->getMorePhoneNumbers()) {
        removeFromMultimap(this->by_phone, phone_number.getNumber(), client);
        removeFromMultimap(this->by_phone_substr_search, phone_number.getNumber(), client);
    }

    if (client->getOwner()) {
        auto& vec = this->by_owner[client->getOwner()->getId()];
        if (vec.empty()) {
            EventLog::getInstance().log(
                LOG_LEVEL::ERROR,
                __FILE__,
                __LINE__,
                "Data inconsistency in by_owner index\nClient id: " + client->getId().num +
                    "\n\tOwner id:" + client->getOwner()->getId().num +
                    "\n\tThe client has an owner but there is no entry in the database"
            );
        } else {
            vec.erase(std::remove(vec.begin(), vec.end(), client), vec.end());
            if (vec.empty()) {
                this->by_owner.erase(client->getOwner()->getId());
            }
        }
    }

    if (client->getType() != Client::ClientType::other) {
        auto& vec = this->by_type.find(client->getType())->second;
        vec.erase(std::remove(vec.begin(), vec.end(), client), vec.end());
        if (vec.empty()) {
            this->by_type.erase(client->getType());
        }
    } else {
        if (client->getOtherType().has_value()) {
            auto& vec = this->by_other_type.find(client->getOtherType().value())->second;
            vec.erase(std::remove(vec.begin(), vec.end(), client), vec.end());
            if (vec.empty()) {
                this->by_other_type.erase(client->getOtherType().value());
            }
        }
    }

    if (client->getLeadSource() != Client::LeadSource::other) {
        auto& vec = this->by_lead_source.find(client->getLeadSource())->second;
        vec.erase(std::remove(vec.begin(), vec.end(), client), vec.end());
        if (vec.empty()) {
            this->by_lead_source.erase(client->getLeadSource());
        }
    } else {
        if (client->getOtherLeadSource().has_value()) {
            auto& vec =
                this->by_other_lead_source.find(client->getOtherLeadSource().value())->second;
            vec.erase(std::remove(vec.begin(), vec.end(), client), vec.end());
            if (vec.empty()) {
                this->by_other_lead_source.erase(client->getOtherLeadSource().value());
            }
        }
    }

    auto& vec = this->by_marketing_consent.find(client->getMarketingConsent())->second;
    vec.erase(std::remove(vec.begin(), vec.end(), client), vec.end());
    if (vec.empty()) {
        this->by_marketing_consent.erase(client->getMarketingConsent());
    }

    if (client->getLeadStatus().has_value()) {
        removeFromMultimap(this->by_lead_status, client->getLeadStatus().value(), client);
    }
    this->by_id.erase(id_it);
}

auto ClientDataBase::size() const -> size_t { return this->by_id.size(); }

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

auto ClientDataBase::findById(const BigUint& id) const -> const ClientPtr
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

auto ClientDataBase::findByOwner(const BigUint& id) const -> const std::vector<ClientPtr>
{
    auto clients = this->by_owner.find(id);
    if (clients != this->by_owner.end()) {
        return clients->second;
    }
    return std::vector<ClientPtr>{};
}

auto ClientDataBase::findByType(const Client::ClientType type) const
    -> const std::vector<ClientPtr>
{
    auto clients = this->by_type.find(type);
    if (clients != this->by_type.end()) {
        return clients->second;
    }
    return std::vector<ClientPtr>{};
}

auto ClientDataBase::findByOtherType(const std::string& type) const -> const std::vector<ClientPtr>
{
    auto clients = this->by_other_type.find(type);
    if (clients != this->by_other_type.end()) {
        return clients->second;
    }
    return std::vector<ClientPtr>{};
}

auto ClientDataBase::findByLeadSource(const Client::LeadSource source) const
    -> const std::vector<ClientPtr>
{
    auto clients = this->by_lead_source.find(source);
    if (clients != this->by_lead_source.end()) {
        return clients->second;
    }
    return std::vector<ClientPtr>{};
}

auto ClientDataBase::findByOtherLeadSource(const std::string& source) const
    -> const std::vector<ClientPtr>
{
    auto clients = this->by_other_lead_source.find(source);
    if (clients != this->by_other_lead_source.end()) {
        return clients->second;
    }
    return std::vector<ClientPtr>{};
}

auto ClientDataBase::findByMarketingConsent(const bool consent) const
    -> const std::vector<ClientPtr>
{
    auto clients = this->by_marketing_consent.find(consent);
    if (clients != this->by_marketing_consent.end()) {
        return clients->second;
    }
    return std::vector<ClientPtr>{};
}

auto ClientDataBase::findByLeadStatus(const Client::LeadStatus status) const
    -> const std::vector<ClientPtr>
{
    auto clients = this->by_lead_status.equal_range(status);
    if (clients.first == clients.second) return std::vector<ClientPtr>{};

    std::vector<ClientPtr> result;
    for (auto it = clients.first; it != clients.second; ++it) {
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

void ClientDataBase::removeFromMultimapVect(auto& map, const auto& key, const ClientPtr& client) {}
