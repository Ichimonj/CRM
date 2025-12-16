#include "external_company.hpp"

#include "change_log.hpp"
ExternalCompany::ExternalCompany(const BigUint& id)
    : Company(id)
    , rating(Rating::Inactive)
    , risk_level(RiskLevel::Medium)
    , type(CompanyType::Other)
    , size(CompanySize::Medium)
{
}
ExternalCompany::ExternalCompany(
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
)
    : Company(
          id,
          company_name,
          legal_name,
          website_url,
          industry,
          phone_number,
          email,
          country_code,
          registered_address,
          founded_date,
          tax_id,
          status,
          employee_count,
          annual_revenue,
          budget,
          std::move(notes),
          std::move(tax_rates),
          std::move(deals),
          std::move(tasks),
          std::move(more_phone_numbers),
          std::move(more_emails)
      )
    , type(type)
    , other_type(other_type)
    , size(size)
    , rating(rating)
    , risk_level(risk_level)
    , account_manager(account_manager)
    , VAT_number(VAT_number)
    , last_interaction_date(last_interaction_date)
    , preferred_contact_method(preferred_contact_method)
    , payment_terms(payment_terms)
    , preferred_currency(preferred_currency)
    , win_rate(win_rate)
    , contacts(std::move(contacts))
    , compliance_status(compliance_status)
    , associated_clients(std::move(associated_clients))
    , credit_limit(credit_limit)
    , total_revenue_generated(total_revenue_generated)
    , outstanding_balance(outstanding_balance)
    , documents(std::move(documents))
    , churn_probability(churn_probability)
{
}

auto ExternalCompany::getType() const -> const CompanyType { return this->type; }
auto ExternalCompany::getOtherType() const -> const OptionalStr& { return this->other_type; }
auto ExternalCompany::getSize() const -> const CompanySize { return this->size; }
auto ExternalCompany::getRating() const -> const Rating { return this->rating; }
auto ExternalCompany::getRiskLevel() const -> const RiskLevel { return this->risk_level; }
auto ExternalCompany::getAccountManager() const -> const InternalEmployeePtr&
{
    return this->account_manager;
}
auto ExternalCompany::getVatNumber() const -> const OptionalStr& { return this->VAT_number; }
auto ExternalCompany::getLastInteractionDate() const -> const DatePtr&
{
    return this->last_interaction_date;
}
auto ExternalCompany::getPreferredContactMethod() const -> const OptionalStr&
{
    return this->preferred_contact_method;
}
auto ExternalCompany::getPaymentTerms() const -> const OptionalStr& { return this->payment_terms; }
auto ExternalCompany::getPreferredCurrency() const -> const Currencies&
{
    return this->preferred_currency;
}
auto ExternalCompany::getServiceLevelAgreement() const -> const OptionalStr&
{
    return this->service_level_agreement;
}
auto ExternalCompany::getPreferredIntegrationTool() const -> const OptionalStr&
{
    return this->preferred_integration_tool;
}

auto ExternalCompany::getIntegrationStatus() const -> const std::optional<IntegrationStatus>&
{
    return this->integration_status;
}

auto ExternalCompany::getWinRate() const -> const std::optional<double>& { return this->win_rate; }
auto ExternalCompany::getContacts() const -> const std::vector<ExternalEmployeePtr>&
{
    return this->contacts;
}
auto ExternalCompany::getComplianceStatus() const -> const std::optional<ComplianceLevel>&
{
    return this->compliance_status;
}
auto ExternalCompany::getAssociatedClients() const -> const std::vector<ClientPtr>&
{
    return this->associated_clients;
}
auto ExternalCompany::getCreditLimit() const -> const MoneyPtr& { return this->credit_limit; }
auto ExternalCompany::getTotalRevenueGenerated() const -> const MoneyPtr&
{
    return this->total_revenue_generated;
}
auto ExternalCompany::getOutstandingBalance() const -> const MoneyPtr&
{
    return this->outstanding_balance;
}
auto ExternalCompany::getDocuments() const -> const std::vector<FilePtr>&
{
    return this->documents;
}
auto ExternalCompany::getChurnProbability() const -> const std::optional<double>&
{
    return this->churn_probability;
}

bool ExternalCompany::setType(const CompanyType type, const InternalEmployeePtr& changer)
{
    if (this->type != type) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->other_type ? std::make_optional<ChangeLog::ValueVariant>(
                                   std::make_shared<std::string>(this->other_type.value())
                               )
                             : std::make_optional(this->type),
            std::make_optional(type),
            ExternalCompanyFields::Type,
            this->other_type ? ChangeLog::FieldType::String : ChangeLog::FieldType::CompanyType,
            ChangeLog::FieldType::CompanyType,
            ChangeLog::Action::Change
        ));
        this->type       = type;
        this->other_type = std::nullopt;
        return true;
    }
    return false;
}

bool ExternalCompany::setOtherType(
    const OptionalStr& other_type, const InternalEmployeePtr& changer
)
{
    if (this->other_type != other_type) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->other_type ? std::make_optional<ChangeLog::ValueVariant>(
                                   std::make_shared<std::string>(this->other_type.value())
                               )
                             : std::make_optional(this->type),
            other_type.has_value() ? std::make_optional<ChangeLog::ValueVariant>(
                                         std::make_shared<std::string>(other_type.value())
                                     )
                                   : std::nullopt,
            ExternalCompanyFields::Type,
            this->other_type ? ChangeLog::FieldType::String : ChangeLog::FieldType::CompanyType,
            other_type.has_value() ? ChangeLog::FieldType::String
                                   : ChangeLog::FieldType::CompanyType,
            ChangeLog::Action::Change
        ));
        this->other_type = other_type;
        this->type       = CompanyType::Other;
        return true;
    }
    return false;
}

bool ExternalCompany::setRating(const Rating rating, const InternalEmployeePtr& changer)
{
    if (this->rating != rating) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->rating),
            std::make_optional(rating),
            ExternalCompanyFields::Rating,
            ChangeLog::FieldType::CompanyRating,
            ChangeLog::FieldType::CompanyRating,
            ChangeLog::Action::Change
        ));
        this->rating = rating;
        return true;
    }
    return false;
}

bool ExternalCompany::setRiskLevel(const RiskLevel risk_level, const InternalEmployeePtr& changer)
{
    if (this->risk_level != risk_level) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->risk_level),
            std::make_optional(risk_level),
            ExternalCompanyFields::RiskLevel,
            ChangeLog::FieldType::CompanyRiskLevel,
            ChangeLog::FieldType::CompanyRiskLevel,
            ChangeLog::Action::Change
        ));
        this->risk_level = risk_level;
        return true;
    }
    return false;
}

bool ExternalCompany::setAccountManager(
    const InternalEmployeePtr& account_manager, const InternalEmployeePtr& changer
)
{
    if (this->account_manager != account_manager) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->account_manager),
            PTR_TO_OPTIONAL(account_manager),
            ExternalCompanyFields::AccountManager,
            this->account_manager ? ChangeLog::FieldType::InternalEmployee
                                  : ChangeLog::FieldType::null,
            account_manager ? ChangeLog::FieldType::InternalEmployee : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->account_manager = account_manager;
        return true;
    }
    return false;
}

bool ExternalCompany::setLastInteractionDate(
    const DatePtr& last_interaction_date, const InternalEmployeePtr& changer
)
{
    if (this->last_interaction_date == nullptr || last_interaction_date == nullptr) {
        if (this->last_interaction_date == last_interaction_date) {
            return false;
        }
    } else if (*this->last_interaction_date == *last_interaction_date) {
        return false;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->last_interaction_date),
        PTR_TO_OPTIONAL(last_interaction_date),
        ExternalCompanyFields::LastInteractionDate,
        this->last_interaction_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        last_interaction_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->last_interaction_date = last_interaction_date;
    return true;
}

bool ExternalCompany::setCreditLimit(
    const MoneyPtr& credit_limit, const InternalEmployeePtr& changer
)
{
    if (this->credit_limit == nullptr || credit_limit == nullptr) {
        if (this->credit_limit == credit_limit) {
            return false;
        }
    } else if (*this->credit_limit == *credit_limit) {
        return false;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->credit_limit),
        PTR_TO_OPTIONAL(credit_limit),
        ExternalCompanyFields::CreditLimit,
        this->credit_limit ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        credit_limit ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->credit_limit = credit_limit;
    return true;
}

bool ExternalCompany::setTotalRevenueGenerated(
    const MoneyPtr& total_revenue_generated, const InternalEmployeePtr& changer
)
{
    if (this->total_revenue_generated == nullptr || total_revenue_generated == nullptr) {
        if (this->total_revenue_generated == total_revenue_generated) {
            return false;
        }
    } else if (*this->total_revenue_generated == *total_revenue_generated) {
        return false;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->total_revenue_generated),
        PTR_TO_OPTIONAL(total_revenue_generated),
        ExternalCompanyFields::TotalRevenueGenerated,
        this->total_revenue_generated ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        total_revenue_generated ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->total_revenue_generated = total_revenue_generated;
    return true;
}

bool ExternalCompany::setOutstandingBalance(
    const MoneyPtr& outstanding_balance, const InternalEmployeePtr& changer
)
{
    if (this->outstanding_balance == nullptr || outstanding_balance == nullptr) {
        if (this->outstanding_balance == outstanding_balance) {
            return false;
        }
    } else if (*this->outstanding_balance == *outstanding_balance) {
        return false;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->outstanding_balance),
        PTR_TO_OPTIONAL(outstanding_balance),
        ExternalCompanyFields::OutstandingBalance,
        this->outstanding_balance ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        outstanding_balance ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->outstanding_balance = outstanding_balance;
    return true;
}

bool ExternalCompany::setChurnProbability(
    const std::optional<double>& churn_probability, const InternalEmployeePtr& changer
)
{
    if (this->churn_probability != churn_probability) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->churn_probability ? std::make_optional(this->churn_probability.value())
                                    : std::nullopt,
            churn_probability ? std::make_optional(churn_probability.value()) : std::nullopt,
            ExternalCompanyFields::ChurnProbability,
            this->churn_probability ? ChangeLog::FieldType::Double : ChangeLog::FieldType::null,
            churn_probability ? ChangeLog::FieldType::Double : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->churn_probability = churn_probability;
        return true;
    }
    return false;
}

bool ExternalCompany::addContact(
    const ExternalEmployeePtr& contact, const InternalEmployeePtr& changer
)
{
    if (std::find(this->contacts.begin(), this->contacts.end(), contact) == this->contacts.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(contact),
            ExternalCompanyFields::Contacts,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::ExternalEmployee,
            ChangeLog::Action::Add
        ));
        this->contacts.push_back(contact);
        return true;
    }
    return false;
}

bool ExternalCompany::delContact(size_t index, const InternalEmployeePtr& changer)
{
    if (this->contacts.size() > index) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->contacts[index]),
            std::nullopt,
            ExternalCompanyFields::Contacts,
            ChangeLog::FieldType::ExternalEmployee,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->contacts.erase(this->contacts.begin() + index);
        return true;
    }
    return false;
}

bool ExternalCompany::addAssociatedClient(
    const ClientPtr& associated_client, const InternalEmployeePtr& changer
)
{
    if (std::find(
            this->associated_clients.begin(), this->associated_clients.end(), associated_client
        ) == this->associated_clients.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(associated_client),
            ExternalCompanyFields::AssociatedClients,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Client,
            ChangeLog::Action::Add
        ));
        this->associated_clients.push_back(associated_client);
        return true;
    }
    return false;
}

bool ExternalCompany::delAssociatedClient(size_t index, const InternalEmployeePtr& changer)
{
    if (this->associated_clients.size() > index) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->associated_clients[index]),
            std::nullopt,
            ExternalCompanyFields::AssociatedClients,
            ChangeLog::FieldType::Client,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->associated_clients.erase(this->associated_clients.begin() + index);
        return true;
    }
    return false;
}

bool ExternalCompany::addDocument(const FilePtr& document, const InternalEmployeePtr& changer)
{
    if (std::find(this->documents.begin(), this->documents.end(), document) ==
        this->documents.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(document),
            ExternalCompanyFields::Documents,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::FileMetadata,
            ChangeLog::Action::Add
        ));
        this->documents.push_back(document);
        return true;
    }
    return false;
}

bool ExternalCompany::delDocument(size_t index, const InternalEmployeePtr& changer)
{
    if (this->documents.size() > index) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->documents[index]),
            std::nullopt,
            ExternalCompanyFields::Documents,
            ChangeLog::FieldType::FileMetadata,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->documents.erase(this->documents.begin() + index);
        return true;
    }
    return false;
}

bool ExternalCompany::setSize(const CompanySize size, const InternalEmployeePtr& changer)
{
    if (this->size != size) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->size),
            std::make_optional(size),
            ExternalCompanyFields::Size,
            ChangeLog::FieldType::CompanySize,
            ChangeLog::FieldType::CompanySize,
            ChangeLog::Action::Change
        ));
        this->size = size;
        return true;
    }
    return false;
}

bool ExternalCompany::setVatNumber(
    const OptionalStr& VAT_number, const InternalEmployeePtr& changer
)
{
    if (this->VAT_number != VAT_number) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->VAT_number),
            OPTIONAL_STR_TO_VALUE(VAT_number),
            ExternalCompanyFields::VatNumber,
            this->VAT_number ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            VAT_number ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->VAT_number = VAT_number;
        return true;
    }
    return false;
}

bool ExternalCompany::setPreferredContactMethod(
    const OptionalStr& preferred_contact_method, const InternalEmployeePtr& changer
)
{
    if (this->preferred_contact_method != preferred_contact_method) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->preferred_contact_method),
            OPTIONAL_STR_TO_VALUE(preferred_contact_method),
            ExternalCompanyFields::PreferredContactMethod,
            this->preferred_contact_method ? ChangeLog::FieldType::String
                                           : ChangeLog::FieldType::null,
            preferred_contact_method ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->preferred_contact_method = preferred_contact_method;
        return true;
    }
    return false;
}

bool ExternalCompany::setPaymentTerms(
    const OptionalStr& payment_terms, const InternalEmployeePtr& changer
)
{
    if (this->payment_terms != payment_terms) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->payment_terms),
            OPTIONAL_STR_TO_VALUE(payment_terms),
            ExternalCompanyFields::PaymentTerms,
            this->payment_terms ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            payment_terms ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->payment_terms = payment_terms;
        return true;
    }
    return false;
}

bool ExternalCompany::setPreferredCurrency(
    const Currencies& preferred_currency, const InternalEmployeePtr& changer
)
{
    if (this->preferred_currency != preferred_currency) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->preferred_currency),
            std::make_optional(preferred_currency),
            ExternalCompanyFields::PreferredCurrency,
            ChangeLog::FieldType::Currencies,
            ChangeLog::FieldType::Currencies,
            ChangeLog::Action::Change
        ));
        this->preferred_currency = preferred_currency;
        return true;
    }
    return false;
}

bool ExternalCompany::setServiceLevelAgreement(
    const OptionalStr& service_level_agreement, const InternalEmployeePtr& changer
)
{
    if (this->service_level_agreement != service_level_agreement) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->service_level_agreement),
            OPTIONAL_STR_TO_VALUE(service_level_agreement),
            ExternalCompanyFields::ServiceLevelAgreement,
            this->service_level_agreement ? ChangeLog::FieldType::String
                                          : ChangeLog::FieldType::null,
            service_level_agreement ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->service_level_agreement = service_level_agreement;
        return true;
    }
    return false;
}

bool ExternalCompany::setPreferredIntegrationTool(
    const OptionalStr& preferred_integration_tool, const InternalEmployeePtr& changer
)
{
    if (this->preferred_integration_tool != preferred_integration_tool) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->preferred_integration_tool),
            OPTIONAL_STR_TO_VALUE(preferred_integration_tool),
            ExternalCompanyFields::PreferredIntegrationTool,
            this->preferred_integration_tool ? ChangeLog::FieldType::String
                                             : ChangeLog::FieldType::null,
            preferred_integration_tool ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->preferred_integration_tool = preferred_integration_tool;
        return true;
    }
    return false;
}

bool ExternalCompany::setIntegrationStatus(
    const std::optional<IntegrationStatus>& integration_status, const InternalEmployeePtr& changer
)
{
    if (this->integration_status != integration_status) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->integration_status ? std::make_optional(this->integration_status.value())
                                     : std::nullopt,
            integration_status ? std::make_optional(integration_status.value()) : std::nullopt,
            ExternalCompanyFields::IntegrationStatus,
            this->integration_status ? ChangeLog::FieldType::IntegrationStatus
                                     : ChangeLog::FieldType::null,
            integration_status ? ChangeLog::FieldType::IntegrationStatus
                               : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->integration_status = integration_status;
        return true;
    }
    return false;
}

bool ExternalCompany::setWinRate(
    const std::optional<double>& win_rate, const InternalEmployeePtr& changer
)
{
    if (this->win_rate != win_rate) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->win_rate ? std::make_optional(this->win_rate.value()) : std::nullopt,
            win_rate ? std::make_optional(win_rate.value()) : std::nullopt,
            ExternalCompanyFields::WinRate,
            this->win_rate ? ChangeLog::FieldType::Double : ChangeLog::FieldType::null,
            win_rate ? ChangeLog::FieldType::Double : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->win_rate = win_rate;
        return true;
    }
    return false;
}

bool ExternalCompany::setComplianceStatus(
    const std::optional<ComplianceLevel>& compliance_status, const InternalEmployeePtr& changer
)
{
    if (this->compliance_status != compliance_status) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->compliance_status ? std::make_optional(this->compliance_status.value())
                                    : std::nullopt,
            compliance_status ? std::make_optional(compliance_status.value()) : std::nullopt,
            ExternalCompanyFields::ComplianceStatus,
            this->compliance_status ? ChangeLog::FieldType::ComplianceLevel
                                    : ChangeLog::FieldType::null,
            compliance_status ? ChangeLog::FieldType::ComplianceLevel : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->compliance_status = compliance_status;
        return true;
    }
    return false;
}