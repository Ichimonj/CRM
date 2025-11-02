#pragma once
#include "company.hpp"
#include "currencies.hpp"
class Client;
class FileMetadata;
class Task;
struct Deal;
using ClientPtr = std::shared_ptr<Client>;
using DatePtr   = std::shared_ptr<Date>;
using FilePtr   = std::shared_ptr<FileMetadata>;
using TaskPtr   = std::shared_ptr<Task>;
using DealPtr   = std::shared_ptr<Deal>;

class ExternalCompany : public Company {
public:
    enum class CompanyType : uint8_t { Client, Partner, Vendor, Prospect, Supplier, Other };
    enum class Rating : uint8_t { Hot, Warm, Cold, Inactive };
    enum class RiskLevel : uint8_t { Low, Medium, High, Critical };
    enum class CompanySize : uint8_t { Micro, Small, Medium, Large, Enterprise };
    enum class ComplianceLevel : uint8_t { Compliant, Warning, NonCompliant };
    enum class IntegrationStatus : uint8_t { Connected, Pending, Failed };

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
        const InternalEmployeePtr&            account_manager,
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
        std::vector<ExternalEmployeePtr>      contacts,
        std::vector<ClientPtr>                associated_clients,
        std::vector<FilePtr>                  documents,
        std::vector<Note>                     notes,
        std::vector<TaxInfo>                  tax_rates,
        std::vector<DealPtr>                  deals,
        std::vector<TaskPtr>                  tasks,
        std::vector<PhoneNumber>              more_phone_numbers,
        std::vector<std::string>              more_emails
    );
    /// @name Getters
    /// @{
    auto getType() const -> const CompanyType;
    auto getOtherType() const -> const OptionalStr&;
    auto getSize() const -> const CompanySize;
    auto getRating() const -> const Rating;
    auto getRiskLevel() const -> const RiskLevel;
    auto getAccountManager() const -> const InternalEmployeePtr&;
    auto getVatNumber() const -> const OptionalStr&;
    auto getLastInteractionDate() const -> const DatePtr&;
    auto getPreferredContactMethod() const -> const OptionalStr&;
    auto getPaymentTerms() const -> const OptionalStr&;
    auto getPreferredCurrency() const -> const Currencies&;
    auto getServiceLevelAgreement() const -> const OptionalStr&;
    auto getPreferredIntegrationTool() const -> const OptionalStr&;
    auto getIntegrationStatus() const -> const std::optional<IntegrationStatus>&;
    auto getWinRate() const -> const std::optional<double>&;
    auto getContacts() const -> const std::vector<ExternalEmployeePtr>&;
    auto getComplianceStatus() const -> const std::optional<ComplianceLevel>&;
    auto getAssociatedClients() const -> const std::vector<ClientPtr>&;
    auto getCreditLimit() const -> const MoneyPtr&;
    auto getTotalRevenueGenerated() const -> const MoneyPtr&;
    auto getOutstandingBalance() const -> const MoneyPtr&;
    auto getDocuments() const -> const std::vector<FilePtr>&;
    auto getChurnProbability() const -> const std::optional<double>&;
    /// @}

    /// @name Setters
    /// @{
    void setType(const CompanyType type, const InternalEmployeePtr& changer);
    void setOtherType(const OptionalStr& other_type, const InternalEmployeePtr& changer);
    void setSize(const CompanySize size, const InternalEmployeePtr& changer);
    void setRating(const Rating rating, const InternalEmployeePtr& changer);
    void setRiskLevel(const RiskLevel risk_level, const InternalEmployeePtr& changer);
    void setAccountManager(
        const InternalEmployeePtr& account_manager, const InternalEmployeePtr& changer
    );
    void setVatNumber(const OptionalStr& VAT_number, const InternalEmployeePtr& changer);
    void setLastInteractionDate(
        const DatePtr& last_interaction_date, const InternalEmployeePtr& changer
    );
    void setCreditLimit(const MoneyPtr& credit_limit, const InternalEmployeePtr& changer);
    void setTotalRevenueGenerated(
        const MoneyPtr& total_revenue_generated, const InternalEmployeePtr& changer
    );
    void setOutstandingBalance(
        const MoneyPtr& outstanding_balance, const InternalEmployeePtr& changer
    );
    void setChurnProbability(
        const std::optional<double>& churn_probability, const InternalEmployeePtr& changer
    );
    void setPreferredContactMethod(
        const OptionalStr& preferred_contact_method, const InternalEmployeePtr& changer
    );
    void setPaymentTerms(const OptionalStr& payment_terms, const InternalEmployeePtr& changer);
    void setPreferredCurrency(
        const Currencies& preferred_currency, const InternalEmployeePtr& changer
    );
    void setServiceLevelAgreement(
        const OptionalStr& service_level_agreement, const InternalEmployeePtr& changer
    );
    void setPreferredIntegrationTool(
        const OptionalStr& preferred_integration_tool, const InternalEmployeePtr& changer
    );
    void setIntegrationStatus(
        const std::optional<IntegrationStatus>& integration_status,
        const InternalEmployeePtr&              changer
    );
    void setWinRate(const std::optional<double>& win_rate, const InternalEmployeePtr& changer);
    void setComplianceStatus(
        const std::optional<ComplianceLevel>& compliance_status, const InternalEmployeePtr& changer
    );

    void addContact(const ExternalEmployeePtr& contact, const InternalEmployeePtr& changer);
    void delContact(size_t index, const InternalEmployeePtr& changer);

    void addAssociatedClient(
        const ClientPtr& associated_client, const InternalEmployeePtr& changer
    );
    void delAssociatedClient(size_t index, const InternalEmployeePtr& changer);

    void addDocument(const FilePtr& document, const InternalEmployeePtr& changer);
    void delDocument(size_t index, const InternalEmployeePtr& changer);
    /// @}

private:
    CompanyType         type;
    OptionalStr         other_type;
    CompanySize         size;
    Rating              rating;
    RiskLevel           risk_level;
    InternalEmployeePtr account_manager;
    OptionalStr         VAT_number;
    DatePtr             last_interaction_date;
    OptionalStr         preferred_contact_method;
    OptionalStr         payment_terms;
    Currencies          preferred_currency;
    OptionalStr         service_level_agreement;
    OptionalStr         preferred_integration_tool;
    //
    std::optional<IntegrationStatus> integration_status;
    std::optional<double>            win_rate;
    std::vector<ExternalEmployeePtr> contacts;
    std::optional<ComplianceLevel>   compliance_status;
    std::vector<ClientPtr>           associated_clients;
    MoneyPtr                         credit_limit;
    MoneyPtr                         total_revenue_generated;
    MoneyPtr                         outstanding_balance;
    std::vector<FilePtr>             documents;
    std::optional<double>            churn_probability;
};