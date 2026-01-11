#pragma once
#include <map>
#include <unordered_map>

#include "Person/Client/client.hpp"
#include "Usings/type_usings.hpp"

class ClientDataBase {
public:
    void add(const ClientPtr& client);
    void soft_remove(const BigUint& id, const Date& remove_date);
    void hard_remove(const size_t index);
    /// @name Getters
    /// @{
    auto size() const -> size_t;
    bool empty() const;
    auto getAll() const -> const std::unordered_map<BigUint, ClientPtr>&;
    auto getByName() const -> const std::unordered_multimap<std::string, ClientPtr>&;
    auto getByEmail() const -> const std::unordered_multimap<std::string, ClientPtr>&;
    auto getByPhone() const -> const std::unordered_multimap<std::string, ClientPtr>&;
    auto getByOwner() const -> const std::unordered_map<BigUint, std::vector<ClientPtr>>&;
    auto getByType() const -> const std::unordered_map<Client::ClientType, std::vector<ClientPtr>>&;
    auto getByOtherType() const -> const std::unordered_map<std::string, std::vector<ClientPtr>>&;
    auto getByLeadSource() const
        -> const std::unordered_map<Client::LeadSource, std::vector<ClientPtr>>&;
    auto getByMarketingConsent() const -> const std::unordered_map<bool, std::vector<ClientPtr>>&;
    auto getByLeadStatus() const
        -> const std::unordered_map<Client::LeadStatus, std::vector<ClientPtr>>&;
    /// @}

    /// @name Find functions
    /// @{
    auto findById(const BigUint& id) const -> const ClientPtr;
    auto findByName(const std::string& name) const -> const std::vector<ClientPtr>;
    auto findByNameSubstr(const std::string& substr) const -> const std::vector<ClientPtr>;
    auto findByEmail(const std::string& email) const -> const std::vector<ClientPtr>;
    auto findByEmailSubstr(const std::string& substr) const -> const std::vector<ClientPtr>;
    auto findByPhone(const std::string& phone) const -> const std::vector<ClientPtr>;
    auto findByPhoneSubstr(const std::string& substr) const -> const std::vector<ClientPtr>;
    auto findByOwner(const BigUint& id) const -> const std::vector<ClientPtr>&;
    auto findByType(const Client::ClientType type) const -> const std::vector<ClientPtr>&;
    auto findByOtherType(const std::string& type) const -> const std::vector<ClientPtr>&;
    auto findByLeadSource(const Client::LeadSource source) const -> const std::vector<ClientPtr>&;
    auto findByOtherLeadSource(const std::string& source) const -> const std::vector<ClientPtr>&;
    auto findByMarketingConsent(const bool consent) const -> const std::vector<ClientPtr>&;
    auto findByLeadStatus(const Client::LeadStatus status) const -> const std::vector<ClientPtr>&;
    /// @}

    /// @name Change functions
    /// @{
    void changeName(const BigUint& id, const std::string& name, const InternalEmployeePtr& changer);
    void changeEmail(
        const BigUint& id, const OptionalStr& email, const InternalEmployeePtr& changer
    );
    void addMoreEmail(
        const BigUint& id, const std::string& email, const InternalEmployeePtr& changer
    );
    void delMoreEmail(const BigUint& id, size_t index, const InternalEmployeePtr& changer);

    void changePhone(
        const BigUint& id, const PhoneNumberPtr& number, const InternalEmployeePtr& changer
    );

    void addMorePhone(
        const BigUint& id, const PhoneNumber& number, const InternalEmployeePtr& changer
    );
    void delMorePhone(const BigUint& id, size_t index, const InternalEmployeePtr& changer);

    void changeOwner(
        const BigUint& id, const WeakInternalEmployee& owner, const InternalEmployeePtr& changer
    );
    void changeType(
        const BigUint& id, const Client::ClientType type, const InternalEmployeePtr& changer
    );
    void changeOtherType(
        const BigUint& id, const std::string& type, const InternalEmployeePtr& changer
    );
    void changeLeadSource(
        const BigUint& id, const Client::LeadSource source, const InternalEmployeePtr& changer
    );
    void changeOtherLeadSource(
        const BigUint& id, const std::string& source, const InternalEmployeePtr& changer
    );
    void changeMarketingConsent(
        const BigUint& id, const bool consent, const InternalEmployeePtr& changer
    );
    void changeLeadStatus(
        const BigUint&                          id,
        const std::optional<Client::LeadStatus> status,
        const InternalEmployeePtr&              changer
    );
    /// @}

    /// @name Auxiliary functions
    /// @{
    void removeOwner(const BigUint& id);
    /// @}

private:
    static const std::vector<ClientPtr>             empty_vector;
    std::unordered_map<BigUint, ClientPtr>          by_id;
    std::unordered_multimap<std::string, ClientPtr> by_name;
    std::multimap<std::string, ClientPtr>           by_name_substr_search;
    std::unordered_multimap<std::string, ClientPtr> by_email;
    std::multimap<std::string, ClientPtr>           by_email_substr_search;
    std::unordered_multimap<std::string, ClientPtr> by_phone;
    std::multimap<std::string, ClientPtr>           by_phone_substr_search;

    //
    std::unordered_map<BigUint, std::vector<ClientPtr>>            by_owner;
    std::unordered_map<Client::ClientType, std::vector<ClientPtr>> by_type;
    std::unordered_map<std::string, std::vector<ClientPtr>>        by_other_type;
    std::unordered_map<Client::LeadSource, std::vector<ClientPtr>> by_lead_source;
    std::unordered_map<std::string, std::vector<ClientPtr>>        by_other_lead_source;
    std::unordered_map<bool, std::vector<ClientPtr>>               by_marketing_consent;
    std::unordered_map<Client::LeadStatus, std::vector<ClientPtr>> by_lead_status;
    std::vector<std::pair<Date, ClientPtr>>                        removed;
    //
    void safeRemoveFromMap(
        auto&              map,
        const auto&        key,
        const ClientPtr&   client,
        const size_t       line,
        const std::string& index_name
    );
    void safeRemoveFromVector(
        auto&              map,
        const auto&        key,
        const ClientPtr&   client,
        const size_t       line,
        const std::string& index_name
    );

    void logEmptyContainer(
        const std::string& file,
        const size_t       line,
        const std::string& client_id,
        const std::string& index_name
    );
};