#include "deal.hpp"

#include <utility>

#include "ChangeLog/change_log.hpp"

Deal::Deal(const BigUint& id) : id(id) {}

Deal::Deal(
    const BigUint&                    id,
    const std::string&                contract_number,
    const std::string&                title,
    const OptionalStr&                description,
    const OptionalStr&                source,
    const Money&                      total_amount,
    const Money&                      paid_amount,
    const Status&                     status,
    const OptionalStr&                other_status,
    const Priority&                   deal_priority,
    const DatePtr&                    drawing_date,
    const DatePtr&                    date_approval,
    const Date&                       creation_date,
    const WeakPersonPtr&              owner,
    const WeakInternalEmployee&       manager,
    std::vector<std::string>          tags,
    std::vector<WeakBuyerShare>       buyers,
    std::vector<PaymentPtr>           payment_transactions,
    std::vector<WeakInternalEmployee> assigned_employees,
    std::vector<OfferDealPtr>         offers,
    std::vector<DocumentPtr>          documents,
    std::vector<TaskPtr>              tasks,
    std::vector<OfferDealPtr>         offerings
)
    : id(id)
    , contract_number(contract_number)
    , title(title)
    , description(description)
    , source(source)
    , total_amount(total_amount)
    , paid_amount(paid_amount)
    , status(status)
    , other_status(other_status)
    , deal_priority(deal_priority)
    , drawing_date(drawing_date)
    , date_approval(date_approval)
    , creation_date(creation_date)
    , owner(owner)
    , manager(manager)
    , tags(std::move(tags))
    , buyers(std::move(buyers))
    , payment_transactions(std::move(payment_transactions))
    , assigned_employees(std::move(assigned_employees))
    , offers(std::move(offers))
    , documents(std::move(documents))
    , tasks(std::move(tasks))
    , offerings(std::move(offerings))
{
}

auto Deal::getId() const -> const BigUint& { return id; }
auto Deal::getContractNumber() const -> const std::string& { return contract_number; }
auto Deal::getTitle() const -> const std::string& { return title; }
auto Deal::getDescription() const -> const OptionalStr& { return description; }
auto Deal::getSource() const -> const OptionalStr& { return source; }
auto Deal::getTags() const -> const std::vector<std::string>& { return tags; }
auto Deal::getBuyers() const -> const std::vector<WeakBuyerShare>& { return buyers; }
auto Deal::getTotalAmount() const -> const Money& { return total_amount; }
auto Deal::getPaidAmount() const -> const Money& { return paid_amount; }
auto Deal::getPaymentTransactions() const -> const std::vector<PaymentPtr>&
{
    return payment_transactions;
}
auto Deal::getStatus() const -> const Status& { return status; }
auto Deal::getOtherStatus() const -> const OptionalStr& { return other_status; }
auto Deal::getDealPriority() const -> const Priority& { return deal_priority; }
auto Deal::getDrawingDate() const -> const DatePtr& { return drawing_date; }
auto Deal::getDateApproval() const -> const DatePtr& { return date_approval; }
auto Deal::getCreationDate() const -> const Date& { return creation_date; }
auto Deal::getAssignedEmployees() const -> const std::vector<WeakInternalEmployee>&
{
    return assigned_employees;
}
auto Deal::getOffers() const -> const std::vector<OfferDealPtr>& { return offers; }
auto Deal::getDocuments() const -> const std::vector<DocumentPtr>& { return documents; }
auto Deal::getTasks() const -> const std::vector<TaskPtr>& { return tasks; }
auto Deal::getOwner() const -> const WeakPersonPtr& { return owner; }
auto Deal::getManager() const -> const WeakInternalEmployee& { return this->manager; }
auto Deal::getOfferings() const -> const std::vector<OfferDealPtr>& { return offerings; }
auto Deal::getChangeLogs() const -> const std::vector<ChangeLogPtr>& { return change_logs; }

bool Deal::changeContractNumber(const std::string& number, const InternalEmployeePtr& changer)
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
        return true;
    }
    return false;
}

bool Deal::changeTitle(const std::string& title, const InternalEmployeePtr& changer)
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
        return true;
    }
    return false;
}

bool Deal::changeDescription(const OptionalStr& description, const InternalEmployeePtr& changer)
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
        return true;
    }
    return false;
}

bool Deal::changeSource(const OptionalStr& source, const InternalEmployeePtr& changer)
{
    if (this->source != source) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->source),
            OPTIONAL_STR_TO_VALUE(source),
            DealFields::Source,
            this->source ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            source ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->source = source;
        return true;
    }
    return false;
}

bool Deal::changeTotalAmount(const Money& amount, const InternalEmployeePtr& changer)
{
    if (this->total_amount != amount) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<Money>(this->total_amount)),
            std::make_optional(std::make_shared<Money>(amount)),
            DealFields::TotalAmount,
            ChangeLog::FieldType::Money,
            ChangeLog::FieldType::Money,
            ChangeLog::Action::Change
        ));
        this->total_amount = amount;
        return true;
    }
    return false;
}

bool Deal::changePaidAmount(const Money& amount, const InternalEmployeePtr& changer)
{
    if (this->paid_amount != amount) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<Money>(this->paid_amount)),
            std::make_optional(std::make_shared<Money>(amount)),
            DealFields::PaidAmount,
            ChangeLog::FieldType::Money,
            ChangeLog::FieldType::Money,
            ChangeLog::Action::Change
        ));
        this->paid_amount = amount;
        return true;
    }
    return false;
}

bool Deal::changeStatus(const Status status, const InternalEmployeePtr& changer)
{
    if (this->status != status) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->other_status ? std::make_optional<ChangeLog::ValueVariant>(
                                     std::make_shared<std::string>(this->other_status.value())
                                 )
                               : std::make_optional<ChangeLog::ValueVariant>(this->status),
            std::make_optional<ChangeLog::ValueVariant>(status),
            DealFields::Status,
            this->other_status ? ChangeLog::FieldType::String
                               : ChangeLog::FieldType::DealStatus,
            ChangeLog::FieldType::DealStatus,
            ChangeLog::Action::Change
        ));
        this->other_status = std::nullopt;
        this->status       = status;
        return true;
    }
    return false;
}

bool Deal::changeOtherStatus(const OptionalStr& status, const InternalEmployeePtr& changer)
{
    if (this->other_status != status) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->other_status ? std::make_optional<ChangeLog::ValueVariant>(
                                     std::make_shared<std::string>(this->other_status.value())
                                 )
                               : std::make_optional<ChangeLog::ValueVariant>(this->status),
            status ? std::make_optional<ChangeLog::ValueVariant>(
                         std::make_shared<std::string>(status.value())
                     )
                   : std::nullopt,
            DealFields::Status,
            this->other_status ? ChangeLog::FieldType::String
                               : ChangeLog::FieldType::DealStatus,
            status ? ChangeLog::FieldType::String : ChangeLog::FieldType::DealStatus,
            ChangeLog::Action::Change
        ));
        this->status       = Status::Other;
        this->other_status = status;
        return true;
    }
    return false;
}

bool Deal::changeDealPriority(const Priority priority, const InternalEmployeePtr& changer)
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
        return true;
    }
    return false;
}

bool Deal::setDrawingDate(const DatePtr& date, const InternalEmployeePtr& changer)
{
    if (this->drawing_date == nullptr || date == nullptr) {
        if (this->drawing_date == date) {
            return false;
        }
    } else if (*this->drawing_date == *date) {
        return false;
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
    return true;
}

bool Deal::setDateApproval(const DatePtr& date, const InternalEmployeePtr& changer)
{
    if (this->date_approval == nullptr || date == nullptr) {
        if (this->date_approval == date) {
            return false;
        }
    } else if (*this->date_approval == *date) {
        return false;
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
    return true;
}

bool Deal::setCreationDate(const Date& date, const InternalEmployeePtr& changer)
{
    if (this->creation_date != date) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_shared<Date>(this->creation_date),
            std::make_shared<Date>(date),
            DealFields::CreationDate,
            ChangeLog::FieldType::Date,
            ChangeLog::FieldType::Date,
            ChangeLog::Action::Change
        ));
        this->creation_date = date;
        return true;
    }
    return false;
}

bool Deal::setOwner(const WeakPersonPtr& owner, const InternalEmployeePtr& changer)
{
    if (this->owner.owner_before(owner) || owner.owner_before(this->owner)) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            WEAK_PTR_TO_OPTIONAL(this->owner),
            WEAK_PTR_TO_OPTIONAL(owner),
            DealFields::Owner,
            !this->owner.expired() ? ChangeLog::FieldType::WeakPerson : ChangeLog::FieldType::null,
            !owner.expired() ? ChangeLog::FieldType::WeakPerson : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->owner = owner;
        return true;
    }
    return false;
}

bool Deal::setManager(const WeakInternalEmployee& manager, const InternalEmployeePtr& changer)
{
    if (this->manager.owner_before(manager) || manager.owner_before(this->manager)) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            WEAK_PTR_TO_OPTIONAL(this->manager),
            WEAK_PTR_TO_OPTIONAL(manager),
            DealFields::DealManager,
            !this->manager.expired() ? ChangeLog::FieldType::WeakInternalEmployee
                                     : ChangeLog::FieldType::null,
            !manager.expired() ? ChangeLog::FieldType::WeakInternalEmployee
                               : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->manager = manager;
        return true;
    }
    return false;
}

bool Deal::addTag(const std::string& tag, const InternalEmployeePtr& changer)
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
        return true;
    }
    return false;
}

bool Deal::delTag(const size_t id, const InternalEmployeePtr& changer)
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
        return true;
    }
    return false;
}

bool Deal::addBuyer(
    const WeakPersonPtr& buyer, const Money& money, const InternalEmployeePtr& changer
)
{
    if (std::find_if(
            this->buyers.begin(),
            this->buyers.end(),
            [&buyer](const WeakBuyerShare& person) {
                return !(buyer.owner_before(person.first) || person.first.owner_before(buyer));
            }
        ) == this->buyers.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(std::make_shared<WeakBuyerShare>(buyer, money)),
            DealFields::Buyers,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::PersonMoneyPair,
            ChangeLog::Action::Add
        ));
        this->buyers.push_back(std::make_pair(buyer, money));
        return true;
    }
    return false;
}

bool Deal::delBuyer(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->buyers.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<WeakBuyerShare>(this->buyers[id])),
            std::nullopt,
            DealFields::Buyers,
            ChangeLog::FieldType::PersonMoneyPair,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->buyers.erase(this->buyers.begin() + id);
        return true;
    }
    return false;
}

bool Deal::updateBuyerMoney(size_t id, const Money& newMoney, const InternalEmployeePtr& changer)
{
    if (this->buyers.size() > id) {
        if (this->buyers[id].second != newMoney) {
            this->change_logs.emplace_back(std::make_shared<ChangeLog>(
                changer,
                std::make_optional(std::make_shared<WeakBuyerShare>(this->buyers[id])),
                std::make_optional(std::make_shared<WeakBuyerShare>(
                    std::make_pair(this->buyers[id].first, newMoney)
                )),
                DealFields::Buyers,
                ChangeLog::FieldType::PersonMoneyPair,
                ChangeLog::FieldType::PersonMoneyPair,
                ChangeLog::Action::Change
            ));
            this->buyers[id].second = newMoney;
            return true;
        }
    }
    return false;
}

bool Deal::addPaymentTransaction(
    const std::shared_ptr<Payment>& payment, const InternalEmployeePtr& changer
)
{
    if (std::find(this->payment_transactions.begin(), this->payment_transactions.end(), payment) ==
        this->payment_transactions.end()) {
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
        return true;
    }
    return false;
}

bool Deal::delPaymentTransaction(size_t id, const InternalEmployeePtr& changer)
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
        return true;
    }
    return false;
}

bool Deal::addAssignedEmployee(
    const WeakInternalEmployee& employee, const InternalEmployeePtr& changer
)
{
    if (std::find_if(
            this->assigned_employees.begin(),
            this->assigned_employees.end(),
            [&employee](const WeakInternalEmployee& other_employee) {
                return !(
                    employee.owner_before(other_employee) || other_employee.owner_before(employee)
                );
            }
        ) == this->assigned_employees.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(employee),
            DealFields::AssignedEmployees,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::WeakInternalEmployee,
            ChangeLog::Action::Add
        ));
        this->assigned_employees.push_back(employee);
        return true;
    }
    return false;
}

bool Deal::delAssignedEmployee(size_t id, const InternalEmployeePtr& changer)
{
    if (this->assigned_employees.size() > id) {
        auto removed = this->assigned_employees[id];
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(removed),
            std::nullopt,
            DealFields::AssignedEmployees,
            ChangeLog::FieldType::WeakInternalEmployee,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->assigned_employees.erase(this->assigned_employees.begin() + id);
        return true;
    }
    return false;
}

bool Deal::addOffer(const OfferDealPtr& offer, const InternalEmployeePtr& changer)
{
    if (std::find(this->offers.begin(), this->offers.end(), offer) == this->offers.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(offer),
            DealFields::Offers,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::OfferDeal,
            ChangeLog::Action::Add
        ));
        this->offers.push_back(offer);
        return true;
    }
    return false;
}

bool Deal::delOffer(size_t index, const InternalEmployeePtr& changer)
{
    if (this->offers.size() > index) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->offers[index]),
            std::nullopt,
            DealFields::Offers,
            ChangeLog::FieldType::OfferDeal,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->offers.erase(this->offers.begin() + index);
        return true;
    }
    return false;
}

bool Deal::addDocument(const DocumentPtr& document, const InternalEmployeePtr& changer)
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
        return true;
    }
    return false;
}

bool Deal::delDocument(size_t id, const InternalEmployeePtr& changer)
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
        return true;
    }
    return false;
}

bool Deal::addTask(const TaskPtr& task, const InternalEmployeePtr& changer)
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
        return true;
    }
    return false;
}

bool Deal::delTask(size_t index, const InternalEmployeePtr& changer)
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
        return true;
    }
    return false;
}

bool Deal::addOffering(const OfferDealPtr& offering, const InternalEmployeePtr& changer)
{
    if (std::find(this->offerings.begin(), this->offerings.end(), offering) ==
        this->offerings.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(offering),
            DealFields::Offerings,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::OfferDeal,
            ChangeLog::Action::Add
        ));
        this->offerings.push_back(offering);
        return true;
    }
    return false;
}

bool Deal::delOffering(size_t index, const InternalEmployeePtr& changer)
{
    if (this->offerings.size() > index) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->offerings[index]),
            std::nullopt,
            DealFields::Offerings,
            ChangeLog::FieldType::OfferDeal,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->offerings.erase(this->offerings.begin() + index);
        return true;
    }
    return false;
}

void Deal::clearAssignedEmployees()
{
    assigned_employees.erase(
        std::remove_if(
            assigned_employees.begin(),
            assigned_employees.end(),
            [](const WeakInternalEmployee& employee) { return employee.expired(); }
        ),
        assigned_employees.end()
    );
}
