#include "client_db.hpp"

#include <algorithm>
#include <string>
#include <vector>

#include "Logger/events_log.hpp"
#include "Person/Employee/internal_employee.hpp"
#include "TenantContext/tenant_context.hpp"

const std::vector<ClientPtr> ClientDataBase::empty_vector;
//
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

    if (!client->getOwner().expired()) {
        this->by_owner[client->getOwner().lock()->getId()].push_back(client);
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
        this->by_lead_status[client->getLeadStatus().value()].push_back(client);
    }
}

void ClientDataBase::soft_remove(const BigUint& id, const Date& remove_date)
{
    auto id_it = by_id.find(id);
    if (id_it == by_id.end()) {
        return;
    }

    ClientPtr          client = id_it->second;

    const std::string& name       = client->getName();
    std::string        lower_name = name;
    std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), ::tolower);

    safeRemoveFromMap(by_name, name, client, __LINE__, "by_name");
    safeRemoveFromMap(by_name_substr_search, lower_name, client, __LINE__, "by_name_substr_search");

    if (client->getEmail().has_value()) {
        const std::string& email       = client->getEmail().value();
        std::string        lower_email = email;
        std::transform(lower_email.begin(), lower_email.end(), lower_email.begin(), ::tolower);

        safeRemoveFromMap(by_email, email, client, __LINE__, "by_email");
        safeRemoveFromMap(
            by_email_substr_search, lower_email, client, __LINE__, "by_email_substr_search"
        );
    }

    for (const std::string& more_email : client->getMoreEmails()) {
        std::string lower_more_email = more_email;
        std::transform(
            lower_more_email.begin(), lower_more_email.end(), lower_more_email.begin(), ::tolower
        );

        safeRemoveFromMap(by_email, more_email, client, __LINE__, "by_email");
        safeRemoveFromMap(
            by_email_substr_search, lower_more_email, client, __LINE__, "by_email_substr_search"
        );
    }

    if (client->getPhoneNumber()) {
        const std::string& phone = client->getPhoneNumber()->getNumber();

        safeRemoveFromMap(by_phone, phone, client, __LINE__, "by_phone");
        safeRemoveFromMap(
            by_phone_substr_search, phone, client, __LINE__, "by_phone_substr_search"
        );
    }

    for (const auto& more_phone : client->getMorePhoneNumbers()) {
        const std::string& phone_str = more_phone.getNumber();

        safeRemoveFromMap(by_phone, phone_str, client, __LINE__, "by_phone");
        safeRemoveFromMap(
            by_phone_substr_search, phone_str, client, __LINE__, "by_phone_substr_search"
        );
    }

    if (!client->getOwner().expired()) {
        BigUint owner_id = client->getOwner().lock()->getId();
        safeRemoveFromVector(by_owner, owner_id, client, __LINE__, "by_owner");
    }

    Client::ClientType type = client->getType();
    if (type != Client::ClientType::other) {
        safeRemoveFromVector(by_type, type, client, __LINE__, "by_type");
    } else if (client->getOtherType().has_value()) {
        const std::string& other_type = client->getOtherType().value();
        safeRemoveFromVector(by_other_type, other_type, client, __LINE__, "by_other_type");
    }

    Client::LeadSource lead_source = client->getLeadSource();
    if (lead_source != Client::LeadSource::other) {
        safeRemoveFromVector(by_lead_source, lead_source, client, __LINE__, "by_lead_source");
    } else if (client->getOtherLeadSource().has_value()) {
        const std::string& other_lead_source = client->getOtherLeadSource().value();
        safeRemoveFromVector(
            by_other_lead_source, other_lead_source, client, __LINE__, "by_other_lead_source"
        );
    }

    bool marketing_consent = client->getMarketingConsent();
    safeRemoveFromVector(
        by_marketing_consent, marketing_consent, client, __LINE__, "by_marketing_consent"
    );

    if (client->getLeadStatus().has_value()) {
        Client::LeadStatus status = client->getLeadStatus().value();
        safeRemoveFromVector(by_lead_status, status, client, __LINE__, "by_lead_status");
    }

    this->removed.push_back({remove_date, client});

    by_id.erase(id_it);
}

void ClientDataBase::hard_remove(const size_t index, TenantContext& context)
{
    if (index < this->removed.size()) {
        const auto& client    = removed[index].second;
        auto        client_id = client->getId();

        context.task_data_base.removeParty(client_id);
        context.interaction_data_base.removeParticipant(client_id);

        this->removed.erase(this->removed.begin() + index);
    }
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

auto ClientDataBase::getByOwner() const
    -> const std::unordered_map<BigUint, std::vector<ClientPtr>>&
{
    return this->by_owner;
}

auto ClientDataBase::getByType() const
    -> const std::unordered_map<Client::ClientType, std::vector<ClientPtr>>&
{
    return this->by_type;
}

auto ClientDataBase::getByOtherType() const
    -> const std::unordered_map<std::string, std::vector<ClientPtr>>&
{
    return this->by_other_type;
}

auto ClientDataBase::getByLeadSource() const
    -> const std::unordered_map<Client::LeadSource, std::vector<ClientPtr>>&
{
    return this->by_lead_source;
}

auto ClientDataBase::getByOtherLeadSource() const
    -> const std::unordered_map<std::string, std::vector<ClientPtr>>&
{
    return this->by_other_lead_source;
}

auto ClientDataBase::getByMarketingConsent() const
    -> const std::unordered_map<bool, std::vector<ClientPtr>>&
{
    return this->by_marketing_consent;
}

auto ClientDataBase::getByLeadStatus() const
    -> const std::unordered_map<Client::LeadStatus, std::vector<ClientPtr>>&
{
    return this->by_lead_status;
}

auto ClientDataBase::getRemoved() const -> const std::vector<std::pair<Date, ClientPtr>>&
{
    return this->removed;
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
    if (clients.first == clients.second) return empty_vector;

    std::vector<ClientPtr> result;
    for (auto it = clients.first; it != clients.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto ClientDataBase::findByNameSubstr(const std::string& substr) const
    -> const std::vector<ClientPtr>
{
    if (substr.empty()) return empty_vector;

    std::string key = substr;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    auto first = this->by_name_substr_search.lower_bound(key);
    key.back()++;
    auto second = this->by_name_substr_search.lower_bound(key);

    if (first == second) return empty_vector;

    std::vector<ClientPtr> result;
    for (auto it = first; it != second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto ClientDataBase::findByEmail(const std::string& email) const -> const std::vector<ClientPtr>
{
    auto clients = this->by_email.equal_range(email);
    if (clients.first == clients.second) return empty_vector;

    std::vector<ClientPtr> result;
    for (auto it = clients.first; it != clients.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto ClientDataBase::findByEmailSubstr(const std::string& substr) const
    -> const std::vector<ClientPtr>
{
    if (substr.empty()) return empty_vector;

    std::string key = substr;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    auto first = this->by_email_substr_search.lower_bound(key);
    key.back()++;
    auto second = this->by_email_substr_search.lower_bound(key);

    if (first == second) return empty_vector;

    std::vector<ClientPtr> result;
    for (auto it = first; it != second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto ClientDataBase::findByPhone(const std::string& phone) const -> const std::vector<ClientPtr>
{
    auto clients = this->by_phone.equal_range(phone);
    if (clients.first == clients.second) return empty_vector;

    std::vector<ClientPtr> result;
    for (auto it = clients.first; it != clients.second; ++it) {
        result.push_back(it->second);
    }

    return result;
}

auto ClientDataBase::findByPhoneSubstr(const std::string& substr) const
    -> const std::vector<ClientPtr>
{
    if (substr.empty()) return empty_vector;

    std::string key = substr;

    //
    auto first = this->by_phone_substr_search.lower_bound(key);
    key.back()++;
    auto second = this->by_phone_substr_search.lower_bound(key);

    if (first == second) return empty_vector;

    std::vector<ClientPtr> result;
    for (auto it = first; it != second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto ClientDataBase::findByOwner(const BigUint& id) const -> const std::vector<ClientPtr>&
{
    auto clients = this->by_owner.find(id);
    if (clients != this->by_owner.end()) {
        return clients->second;
    }
    return empty_vector;
}

auto ClientDataBase::findByType(const Client::ClientType type) const
    -> const std::vector<ClientPtr>&
{
    auto clients = this->by_type.find(type);
    if (clients != this->by_type.end()) {
        return clients->second;
    }
    return empty_vector;
}

auto ClientDataBase::findByOtherType(const std::string& type) const -> const std::vector<ClientPtr>&
{
    auto clients = this->by_other_type.find(type);
    if (clients != this->by_other_type.end()) {
        return clients->second;
    }
    return empty_vector;
}

auto ClientDataBase::findByLeadSource(const Client::LeadSource source) const
    -> const std::vector<ClientPtr>&
{
    auto clients = this->by_lead_source.find(source);
    if (clients != this->by_lead_source.end()) {
        return clients->second;
    }
    return empty_vector;
}

auto ClientDataBase::findByOtherLeadSource(const std::string& source) const
    -> const std::vector<ClientPtr>&
{
    auto clients = this->by_other_lead_source.find(source);
    if (clients != this->by_other_lead_source.end()) {
        return clients->second;
    }
    return empty_vector;
}

auto ClientDataBase::findByMarketingConsent(const bool consent) const
    -> const std::vector<ClientPtr>&
{
    auto clients = this->by_marketing_consent.find(consent);
    if (clients != this->by_marketing_consent.end()) {
        return clients->second;
    }
    return empty_vector;
}

auto ClientDataBase::findByLeadStatus(const Client::LeadStatus status) const
    -> const std::vector<ClientPtr>&
{
    auto clients = this->by_lead_status.find(status);
    if (clients != this->by_lead_status.end()) {
        return clients->second;
    }
    return empty_vector;
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
        safeRemoveFromMap(this->by_name, old_name, client, __LINE__, "by_name");
        this->by_name.emplace(name, client);

        // by_name_substr_search
        std::transform(old_name.begin(), old_name.end(), old_name.begin(), ::tolower);
        std::string new_name = name;
        std::transform(new_name.begin(), new_name.end(), new_name.begin(), ::tolower);

        safeRemoveFromMap(
            this->by_name_substr_search, old_name, client, __LINE__, "by_name_substr_search"
        );
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
            safeRemoveFromMap(this->by_email, old_email_str, client, __LINE__, "by_email");
            std::transform(
                old_email_str.begin(), old_email_str.end(), old_email_str.begin(), ::tolower
            );
            safeRemoveFromMap(
                this->by_email_substr_search,
                old_email_str,
                client,
                __LINE__,
                "by_email_substr_search"
            );
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
        safeRemoveFromMap(this->by_email, old_email, client, __LINE__, "by_email");
        std::transform(old_email.begin(), old_email.end(), old_email.begin(), ::tolower);
        safeRemoveFromMap(
            this->by_email_substr_search, old_email, client, __LINE__, "by_email_substr_search"
        );
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
            safeRemoveFromMap(
                this->by_phone, old_number->getNumber(), client, __LINE__, "by_phone"
            );
            safeRemoveFromMap(
                this->by_phone_substr_search,
                old_number->getNumber(),
                client,
                __LINE__,
                "by_phone_substr_search"
            );
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

        safeRemoveFromMap(this->by_phone, old_number_str, client, __LINE__, "by_phone");
        safeRemoveFromMap(
            this->by_phone_substr_search, old_number_str, client, __LINE__, "by_phone_substr_search"
        );
    }
}

void ClientDataBase::changeOwner(
    const BigUint& id, const WeakInternalEmployee& owner, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    ClientPtr client = id_it->second;

    auto      old_owner = client->getOwner();

    if (client->setOwner(owner, changer)) {
        if (!old_owner.expired()) {
            safeRemoveFromVector(
                this->by_owner, old_owner.lock()->getId(), client, __LINE__, "by_owner"
            );
        }
        if (!owner.expired()) {
            this->by_owner[owner.lock()->getId()].push_back(client);
        }
    }
}

void ClientDataBase::changeType(
    const BigUint& id, const Client::ClientType type, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    ClientPtr client = id_it->second;

    auto      old_type = client->getType();

    if (client->setType(type, changer)) {
        if (old_type != Client::ClientType::other) {
            safeRemoveFromVector(this->by_type, old_type, client, __LINE__, "by_type");
        } else if (client->getOtherType()) {
            safeRemoveFromVector(
                this->by_other_type,
                client->getOtherType().value(),
                client,
                __LINE__,
                "by_other_type"
            );
        }
        if (type != Client::ClientType::other) {
            this->by_type[type].push_back(client);
        }
    }
}

void ClientDataBase::changeOtherType(
    const BigUint& id, const std::string& type, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    ClientPtr client = id_it->second;

    auto      old_other_type = client->getOtherType();

    if (client->setOtherType(type, changer)) {
        if (client->getType() != Client::ClientType::other) {
            safeRemoveFromVector(this->by_type, client->getType(), client, __LINE__, "by_type");
        } else if (old_other_type) {
            safeRemoveFromVector(
                this->by_other_type, old_other_type.value(), client, __LINE__, "by_other_type"
            );
        }
        this->by_other_type[type].push_back(client);
    }
}

void ClientDataBase::changeLeadSource(
    const BigUint& id, const Client::LeadSource source, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    ClientPtr client = id_it->second;

    auto      old_lead_source = client->getLeadSource();

    if (client->setLeadSource(source, changer)) {
        if (old_lead_source != Client::LeadSource::other) {
            safeRemoveFromVector(
                this->by_lead_source, old_lead_source, client, __LINE__, "by_lead_source"
            );
        } else if (client->getOtherLeadSource()) {
            safeRemoveFromVector(
                this->by_other_lead_source,
                client->getOtherLeadSource().value(),
                client,
                __LINE__,
                "by_other_lead_source"
            );
        }
        if (source != Client::LeadSource::other) {
            this->by_lead_source[source].push_back(client);
        }
    }
}

void ClientDataBase::changeOtherLeadSource(
    const BigUint& id, const std::string& source, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    ClientPtr client = id_it->second;

    auto      old_other_lead_source = client->getOtherLeadSource();

    if (client->setOtherLeadSource(source, changer)) {
        if (client->getLeadSource() != Client::LeadSource::other) {
            safeRemoveFromVector(
                this->by_lead_source, client->getLeadSource(), client, __LINE__, "by_lead_source"
            );
        } else if (old_other_lead_source) {
            safeRemoveFromVector(
                this->by_other_lead_source,
                old_other_lead_source.value(),
                client,
                __LINE__,
                "by_other_lead_source"
            );
        }
        this->by_other_lead_source[source].push_back(client);
    }
}

void ClientDataBase::changeMarketingConsent(
    const BigUint& id, const bool consent, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    ClientPtr client = id_it->second;

    auto      old_marketing_consent = client->getMarketingConsent();

    if (client->setMarketingConsent(consent, changer)) {
        safeRemoveFromVector(
            this->by_marketing_consent,
            old_marketing_consent,
            client,
            __LINE__,
            "by_marketing_consent"
        );
        this->by_marketing_consent[consent].push_back(client);
    }
}

void ClientDataBase::changeLeadStatus(
    const BigUint&                          id,
    const std::optional<Client::LeadStatus> status,
    const InternalEmployeePtr&              changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    ClientPtr client = id_it->second;

    auto      old_lead_status = client->getLeadStatus();

    if (client->setLeadStatus(status, changer)) {
        if (old_lead_status) {
            safeRemoveFromVector(
                this->by_lead_status, old_lead_status.value(), client, __LINE__, "by_lead_status"
            );
        }
        if (status) {
            this->by_lead_status[status.value()].push_back(client);
        }
    }
}

void ClientDataBase::removeOwner(const BigUint& id) { this->by_owner.erase(id); }

void ClientDataBase::safeRemoveFromMap(
    auto&              map,
    const auto&        key,
    const ClientPtr&   client,
    const size_t       line,
    const std::string& index_name
)
{
    auto range = map.equal_range(key);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second == client) {
            map.erase(it);
            return;
        }
    }
    this->logEmptyContainer(__FILE__, line, client->getId().num, index_name);
}

void ClientDataBase::safeRemoveFromVector(
    auto&              map,
    const auto&        key,
    const ClientPtr&   client,
    const size_t       line,
    const std::string& index_name
)
{
    auto& vec = map[key];
    if (vec.empty()) {
        this->logEmptyContainer(__FILE__, line, client->getId().num, index_name);

    } else {
        vec.erase(std::remove(vec.begin(), vec.end(), client), vec.end());
        if (vec.empty()) {
            map.erase(key);
        }
    }
}

void ClientDataBase::logEmptyContainer(
    const std::string& file,
    const size_t       line,
    const std::string& client_id,
    const std::string& index_name
)
{
    EventLog::getInstance().log(
        LOG_LEVEL::ERROR,
        file,
        line,
        "Data inconsistency in " + index_name + "\nClient id: " + client_id +
            "\nExpected entry is missing."
    );
}