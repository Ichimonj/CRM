#include "deal.hpp"

#include <utility>

#include "change_log.hpp"

Deal::Deal(const BigUint& id) : id(id) {}

Deal::Deal(
    const BigUint&                         id,
    const std::string&                     contract_number,
    const std::string&                     title,
    const OptionalStr&                     description,
    const OptionalStr&                     source,
    std::vector<std::string>               tags,
    std::vector<BuyerShare>                buyers,
    const Money&                           total_amount,
    const Money&                           paid_amount,
    const std::optional<Currencies>&       currency,
    const OptionalStr&                     other_currency,
    const PaymentArr&                      payment_transactions,
    const Status&                          status,
    const OptionalStr&                     other_status,
    const Priority&                        deal_priority,
    const DatePtr&                         drawing_date,
    const DatePtr&                         date_approval,
    const Date&                            creation_date,
    const InternalEmployeePtr              manager,
    std::vector<InternalEmployeePtr>       assigned_employees,
    std::vector<OfferPtr>                  offers,
    std::vector<DocumentPtr>               documents,
    std::vector<TaskPtr>                   tasks,
    const std::weak_ptr<Person>&           owner,
    const std::weak_ptr<InternalEmployee>& deal_manager,
    std::vector<OfferPtr>                  offerings
)
    : id(id)
    , contract_number(contract_number)
    , title(title)
    , description(description)
    , source(source)
    , tags(std::move(tags))
    , buyers(std::move(buyers))
    , total_amount(total_amount)
    , paid_amount(paid_amount)
    , currency(currency)
    , other_currency(other_currency)
    , payment_transactions(payment_transactions)
    , status(status)
    , other_status(other_status)
    , deal_priority(deal_priority)
    , drawing_date(drawing_date)
    , date_approval(date_approval)
    , creation_date(creation_date)
    , manager(manager)
    , assigned_employees(std::move(assigned_employees))
    , offers(std::move(offers))
    , documents(std::move(documents))
    , tasks(std::move(tasks))
    , owner(owner)
    , deal_manager(deal_manager)
    , offerings(std::move(offerings))
{
}

auto Deal::getId() const -> const BigUint& { return id; }
auto Deal::getContractNumber() const -> const std::string& { return contract_number; }
auto Deal::getTitle() const -> const std::string& { return title; }
auto Deal::getDescription() const -> const OptionalStr& { return description; }
auto Deal::getSource() const -> const OptionalStr& { return source; }
auto Deal::getTags() const -> const std::vector<std::string>& { return tags; }
auto Deal::getBuyers() const -> const std::vector<BuyerShare>& { return buyers; }
auto Deal::getTotalAmount() const -> const Money& { return total_amount; }
auto Deal::getPaidAmount() const -> const Money& { return paid_amount; }
auto Deal::getCurrency() const -> const std::optional<Currencies>& { return currency; }
auto Deal::getOtherCurrency() const -> const OptionalStr& { return other_currency; }
auto Deal::getPaymentTransactions() const -> const PaymentArr& { return payment_transactions; }
auto Deal::getStatus() const -> const Status& { return status; }
auto Deal::getOtherStatus() const -> const OptionalStr& { return other_status; }
auto Deal::getDealPriority() const -> const Priority& { return deal_priority; }
auto Deal::getDrawingDate() const -> const DatePtr& { return drawing_date; }
auto Deal::getDateApproval() const -> const DatePtr& { return date_approval; }
auto Deal::getCreationDate() const -> const Date& { return creation_date; }
auto Deal::getManager() const -> const InternalEmployeePtr& { return manager; }
auto Deal::getAssignedEmployees() const -> const std::vector<InternalEmployeePtr>&
{
    return assigned_employees;
}
auto Deal::getOffers() const -> const std::vector<OfferPtr>& { return offers; }
auto Deal::getDocuments() const -> const std::vector<DocumentPtr>& { return documents; }
auto Deal::getTasks() const -> const std::vector<TaskPtr>& { return tasks; }
auto Deal::getOwner() const -> const std::weak_ptr<Person>& { return owner; }
auto Deal::getDealManager() const -> const std::weak_ptr<InternalEmployee>& { return deal_manager; }
auto Deal::getOfferings() const -> const std::vector<OfferPtr>& { return offerings; }
auto Deal::getChangeLogs() const -> const std::vector<ChangeLogPtr>& { return change_logs; }

void Deal::changeContractNumber(const std::string& number, const InternalEmployeePtr& changer)
{
    if (this->contract_number != number) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<std::string>(this->contract_number)),
            std::make_optional(std::make_shared<std::string>(number)),
            DealFields::ContractNumber,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->contract_number = number;
    }
}

void Deal::changeTitle(const std::string& title, const InternalEmployeePtr& changer)
{
    if (this->title != title) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<std::string>(this->title)),
            std::make_optional(std::make_shared<std::string>(title)),
            DealFields::Title,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->title = title;
    }
}

void Deal::changeDescription(const OptionalStr& description, const InternalEmployeePtr& changer)
{
    if (this->description != description) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->description),
            OPTIONAL_STR_TO_VALUE(description),
            DealFields::Description,
            this->description ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            description ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->description = description;
    }
}

void Deal::changeSource(const OptionalStr& source, const InternalEmployeePtr& changer)
{
    if (this->source != source) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->source),
            OPTIONAL_STR_TO_VALUE(source),
            DealFields::Description,
            this->source ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            source ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->source = source;
    }
}

void Deal::addTag(const std::string& tag, const InternalEmployeePtr& changer)
{
    if (std::find(this->tags.begin(), this->tags.end(), tag) == this->tags.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(std::make_shared<std::string>(tag)),
            DealFields::Tags,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Add
        ));
        this->tags.push_back(tag);
    }
}

void Deal::delTag(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->tags.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<std::string>(this->tags[id])),
            std::nullopt,
            DealFields::Tags,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->tags.erase(this->tags.begin() + id);
    }
}

void Deal::addBuyer(
    const std::shared_ptr<Person>& buyer, const Money& money, const InternalEmployeePtr& changer
)
{
    if (std::find_if(this->buyers.begin(), this->buyers.end(), [&buyer](const BuyerShare& person) {
            return person.first == buyer;
        }) == this->buyers.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(std::make_shared<BuyerShare>(buyer, money)),
            DealFields::Buyers,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::PersonMoneyPair,
            ChangeLog::Action::Add
        ));
        this->buyers.push_back(std::make_pair(buyer, money));
    }
}

void Deal::delBuyer(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->buyers.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<BuyerShare>(this->buyers[id])),
            std::nullopt,
            DealFields::Buyers,
            ChangeLog::FieldType::PersonMoneyPair,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->buyers.erase(this->buyers.begin() + id);
    }
}

void Deal::updateBuyerMoney(size_t id, const Money& newMoney, const InternalEmployeePtr& changer)
{
    if (this->buyers.size() > id) {
        if (this->buyers[id].second != newMoney) {
            this->change_logs.emplace_back(std::make_shared<ChangeLog>(
                changer,
                std::make_optional(std::make_shared<BuyerShare>(this->buyers[id])),
                std::make_optional(
                    std::make_shared<BuyerShare>(std::make_pair(this->buyers[id].first, newMoney))
                ),
                DealFields::Buyers,
                ChangeLog::FieldType::PersonMoneyPair,
                ChangeLog::FieldType::PersonMoneyPair,
                ChangeLog::Action::Change
            ));
            this->buyers[id].second = newMoney;
        }
    }
}

void Deal::updateTotalAmount(const Money& amount, const InternalEmployeePtr& changer)
{
    if (this->total_amount != amount) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<std::string>(this->total_amount.num)),
            std::make_optional(std::make_shared<std::string>(amount.num)),
            DealFields::TotalAmount,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->total_amount = amount;
    }
}

void Deal::updatePaidAmount(const Money& amount, const InternalEmployeePtr& changer)
{
    if (this->paid_amount != amount) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<std::string>(this->paid_amount.num)),
            std::make_optional(std::make_shared<std::string>(amount.num)),
            DealFields::PaidAmount,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->paid_amount = amount;
    }
}

void Deal::changeCurrency(
    const std::optional<Currencies>& currency, const InternalEmployeePtr& changer
)
{
    if (this->currency != currency) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->currency,
            currency,
            DealFields::Currency,
            this->currency ? ChangeLog::FieldType::Currencies : ChangeLog::FieldType::null,
            currency ? ChangeLog::FieldType::Currencies : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->currency       = currency;
        this->other_currency = std::nullopt;
    }
}

void Deal::changeOtherCurrency(const OptionalStr& currency, const InternalEmployeePtr& changer)
{
    if (this->other_currency != currency) {
        std::optional<ChangeLog::ValueVariant> old_value;
        ChangeLog::FieldType                   old_field;

        if (this->currency != std::nullopt) {
            old_value = this->currency;
            old_field = ChangeLog::FieldType::Currencies;
        } else if (this->other_currency != std::nullopt) {
            old_value = std::make_shared<std::string>(other_currency.value());
            old_field = ChangeLog::FieldType::String;
        } else
            old_field = ChangeLog::FieldType::null;

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::move(old_value),
            OPTIONAL_STR_TO_VALUE(currency),
            DealFields::Currency,
            old_field,
            currency ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->other_currency = currency;
        this->currency       = std::nullopt;
    }
}

void Deal::addPaymentTransaction(
    const std::shared_ptr<Payment>& payment, const InternalEmployeePtr& changer
)
{
    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        std::nullopt,
        std::make_optional(payment),
        DealFields::PaymentTransactions,
        ChangeLog::FieldType::null,
        ChangeLog::FieldType::Payment,
        ChangeLog::Action::Add
    ));
    this->payment_transactions.push_back(payment);
}

void Deal::delPaymentTransaction(size_t id, const InternalEmployeePtr& changer)
{
    if (this->payment_transactions.size() > id) {
        auto removed = this->payment_transactions[id];
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(removed),
            std::nullopt,
            DealFields::PaymentTransactions,
            ChangeLog::FieldType::Payment,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->payment_transactions.erase(this->payment_transactions.begin() + id);
    }
}

void Deal::changeStatus(const Status status, const InternalEmployeePtr& changer)
{
    if (this->status != status) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->other_status
                ? std::make_optional(std::make_shared<std::string>(this->other_status.value()))
                : std::make_optional<ChangeLog::ValueVariant>(this->status),
            std::make_optional(status),
            DealFields::Status,
            this->other_status ? ChangeLog::FieldType::String : ChangeLog::FieldType::DealStatus,
            ChangeLog::FieldType::DealStatus,
            ChangeLog::Action::Change
        ));
        this->other_status = std::nullopt;
        this->status       = status;
    }
}

void Deal::changeOtherStatus(const OptionalStr& status, const InternalEmployeePtr& changer)
{
    if (this->other_status != status) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->other_status
                ? std::make_optional(std::make_shared<std::string>(this->other_status.value()))
                : std::make_optional<ChangeLog::ValueVariant>(this->status),
            status ? std::make_optional(std::make_shared<std::string>(status.value()))
                   : std::nullopt,
            DealFields::OtherStatus,
            this->other_status ? ChangeLog::FieldType::String : ChangeLog::FieldType::DealStatus,
            status ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->status       = Status::Other;
        this->other_status = status;
    }
}

void Deal::changeDealPriority(const Priority priority, const InternalEmployeePtr& changer)
{
    if (this->deal_priority != priority) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->deal_priority),
            std::make_optional(priority),
            DealFields::DealPriority,
            ChangeLog::FieldType::Priority,
            ChangeLog::FieldType::Priority,
            ChangeLog::Action::Change
        ));
        this->deal_priority = priority;
    }
}

void Deal::setDrawingDate(const DatePtr& date, const InternalEmployeePtr& changer)
{
    if (this->drawing_date == nullptr || date == nullptr) {
        if (this->drawing_date == date) {
            return;
        }
    } else if (*this->drawing_date == *date) {
        return;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->drawing_date),
        PTR_TO_OPTIONAL(date),
        DealFields::DrawingDate,
        this->drawing_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->drawing_date = date;
}

void Deal::setDateApproval(const DatePtr& date, const InternalEmployeePtr& changer)
{
    if (this->date_approval == nullptr || date == nullptr) {
        if (this->date_approval == date) {
            return;
        }
    } else if (*this->date_approval == *date) {
        return;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->date_approval),
        PTR_TO_OPTIONAL(date),
        DealFields::DateApproval,
        this->date_approval ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->date_approval = date;
}

void Deal::changeManager(const InternalEmployeePtr& manager, const InternalEmployeePtr& changer)
{
    if (this->manager != manager) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->manager),
            PTR_TO_OPTIONAL(manager),
            DealFields::Manager,
            this->manager ? ChangeLog::FieldType::InternalEmployee : ChangeLog::FieldType::null,
            manager ? ChangeLog::FieldType::InternalEmployee : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->manager = manager;
    }
}

void Deal::addAssignedEmployee(
    const InternalEmployeePtr& employee, const InternalEmployeePtr& changer
)
{
    if (std::find(this->assigned_employees.begin(), this->assigned_employees.end(), employee) ==
        this->assigned_employees.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(employee),
            DealFields::AssignedEmployees,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::InternalEmployee,
            ChangeLog::Action::Add
        ));
        this->assigned_employees.push_back(employee);
    }
}

void Deal::delAssignedEmployee(size_t id, const InternalEmployeePtr& changer)
{
    if (this->assigned_employees.size() > id) {
        auto removed = this->assigned_employees[id];
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(removed),
            std::nullopt,
            DealFields::AssignedEmployees,
            ChangeLog::FieldType::InternalEmployee,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->assigned_employees.erase(this->assigned_employees.begin() + id);
    }
}

void Deal::addOffer(const OfferPtr& offer, const InternalEmployeePtr& changer)
{
    if (std::find(this->offers.begin(), this->offers.end(), offer) == this->offers.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(offer),
            DealFields::Offers,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Offer,
            ChangeLog::Action::Add
        ));
        this->offers.push_back(offer);
    }
}

void Deal::delOffer(size_t index, const InternalEmployeePtr& changer)
{
    if (this->offers.size() > index) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->offers[index]),
            std::nullopt,
            DealFields::Offers,
            ChangeLog::FieldType::Offer,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->offers.erase(this->offers.begin() + index);
    }
}

void Deal::addDocument(const DocumentPtr& document, const InternalEmployeePtr& changer)
{
    if (std::find(this->documents.begin(), this->documents.end(), document) ==
        this->documents.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(document),
            DealFields::Documents,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Document,
            ChangeLog::Action::Add
        ));
        this->documents.push_back(document);
    }
}

void Deal::delDocument(size_t id, const InternalEmployeePtr& changer)
{
    if (this->documents.size() > id) {
        auto removed = this->documents[id];
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(removed),
            std::nullopt,
            DealFields::Documents,
            ChangeLog::FieldType::Document,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->documents.erase(this->documents.begin() + id);
    }
}

void Deal::addTask(const TaskPtr& task, const InternalEmployeePtr& changer)
{
    if (std::find(this->tasks.begin(), this->tasks.end(), task) == this->tasks.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(task),
            DealFields::Task,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Task,
            ChangeLog::Action::Add
        ));
        this->tasks.push_back(task);
    }
}

void Deal::delTask(size_t index, const InternalEmployeePtr& changer)
{
    if (this->tasks.size() > index) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->tasks[index]),
            std::nullopt,
            DealFields::Task,
            ChangeLog::FieldType::Task,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->tasks.erase(this->tasks.begin() + index);
    }
}

void Deal::setOwner(const std::weak_ptr<Person>& owner, const InternalEmployeePtr& changer)
{
    if (this->owner.lock() != owner.lock()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->owner.lock()),
            PTR_TO_OPTIONAL(owner.lock()),
            DealFields::Owner,
            this->owner.lock() ? ChangeLog::FieldType::Person : ChangeLog::FieldType::null,
            owner.lock() ? ChangeLog::FieldType::Person : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->owner = owner;
    }
}

void Deal::setDealManager(
    const std::weak_ptr<InternalEmployee>& manager, const InternalEmployeePtr& changer
)
{
    if (this->deal_manager.lock() != manager.lock()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->deal_manager.lock()),
            PTR_TO_OPTIONAL(manager.lock()),
            DealFields::DealManager,
            this->deal_manager.lock() ? ChangeLog::FieldType::Person : ChangeLog::FieldType::null,
            manager.lock() ? ChangeLog::FieldType::Person : ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->deal_manager = manager;
    }
}

void Deal::addOffering(const OfferPtr& offering, const InternalEmployeePtr& changer)
{
    if (std::find(this->offerings.begin(), this->offerings.end(), offering) ==
        this->offerings.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(offering),
            DealFields::Offerings,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Offer,
            ChangeLog::Action::Add
        ));
        this->offerings.push_back(offering);
    }
}

void Deal::delOffering(size_t index, const InternalEmployeePtr& changer)
{
    if (this->offerings.size() > index) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->offerings[index]),
            std::nullopt,
            DealFields::Offerings,
            ChangeLog::FieldType::Offer,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->offerings.erase(this->offerings.begin() + index);
    }
}