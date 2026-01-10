#pragma once
#include <vector>

#include "Address/address.hpp"
#include "BigNum/big_uint.hpp"
#include "BigNum/money.hpp"
#include "DateTime/date.hpp"
#include "Note/note.hpp"
#include "Person/Employee/external_employee.hpp"
#include "PhoneNumber/phone_number.hpp"
#include "Usings/type_usings.hpp"

struct TaxInfo {
    std::string tax_type;
    double      rate;
    std::string code;
    bool        is_default;

    //
    bool operator==(const TaxInfo& other) const
    {
        if (this->tax_type != other.tax_type) return false;
        if (this->rate != other.rate) return false;
        if (this->code != other.code) return false;
        if (this->is_default != other.is_default) return false;
        return true;
    }
};
class Company {
public:
    enum class CompanyStatus : uint8_t { Active, Inactive, Archived, COUNT };
    Company(const BigUint& id);
    Company(
        const BigUint&                      id,
        const std::string&                  company_name,
        const OptionalStr&                  legal_name,
        const OptionalStr&                  website_url,
        const OptionalStr&                  industry,
        const PhoneNumberPtr&               phone_number,
        const OptionalStr&                  email,
        const OptionalStr&                  country_code,
        const AddressPtr&                   registered_address,
        const DatePtr&                      founded_date,
        const OptionalStr&                  tax_id,
        const std::optional<CompanyStatus>& status,
        const std::optional<uint32_t>&      employee_count,
        const MoneyPtr&                     annual_revenue,
        const MoneyPtr&                     budget,
        std::vector<Note>                   notes,
        std::vector<TaxInfo>                tax_rates,
        std::vector<WeakDealPtr>            deals,
        std::vector<TaskPtr>                tasks,
        std::vector<PhoneNumber>            more_phone_numbers,
        std::vector<std::string>            more_emails
    );

    virtual ~Company() noexcept = default;

    /// @name Getters
    /// @{
    auto getId() const -> const BigUint&;
    auto getCompanyName() const -> const std::string&;
    auto getLegalName() const -> const OptionalStr&;
    auto getWebsiteUrl() const -> const OptionalStr&;
    auto getIndustry() const -> const OptionalStr&;
    auto getPhoneNumber() const -> const PhoneNumberPtr&;
    auto getEmail() const -> const OptionalStr&;
    auto getNotes() const -> const std::vector<Note>&;
    auto getCountryCode() const -> const OptionalStr&;
    auto getRegisteredAddress() const -> const AddressPtr&;
    auto getCreatedAt() const -> const Date&;
    auto getFoundedDate() const -> const DatePtr&;
    auto getTaxRates() const -> const std::vector<TaxInfo>&;
    auto getTaxId() const -> const OptionalStr&;
    auto getStatus() const -> const std::optional<CompanyStatus>&;
    auto getDeals() const -> const std::vector<WeakDealPtr>&;
    auto getTasks() const -> const std::vector<TaskPtr>&;
    auto getMorePhoneNumbers() const -> const std::vector<PhoneNumber>&;
    auto getMoreEmails() const -> const std::vector<std::string>&;
    auto getEmployeeCount() const -> const std::optional<uint32_t>&;
    auto getAnnualRevenue() const -> const MoneyPtr&;
    auto getBudget() const -> const MoneyPtr&;
    auto getChangeLogs() const -> const std::vector<ChangeLogPtr>&;
    /// @}

    /// @name Change functions
    /// @{
    bool setCompanyName(const std::string& company_name, const InternalEmployeePtr& changer);
    bool setLegalName(const OptionalStr& legal_name, const InternalEmployeePtr& changer);
    bool setWebsiteUrl(const OptionalStr& website_url, const InternalEmployeePtr& changer);
    bool setIndustry(const OptionalStr& industry, const InternalEmployeePtr& changer);
    bool setPhoneNumber(const PhoneNumberPtr& phone_number, const InternalEmployeePtr& changer);
    bool setEmail(const OptionalStr& email, const InternalEmployeePtr& changer);
    bool setCountryCode(const OptionalStr& country_code, const InternalEmployeePtr& changer);
    bool setRegisteredAddress(
        const AddressPtr& registered_address, const InternalEmployeePtr& changer
    );
    bool setFoundedDate(const DatePtr& founded_date, const InternalEmployeePtr& changer);
    bool setTaxId(const OptionalStr& tax_id, const InternalEmployeePtr& changer);
    bool setStatus(const std::optional<CompanyStatus>& status, const InternalEmployeePtr& changer);
    bool setEmployeeCount(
        const std::optional<uint32_t>& employee_count, const InternalEmployeePtr& changer
    );
    bool setAnnualRevenue(const MoneyPtr& annual_revenue, const InternalEmployeePtr& changer);
    bool setBudget(const MoneyPtr& budget, const InternalEmployeePtr& changer);

    bool addTaxRate(const TaxInfo& tax_rate, const InternalEmployeePtr& changer);
    bool delTaxRate(size_t index, const InternalEmployeePtr& changer);

    bool addNote(const Note& note, const InternalEmployeePtr& changer);
    bool delNote(size_t index, const InternalEmployeePtr& changer);

    bool addMorePhoneNumber(const PhoneNumber& phone_number, const InternalEmployeePtr& changer);
    bool delMorePhoneNumber(size_t index, const InternalEmployeePtr& changer);

    bool addMoreEmail(const std::string& email, const InternalEmployeePtr& changer);
    bool delMoreEmail(size_t index, const InternalEmployeePtr& changer);

    bool addDeal(const WeakDealPtr& deal, const InternalEmployeePtr& changer);
    bool delDeal(size_t index, const InternalEmployeePtr& changer);

    bool addTask(const TaskPtr& task, const InternalEmployeePtr& changer);
    bool delTask(size_t index, const InternalEmployeePtr& changer);
    /// @}

private:
    BigUint        id;
    std::string    company_name;
    OptionalStr    legal_name;
    OptionalStr    website_url;
    OptionalStr    industry;
    OptionalStr    tax_id;
    PhoneNumberPtr phone_number;

    OptionalStr    email;

    OptionalStr    country_code;
    AddressPtr     registered_address;
    Date           created_at;
    DatePtr        founded_date;

    MoneyPtr       annual_revenue;
    MoneyPtr       budget;
    //
    std::vector<Note>            notes;
    std::vector<TaxInfo>         tax_rates;
    std::optional<CompanyStatus> status;
    std::vector<WeakDealPtr>     deals;
    std::vector<TaskPtr>         tasks;
    std::vector<PhoneNumber>     more_phone_numbers;
    std::vector<std::string>     more_emails;
    std::optional<uint32_t>      employee_count;

protected:
    std::vector<ChangeLogPtr> change_logs;
};