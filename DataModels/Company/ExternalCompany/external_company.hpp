#pragma once
#include "Company/company.hpp"
#include "Currencies/currencies.hpp"
#include "Usings/type_usings.hpp"

class ExternalCompany : public Company {
public:
    enum class CompanyType : uint8_t { Client, Partner, Vendor, Prospect, Supplier, Other, COUNT };
    enum class Rating : uint8_t { Hot, Warm, Cold, Inactive, COUNT };
    enum class RiskLevel : uint8_t { Low, Medium, High, Critical, COUNT };
    enum class CompanySize : uint8_t { Micro, Small, Medium, Large, Enterprise, COUNT };
    enum class ComplianceLevel : uint8_t { Compliant, Warning, NonCompliant, COUNT };
    enum class IntegrationStatus : uint8_t { Connected, Pending, Failed, COUNT };

    ExternalCompany(const BigUint& id);
    ExternalCompany(
        const BigUint&                        id,
        const std::string&                    company_name,
        const OptionalStr&                    legal_name,
        const OptionalStr&                    website_url,
        const OptionalStr&                    sic_code,
        const OptionalStr&                    industry,
        const PhoneNumberPtr&                 phone_number,
        const OptionalStr&                    email,
        const OptionalStr&                    country_code,
        const AddressPtr&                     registered_address,
        const DatePtr&                        founded_date,
        const OptionalStr&                    tax_id,
        const std::optional<CompanyStatus>&   status,
        const std::optional<uint32_t>&        employee_count,
        const MoneyPtr&                       annual_revenue,
        const MoneyPtr&                       budget,
        const CompanyType&                    type,
        const OptionalStr&                    other_type,
        const CompanySize&                    size,
        const Rating&                         rating,
        const RiskLevel&                      risk_level,
        const WeakInternalEmployee&           account_manager,
        const OptionalStr&                    VAT_number,
        const DatePtr&                        last_interaction_date,
        const OptionalStr&                    preferred_contact_method,
        const OptionalStr&                    payment_terms,
        const Currencies&                     preferred_currency,
        const std::optional<double>&          win_rate,
        const std::optional<ComplianceLevel>& compliance_status,
        const MoneyPtr&                       credit_limit,
        const MoneyPtr&                       total_revenue_generated,
        const MoneyPtr&                       outstanding_balance,
        const std::optional<double>&          churn_probability,
        std::vector<WeakExternalEmployee>     contacts,
        std::vector<WeakClientPtr>            associated_clients,
        std::vector<FilePtr>                  documents,
        std::vector<Note>                     notes,
        std::vector<TaxInfo>                  tax_rates,
        std::vector<WeakDealPtr>              deals,
        std::vector<TaskPtr>                  tasks,
        std::vector<PhoneNumber>              more_phone_numbers,
        std::vector<std::string>              more_emails
    );
    /// @name Getters
    /// @{
    auto getType() const -> CompanyType;
    auto getOtherType() const -> const OptionalStr&;
    auto getSize() const -> CompanySize;
    auto getRating() const -> Rating;
    auto getRiskLevel() const -> RiskLevel;
    auto getAccountManager() const -> const WeakInternalEmployee&;
    auto getVatNumber() const -> const OptionalStr&;
    auto getLastInteractionDate() const -> const DatePtr&;
    auto getPreferredContactMethod() const -> const OptionalStr&;
    auto getPaymentTerms() const -> const OptionalStr&;
    auto getPreferredCurrency() const -> const Currencies&;
    auto getServiceLevelAgreement() const -> const OptionalStr&;
    auto getPreferredIntegrationTool() const -> const OptionalStr&;
    auto getIntegrationStatus() const -> const std::optional<IntegrationStatus>&;
    auto getWinRate() const -> const std::optional<double>&;
    auto getContacts() const -> const std::vector<WeakExternalEmployee>&;
    auto getComplianceStatus() const -> const std::optional<ComplianceLevel>&;
    auto getAssociatedClients() const -> const std::vector<WeakClientPtr>&;
    auto getCreditLimit() const -> const MoneyPtr&;
    auto getTotalRevenueGenerated() const -> const MoneyPtr&;
    auto getOutstandingBalance() const -> const MoneyPtr&;
    auto getDocuments() const -> const std::vector<FilePtr>&;
    auto getChurnProbability() const -> const std::optional<double>&;
    /// @}

    /// @name Setters
    /// @{
    bool setType(const CompanyType type, const InternalEmployeePtr& changer);
    bool setOtherType(const OptionalStr& other_type, const InternalEmployeePtr& changer);
    bool setSize(const CompanySize size, const InternalEmployeePtr& changer);
    bool setRating(const Rating rating, const InternalEmployeePtr& changer);
    bool setRiskLevel(const RiskLevel risk_level, const InternalEmployeePtr& changer);
    bool setAccountManager(
        const WeakInternalEmployee& account_manager, const InternalEmployeePtr& changer
    );
    bool setVatNumber(const OptionalStr& VAT_number, const InternalEmployeePtr& changer);
    bool setLastInteractionDate(
        const DatePtr& last_interaction_date, const InternalEmployeePtr& changer
    );
    bool setCreditLimit(const MoneyPtr& credit_limit, const InternalEmployeePtr& changer);
    bool setTotalRevenueGenerated(
        const MoneyPtr& total_revenue_generated, const InternalEmployeePtr& changer
    );
    bool setOutstandingBalance(
        const MoneyPtr& outstanding_balance, const InternalEmployeePtr& changer
    );
    bool setChurnProbability(
        const std::optional<double>& churn_probability, const InternalEmployeePtr& changer
    );
    bool setPreferredContactMethod(
        const OptionalStr& preferred_contact_method, const InternalEmployeePtr& changer
    );
    bool setPaymentTerms(const OptionalStr& payment_terms, const InternalEmployeePtr& changer);
    bool setPreferredCurrency(
        const Currencies& preferred_currency, const InternalEmployeePtr& changer
    );
    bool setServiceLevelAgreement(
        const OptionalStr& service_level_agreement, const InternalEmployeePtr& changer
    );
    bool setPreferredIntegrationTool(
        const OptionalStr& preferred_integration_tool, const InternalEmployeePtr& changer
    );
    bool setIntegrationStatus(
        const std::optional<IntegrationStatus>& integration_status,
        const InternalEmployeePtr&              changer
    );
    bool setWinRate(const std::optional<double>& win_rate, const InternalEmployeePtr& changer);
    bool setComplianceStatus(
        const std::optional<ComplianceLevel>& compliance_status, const InternalEmployeePtr& changer
    );

    bool addContact(const WeakExternalEmployee& contact, const InternalEmployeePtr& changer);
    bool delContact(size_t index, const InternalEmployeePtr& changer);

    bool addAssociatedClient(
        const WeakClientPtr& associated_client, const InternalEmployeePtr& changer
    );
    bool delAssociatedClient(size_t index, const InternalEmployeePtr& changer);

    bool addDocument(const FilePtr& document, const InternalEmployeePtr& changer);
    bool delDocument(size_t index, const InternalEmployeePtr& changer);
    /// @}

    /// @name Auxiliary functions
    /// @{
    void clearContacts();
    void clearAssociatedClients();
    /// @}
private:
    CompanyType          type;
    OptionalStr          other_type;
    CompanySize          size;
    Rating               rating;
    RiskLevel            risk_level;
    WeakInternalEmployee account_manager;
    OptionalStr          VAT_number;
    DatePtr              last_interaction_date;
    OptionalStr          preferred_contact_method;
    OptionalStr          payment_terms;
    Currencies           preferred_currency;
    OptionalStr          service_level_agreement;
    OptionalStr          preferred_integration_tool;
    //
    std::optional<IntegrationStatus>  integration_status;
    std::optional<double>             win_rate;
    std::vector<WeakExternalEmployee> contacts;
    std::optional<ComplianceLevel>    compliance_status;
    std::vector<WeakClientPtr>        associated_clients;
    MoneyPtr                          credit_limit;
    MoneyPtr                          total_revenue_generated;
    MoneyPtr                          outstanding_balance;
    std::vector<FilePtr>              documents;
    std::optional<double>             churn_probability;
};