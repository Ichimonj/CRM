#include "company.hpp"

#include "ChangeLog/change_log.hpp"

Company::Company(const BigUint& id) : id(id) {}
Company::Company(
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
    std::vector<DealPtr>                deals,
    std::vector<TaskPtr>                tasks,
    std::vector<PhoneNumber>            more_phone_numbers,
    std::vector<std::string>            more_emails
)
    : id(id)
    , company_name(company_name)
    , legal_name(legal_name)
    , website_url(website_url)
    , industry(industry)
    , phone_number(phone_number)
    , email(email)
    , country_code(country_code)
    , registered_address(registered_address)
    , founded_date(founded_date)
    , tax_id(tax_id)
    , status(status)
    , employee_count(employee_count)
    , annual_revenue(annual_revenue)
    , budget(budget)
    , notes(std::move(notes))
    , tax_rates(std::move(tax_rates))
    , deals(std::move(deals))
    , tasks(std::move(tasks))
    , more_phone_numbers(std::move(more_phone_numbers))
    , more_emails(std::move(more_emails))
{
    this->created_at = Date();
}

auto Company::getId() const -> const BigUint& { return this->id; }
auto Company::getCompanyName() const -> const std::string& { return this->company_name; }
auto Company::getLegalName() const -> const OptionalStr& { return this->legal_name; }
auto Company::getWebsiteUrl() const -> const OptionalStr& { return this->website_url; }
auto Company::getPhoneNumber() const -> const PhoneNumberPtr& { return this->phone_number; }
auto Company::getEmail() const -> const OptionalStr& { return this->email; }
auto Company::getNotes() const -> const std::vector<Note>& { return this->notes; }
auto Company::getRegisteredAddress() const -> const AddressPtr& { return this->registered_address; }
auto Company::getCreatedAt() const -> const Date& { return this->created_at; }
auto Company::getMorePhoneNumbers() const -> const std::vector<PhoneNumber>&
{
    return this->more_phone_numbers;
}
auto Company::getMoreEmails() const -> const std::vector<std::string>& { return this->more_emails; }
auto Company::getEmployeeCount() const -> const std::optional<uint32_t>&
{
    return this->employee_count;
}
auto Company::getAnnualRevenue() const -> const MoneyPtr& { return this->annual_revenue; }
auto Company::getChangeLogs() const -> const std::vector<ChangeLogPtr>&
{
    return this->change_logs;
}
auto Company::getIndustry() const -> const OptionalStr& { return this->industry; }
auto Company::getCountryCode() const -> const OptionalStr& { return this->country_code; }
auto Company::getFoundedDate() const -> const DatePtr& { return this->founded_date; }
auto Company::getTaxRates() const -> const std::vector<TaxInfo>& { return this->tax_rates; }
auto Company::getTaxId() const -> const OptionalStr& { return this->tax_id; }
auto Company::getStatus() const -> const std::optional<CompanyStatus>& { return this->status; }
auto Company::getDeals() const -> const std::vector<DealPtr>& { return this->deals; }
auto Company::getTasks() const -> const std::vector<TaskPtr>& { return this->tasks; }
auto Company::getBudget() const -> const MoneyPtr& { return this->budget; }

bool Company::setCompanyName(const std::string& company_name, const InternalEmployeePtr& changer)
{
    if (this->company_name != company_name) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<std::string>(this->company_name)
            ),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(company_name)
            ),
            CompanyFields::CompanyName,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->company_name = company_name;
        return true;
    }
    return false;
}

bool Company::setLegalName(const OptionalStr& legal_name, const InternalEmployeePtr& changer)
{
    if (this->legal_name != legal_name) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->legal_name),
            OPTIONAL_STR_TO_VALUE(legal_name),
            CompanyFields::LegalName,
            this->legal_name ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            legal_name ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->legal_name = legal_name;
        return true;
    }
    return false;
}

bool Company::setWebsiteUrl(const OptionalStr& website_url, const InternalEmployeePtr& changer)
{
    if (this->website_url != website_url) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->website_url),
            OPTIONAL_STR_TO_VALUE(website_url),
            CompanyFields::WebsiteUrl,
            this->website_url ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            website_url ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->website_url = website_url;
        return true;
    }
    return false;
}

bool Company::setPhoneNumber(const PhoneNumberPtr& phone_number, const InternalEmployeePtr& changer)
{
    if (this->phone_number == nullptr || phone_number == nullptr) {
        if (this->phone_number == phone_number) {
            return false;
        }
    } else if (*this->phone_number == *phone_number) {
        return false;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->phone_number),
        PTR_TO_OPTIONAL(phone_number),
        CompanyFields::PhoneNumber,
        this->phone_number ? ChangeLog::FieldType::PhoneNumber : ChangeLog::FieldType::null,
        phone_number ? ChangeLog::FieldType::PhoneNumber : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->phone_number = phone_number;
    return true;
}

bool Company::setEmail(const OptionalStr& email, const InternalEmployeePtr& changer)
{
    if (this->email != email) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->email),
            OPTIONAL_STR_TO_VALUE(email),
            CompanyFields::Email,
            this->email ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            email ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->email = email;
        return true;
    }
    return false;
}

bool Company::setRegisteredAddress(
    const AddressPtr& registered_address, const InternalEmployeePtr& changer
)
{
    if (this->registered_address == nullptr || registered_address == nullptr) {
        if (this->registered_address == registered_address) {
            return false;
        }
    } else if (*this->registered_address == *registered_address) {
        return false;
    }
    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->registered_address),
        PTR_TO_OPTIONAL(registered_address),
        CompanyFields::RegisteredAddress,
        this->registered_address ? ChangeLog::FieldType::Address : ChangeLog::FieldType::null,
        registered_address ? ChangeLog::FieldType::Address : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->registered_address = registered_address;
    return true;
}

bool Company::setEmployeeCount(
    const std::optional<uint32_t>& employee_count, const InternalEmployeePtr& changer
)
{
    if (this->employee_count != employee_count) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->employee_count ? std::make_optional(this->employee_count.value()) : std::nullopt,
            employee_count ? std::make_optional(employee_count.value()) : std::nullopt,
            CompanyFields::EmployeeCount,
            this->employee_count ? ChangeLog::FieldType::Uint : ChangeLog::FieldType::null,
            employee_count ? ChangeLog::FieldType::Uint : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->employee_count = employee_count;
        return true;
    }
    return false;
}

bool Company::setAnnualRevenue(const MoneyPtr& annual_revenue, const InternalEmployeePtr& changer)
{
    if (this->annual_revenue == nullptr || annual_revenue == nullptr) {
        if (this->annual_revenue == annual_revenue) {
            return false;
        }
    } else if (*this->annual_revenue == *annual_revenue) {
        return false;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->annual_revenue),
        PTR_TO_OPTIONAL(annual_revenue),
        CompanyFields::AnnualRevenue,
        this->annual_revenue ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        annual_revenue ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->annual_revenue = annual_revenue;
    return true;
}

bool Company::addNote(const Note& note, const InternalEmployeePtr& changer)
{
    if (std::find(this->notes.begin(), this->notes.end(), note) == this->notes.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<Note>(note)),
            CompanyFields::Notes,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Note,
            ChangeLog::Action::Add
        ));
        this->notes.push_back(note);
        return true;
    }
    return false;
}

bool Company::delNote(size_t index, const InternalEmployeePtr& changer)
{
    if (this->notes.size() > index) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<Note>(this->notes[index])),
            std::nullopt,
            CompanyFields::Notes,
            ChangeLog::FieldType::Note,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->notes.erase(this->notes.begin() + index);
        return true;
    }
    return false;
}

bool Company::addMorePhoneNumber(
    const PhoneNumber& phone_number, const InternalEmployeePtr& changer
)
{
    if (std::find(this->more_phone_numbers.begin(), this->more_phone_numbers.end(), phone_number) ==
        this->more_phone_numbers.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<PhoneNumber>(phone_number)
            ),
            CompanyFields::MorePhoneNumbers,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::PhoneNumber,
            ChangeLog::Action::Add
        ));
        this->more_phone_numbers.push_back(phone_number);
        return true;
    }
    return false;
}

bool Company::delMorePhoneNumber(size_t index, const InternalEmployeePtr& changer)
{
    if (this->more_phone_numbers.size() > index) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<PhoneNumber>(this->more_phone_numbers[index])
            ),
            std::nullopt,
            CompanyFields::MorePhoneNumbers,
            ChangeLog::FieldType::PhoneNumber,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->more_phone_numbers.erase(this->more_phone_numbers.begin() + index);
        return true;
    }
    return false;
}

bool Company::addMoreEmail(const std::string& email, const InternalEmployeePtr& changer)
{
    if (std::find(this->more_emails.begin(), this->more_emails.end(), email) ==
        this->more_emails.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(email)),
            CompanyFields::MoreEmails,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Add
        ));
        this->more_emails.push_back(email);
        return true;
    }
    return false;
}

bool Company::delMoreEmail(size_t index, const InternalEmployeePtr& changer)
{
    if (this->more_emails.size() > index) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<std::string>(this->more_emails[index])
            ),
            std::nullopt,
            CompanyFields::MoreEmails,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->more_emails.erase(this->more_emails.begin() + index);
        return true;
    }
    return false;
}

bool Company::setIndustry(const OptionalStr& industry, const InternalEmployeePtr& changer)
{
    if (this->industry != industry) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->industry),
            OPTIONAL_STR_TO_VALUE(industry),
            CompanyFields::Industry,
            this->industry ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            industry ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->industry = industry;
        return true;
    }
    return false;
}

bool Company::setCountryCode(const OptionalStr& country_code, const InternalEmployeePtr& changer)
{
    if (this->country_code != country_code) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->country_code),
            OPTIONAL_STR_TO_VALUE(country_code),
            CompanyFields::CountryCode,
            this->country_code ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            country_code ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->country_code = country_code;
        return true;
    }
    return false;
}

bool Company::setFoundedDate(const DatePtr& founded_date, const InternalEmployeePtr& changer)
{
    if (this->founded_date == nullptr || founded_date == nullptr) {
        if (this->founded_date == founded_date) {
            return false;
        }
    } else if (*this->founded_date == *founded_date) {
        return false;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->founded_date),
        PTR_TO_OPTIONAL(founded_date),
        CompanyFields::FoundedDate,
        this->founded_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        founded_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->founded_date = founded_date;
    return true;
}

bool Company::setTaxId(const OptionalStr& tax_id, const InternalEmployeePtr& changer)
{
    if (this->tax_id != tax_id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->tax_id),
            OPTIONAL_STR_TO_VALUE(tax_id),
            CompanyFields::TaxId,
            this->tax_id ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            tax_id ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->tax_id = tax_id;
        return true;
    }
    return false;
}

bool Company::setStatus(
    const std::optional<CompanyStatus>& status, const InternalEmployeePtr& changer
)
{
    if (this->status != status) {
        std::optional<ChangeLog::ValueVariant> old_value =
            this->status == std::nullopt
                ? std::nullopt
                : std::make_optional<ChangeLog::ValueVariant>(CompanyStatus(this->status.value()));

        std::optional<ChangeLog::ValueVariant> new_value =
            status == std::nullopt
                ? std::nullopt
                : std::make_optional<ChangeLog::ValueVariant>(CompanyStatus(status.value()));

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            old_value,
            new_value,
            CompanyFields::Status,
            old_value == std::nullopt ? ChangeLog::FieldType::null
                                      : ChangeLog::FieldType::CompanyStatus,
            new_value == std::nullopt ? ChangeLog::FieldType::null
                                      : ChangeLog::FieldType::CompanyStatus,
            ChangeLog::Action::Change
        ));
        this->status = status;
        return true;
    }
    return false;
}

bool Company::setBudget(const MoneyPtr& budget, const InternalEmployeePtr& changer)
{
    if (this->budget == nullptr || budget == nullptr) {
        if (this->budget == budget) {
            return false;
        }
    } else if (*this->budget == *budget) {
        return false;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->budget),
        PTR_TO_OPTIONAL(budget),
        CompanyFields::Budget,
        this->budget ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        budget ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->budget = budget;
    return true;
}

bool Company::addTaxRate(const TaxInfo& tax_rate, const InternalEmployeePtr& changer)
{
    if (std::find(this->tax_rates.begin(), this->tax_rates.end(), tax_rate) ==
        this->tax_rates.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<TaxInfo>(tax_rate)),
            CompanyFields::TaxRates,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::TaxInfo,
            ChangeLog::Action::Add
        ));
        this->tax_rates.push_back(tax_rate);
        return true;
    }
    return false;
}

bool Company::delTaxRate(size_t index, const InternalEmployeePtr& changer)
{
    if (index < this->tax_rates.size()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<TaxInfo>(this->tax_rates[index])
            ),
            std::nullopt,
            CompanyFields::TaxRates,
            ChangeLog::FieldType::TaxInfo,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->tax_rates.erase(this->tax_rates.begin() + index);
        return true;
    }
    return false;
}

bool Company::addDeal(const DealPtr& deal, const InternalEmployeePtr& changer)
{
    if (std::find(this->deals.begin(), this->deals.end(), deal) == this->deals.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(deal),
            CompanyFields::Deals,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Deal,
            ChangeLog::Action::Add
        ));
        this->deals.push_back(deal);
        return true;
    }
    return false;
}

bool Company::delDeal(size_t index, const InternalEmployeePtr& changer)
{
    if (index < this->deals.size()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->deals[index]),
            std::nullopt,
            CompanyFields::Deals,
            ChangeLog::FieldType::Deal,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->deals.erase(this->deals.begin() + index);
        return true;
    }
    return false;
}

bool Company::addTask(const TaskPtr& task, const InternalEmployeePtr& changer)
{
    if (std::find(this->tasks.begin(), this->tasks.end(), task) == this->tasks.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(task),
            CompanyFields::Tasks,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Task,
            ChangeLog::Action::Add
        ));
        this->tasks.push_back(task);
        return true;
    }
    return false;
}

bool Company::delTask(size_t index, const InternalEmployeePtr& changer)
{
    if (index < this->tasks.size()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->tasks[index]),
            std::nullopt,
            CompanyFields::Tasks,
            ChangeLog::FieldType::Task,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->tasks.erase(this->tasks.begin() + index);
        return true;
    }
    return false;
}