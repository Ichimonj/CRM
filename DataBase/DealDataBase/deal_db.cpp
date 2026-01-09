#include "deal_db.hpp"

#include <algorithm>

#include "Logger/events_log.hpp"
#include "Person/Employee/internal_employee.hpp"

const std::vector<DealPtr> DealDataBase::empty_vector;

void                       DealDataBase::add(const DealPtr& deal)
{
    if (deal == nullptr) return;

    if (this->by_id.find(deal->getId()) != this->by_id.end()) {
        return;
    }

    this->by_id[deal->getId()] = deal;

    auto deal_manager = deal->getManager().lock();
    if (deal_manager) {
        this->by_manager[deal_manager->getId()].push_back(deal);
    }

    auto owner = deal->getOwner().lock();
    if (owner) {
        this->by_owner[owner->getId()].push_back(deal);
    }

    this->by_total_amount.emplace(deal->getTotalAmount(), deal);
    this->by_paid_amount.emplace(deal->getPaidAmount(), deal);

    if (deal->getStatus() != Deal::Status::Other) {
        this->by_status[deal->getStatus()].push_back(deal);
    } else if (deal->getOtherStatus().has_value()) {
        this->by_other_status[deal->getOtherStatus().value()].push_back(deal);
    }
    if (deal->getDealPriority() != Priority::null) {
        this->by_priority[deal->getDealPriority()].push_back(deal);
    }

    this->by_creation_date.emplace(deal->getCreationDate(), deal);

    if (deal->getDrawingDate()) {
        this->by_drawing_date.emplace(*deal->getDrawingDate(), deal);
    }
    if (deal->getDateApproval()) {
        this->by_approval_date.emplace(*deal->getDateApproval(), deal);
    }

    this->by_contract_number.emplace(deal->getContractNumber(), deal);

    if (!deal->getTitle().empty()) {
        std::string lower_title = deal->getTitle();
        std::transform(lower_title.begin(), lower_title.end(), lower_title.begin(), ::tolower);
        this->by_title_substr_search.emplace(lower_title, deal);
    }
}

void DealDataBase::soft_remove(const BigUint& id)
{
    auto deal_it = by_id.find(id);
    if (deal_it == by_id.end()) {
        return;
    }

    DealPtr deal = deal_it->second;

    auto    deal_manager = deal->getManager().lock();
    if (deal_manager) {
        auto manager_id = deal_manager->getId();
        safeRemoveFromVector(by_manager, manager_id, deal, __LINE__, "by_manager");
    }

    auto owner = deal->getOwner().lock();
    if (owner) {
        auto owner_id = owner->getId();
        safeRemoveFromVector(by_owner, owner_id, deal, __LINE__, "by_owner");
    }

    safeRemoveFromMap(by_total_amount, deal->getTotalAmount(), deal, __LINE__, "by_total_amount");
    safeRemoveFromMap(by_paid_amount, deal->getPaidAmount(), deal, __LINE__, "by_paid_amount");

    if (deal->getStatus() != Deal::Status::Other) {
        safeRemoveFromVector(by_status, deal->getStatus(), deal, __LINE__, "by_status");
    } else if (deal->getOtherStatus().has_value()) {
        safeRemoveFromVector(
            by_other_status, deal->getOtherStatus().value(), deal, __LINE__, "by_status"
        );
    }
    if (deal->getDealPriority() != Priority::null) {
        safeRemoveFromVector(by_priority, deal->getDealPriority(), deal, __LINE__, "by_priority");
    }

    safeRemoveFromMap(
        by_creation_date, deal->getCreationDate(), deal, __LINE__, "by_creation_date"
    );
    if (deal->getDrawingDate()) {
        auto drawing_date = deal->getDrawingDate();
        safeRemoveFromMap(by_drawing_date, *drawing_date, deal, __LINE__, "by_drawing_date");
    }
    if (deal->getDateApproval()) {
        auto approval_date = deal->getDateApproval();
        safeRemoveFromMap(by_approval_date, *approval_date, deal, __LINE__, "by_approval_date");
    }

    safeRemoveFromMap(
        by_contract_number, deal->getContractNumber(), deal, __LINE__, "by_contract_number"
    );

    if (!deal->getTitle().empty()) {
        std::string lower_title = deal->getTitle();
        std::transform(lower_title.begin(), lower_title.end(), lower_title.begin(), ::tolower);
        safeRemoveFromMap(by_title_substr_search, lower_title, deal, __LINE__, "by_title_substr");
    }

    this->removed.push_back({Date(), deal});
    this->by_id.erase(deal->getId());
}

void DealDataBase::hard_remove(const size_t index)
{
    if (index < this->removed.size()) {
        this->removed.erase(this->removed.begin() + index);
    }
}

auto DealDataBase::getAll() const -> const std::unordered_map<BigUint, DealPtr>&
{
    return this->by_id;
}

auto DealDataBase::getByManager() const -> const std::unordered_map<BigUint, std::vector<DealPtr>>&
{
    return this->by_manager;
}

auto DealDataBase::getByOwner() const -> const std::unordered_map<BigUint, std::vector<DealPtr>>&
{
    return this->by_manager;
}

auto DealDataBase::getByTotalAmount() const -> const std::multimap<Money, DealPtr>&
{
    return this->by_total_amount;
}

auto DealDataBase::getByPaidAmount() const -> const std::multimap<Money, DealPtr>&
{
    return this->by_paid_amount;
}

auto DealDataBase::getByStatus() const
    -> const std::unordered_map<Deal::Status, std::vector<DealPtr>>&
{
    return this->by_status;
}

auto DealDataBase::getByPriority() const
    -> const std::unordered_map<Priority, std::vector<DealPtr>>&
{
    return this->by_priority;
}

auto DealDataBase::getByCreationDate() const -> const std::multimap<Date, DealPtr>&
{
    return this->by_creation_date;
}

auto DealDataBase::getByDrawingDate() const -> const std::multimap<Date, DealPtr>&
{
    return this->by_drawing_date;
}

auto DealDataBase::getByApprovalDate() const -> const std::multimap<Date, DealPtr>&
{
    return this->by_approval_date;
}

auto DealDataBase::getByContractNumber() const -> const std::unordered_map<std::string, DealPtr>&
{
    return this->by_contract_number;
}

auto DealDataBase::getByTitleSubstr() const -> const std::multimap<std::string, DealPtr>&
{
    return this->by_title_substr_search;
}

auto DealDataBase::findById(const BigUint& id) const -> const DealPtr
{
    auto deal = this->by_id.find(id);
    if (deal != this->by_id.end()) {
        return deal->second;
    }
    return nullptr;
}

auto DealDataBase::findByManager(const BigUint& manager_id) const -> const std::vector<DealPtr>&
{
    auto deals_it = this->by_manager.find(manager_id);
    if (deals_it != this->by_manager.end()) {
        return deals_it->second;
    }
    return empty_vector;
}

auto DealDataBase::findByOwner(const BigUint& owner_id) const -> const std::vector<DealPtr>&
{
    auto deals_it = this->by_owner.find(owner_id);
    if (deals_it != this->by_owner.end()) {
        return deals_it->second;
    }
    return empty_vector;
}

auto DealDataBase::findByTotalAmount(const Money& amount) const -> std::vector<DealPtr>
{
    auto deals = this->by_total_amount.equal_range(amount);
    if (deals.first == deals.second) return empty_vector;

    std::vector<DealPtr> result;
    for (auto it = deals.first; it != deals.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto DealDataBase::findByPaidAmount(const Money& amount) const -> std::vector<DealPtr>
{
    auto deals = this->by_paid_amount.equal_range(amount);
    if (deals.first == deals.second) return empty_vector;

    std::vector<DealPtr> result;
    for (auto it = deals.first; it != deals.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto DealDataBase::findByStatus(Deal::Status status) const -> const std::vector<DealPtr>&
{
    auto deals_it = this->by_status.find(status);
    if (deals_it != this->by_status.end()) {
        return deals_it->second;
    }
    return empty_vector;
}

auto DealDataBase::findByPriority(Priority priority) const -> const std::vector<DealPtr>&
{
    auto deals_it = this->by_priority.find(priority);
    if (deals_it != this->by_priority.end()) {
        return deals_it->second;
    }
    return empty_vector;
}

auto DealDataBase::findByCreationDate(const Date& date) const -> std::vector<DealPtr>
{
    auto deals = this->by_creation_date.equal_range(date);
    if (deals.first == deals.second) return empty_vector;

    std::vector<DealPtr> result;
    for (auto it = deals.first; it != deals.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto DealDataBase::findByDrawingDate(const Date& date) const -> std::vector<DealPtr>
{
    auto deals = this->by_drawing_date.equal_range(date);
    if (deals.first == deals.second) return empty_vector;

    std::vector<DealPtr> result;
    for (auto it = deals.first; it != deals.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto DealDataBase::findByApprovalDate(const Date& date) const -> std::vector<DealPtr>
{
    auto deals = this->by_approval_date.equal_range(date);
    if (deals.first == deals.second) return empty_vector;

    std::vector<DealPtr> result;
    for (auto it = deals.first; it != deals.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto DealDataBase::findByContractNumber(const std::string& contract_number) const -> const DealPtr
{
    auto deal = this->by_contract_number.find(contract_number);
    if (deal != this->by_contract_number.end()) {
        return deal->second;
    }
    return nullptr;
}

auto DealDataBase::findByTitleSubstr(const std::string& substr) const -> std::vector<DealPtr>
{
    if (substr.empty()) return empty_vector;

    auto key = substr;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    auto first = this->by_title_substr_search.lower_bound(key);
    key.back()++;
    auto second = this->by_title_substr_search.lower_bound(key);

    if (first == second) return empty_vector;
    std::vector<DealPtr> result;
    for (auto it = first; it != second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto DealDataBase::changeManager(
    const BigUint& id, const WeakInternalEmployee& manager, const InternalEmployeePtr& changer
)
{
    auto deal_it = this->by_id.find(id);
    if (deal_it == this->by_id.end()) return;

    DealPtr deal = deal_it->second;

    auto    old_manager = deal->getManager().lock();
    auto    new_manager = manager.lock();
    if (deal->setManager(manager, changer)) {
        if (old_manager) {
            auto old_manager_id = old_manager->getId();
            safeRemoveFromVector(this->by_manager, old_manager_id, deal, __LINE__, "by_manager");
        }
        if (new_manager) {
            auto new_manager_id = new_manager->getId();
            this->by_manager[new_manager_id].push_back(deal);
        }
    }
}

auto DealDataBase::changeOwner(
    const BigUint& id, const WeakPersonPtr& owner, const InternalEmployeePtr& changer
)
{
    auto deal_it = this->by_id.find(id);
    if (deal_it == this->by_id.end()) return;

    DealPtr deal = deal_it->second;

    auto    old_owner = deal->getOwner().lock();
    auto    new_owner = owner.lock();
    if (deal->setOwner(owner, changer)) {
        if (old_owner) {
            auto old_owner_id = old_owner->getId();
            safeRemoveFromVector(this->by_owner, old_owner_id, deal, __LINE__, "by_owner");
        }
        if (new_owner) {
            this->by_owner[new_owner->getId()].push_back(deal);
        }
    }
}

auto DealDataBase::changeTotalAmount(
    const BigUint& id, const Money& total_amount, const InternalEmployeePtr& changer
)
{
    auto deal_it = this->by_id.find(id);
    if (deal_it == this->by_id.end()) return;

    DealPtr deal = deal_it->second;

    auto    old_amount = deal->getTotalAmount();

    if (deal->changeTotalAmount(total_amount, changer)) {
        safeRemoveFromMap(this->by_total_amount, old_amount, deal, __LINE__, "by_total_amount");
        this->by_total_amount.emplace(total_amount, deal);
    }
}

auto DealDataBase::changePaidAmount(
    const BigUint& id, const Money& paid_amount, const InternalEmployeePtr& changer
)
{
    auto deal_it = this->by_id.find(id);
    if (deal_it == this->by_id.end()) return;

    DealPtr deal = deal_it->second;

    auto    old_amount = deal->getPaidAmount();

    if (deal->changePaidAmount(paid_amount, changer)) {
        safeRemoveFromMap(this->by_paid_amount, old_amount, deal, __LINE__, "by_paid_amount");
        this->by_paid_amount.emplace(paid_amount, deal);
    }
}

auto DealDataBase::changeStatus(
    const BigUint& id, const Deal::Status status, const InternalEmployeePtr& changer
)
{
    auto deal_it = this->by_id.find(id);
    if (deal_it == this->by_id.end()) return;

    DealPtr      deal = deal_it->second;

    Deal::Status old_status = deal->getStatus();

    if (deal->changeStatus(status, changer)) {
        if (deal->getStatus() != Deal::Status::Other) {
            safeRemoveFromVector(this->by_status, old_status, deal, __LINE__, "by_status");
        } else if (deal->getOtherStatus().has_value()) {
            safeRemoveFromVector(
                this->by_other_status,
                deal->getOtherStatus().value(),
                deal,
                __LINE__,
                "by_other_status"
            );
        }
        if (status != Deal::Status::Other) {
            this->by_status[status].push_back(deal);
        }
    }
}

auto DealDataBase::changeOtherStatus(
    const BigUint& id, const OptionalStr& status, const InternalEmployeePtr& changer
)
{
    auto deal_it = this->by_id.find(id);
    if (deal_it == this->by_id.end()) return;

    DealPtr     deal = deal_it->second;

    OptionalStr old_status = deal->getOtherStatus();

    if (deal->changeOtherStatus(status, changer)) {
        if (old_status.has_value()) {
            safeRemoveFromVector(
                this->by_other_status, old_status.value(), deal, __LINE__, "by_other_status"
            );
        } else if (deal->getStatus() != Deal::Status::Other) {
            safeRemoveFromVector(this->by_status, deal->getStatus(), deal, __LINE__, "by_status");
        }
        if (status.has_value()) {
            this->by_other_status[status.value()].push_back(deal);
        }
    }
}

auto DealDataBase::changePriority(
    const BigUint& id, const Priority priority, const InternalEmployeePtr& changer
)
{
    auto deal_it = this->by_id.find(id);
    if (deal_it == this->by_id.end()) return;

    DealPtr deal = deal_it->second;

    auto    old_priority = deal->getDealPriority();

    if (deal->changeDealPriority(priority, changer)) {
        if (old_priority != Priority::null) {
            safeRemoveFromVector(this->by_priority, old_priority, deal, __LINE__, "by_priority");
        } else if (priority != Priority::null) {
            this->by_priority[priority].push_back(deal);
        }
    }
}

auto DealDataBase::changeCreationDate(
    const BigUint& id, const Date& date, const InternalEmployeePtr& changer
)
{
    auto deal_it = this->by_id.find(id);
    if (deal_it == this->by_id.end()) return;

    DealPtr deal = deal_it->second;

    auto    old_date = deal->getCreationDate();

    if (deal->setCreationDate(date, changer)) {
        safeRemoveFromMap(this->by_creation_date, old_date, deal, __LINE__, "by_creation_date");
        this->by_creation_date.emplace(date, deal);
    }
}

auto DealDataBase::changeDrawingDate(
    const BigUint& id, const DatePtr& date, const InternalEmployeePtr& changer
)
{
    auto deal_it = this->by_id.find(id);
    if (deal_it == this->by_id.end()) return;

    DealPtr deal = deal_it->second;

    auto    old_date = deal->getDrawingDate();

    if (deal->setDrawingDate(date, changer)) {
        if (old_date) {
            safeRemoveFromMap(this->by_drawing_date, *old_date, deal, __LINE__, "by_drawing_date");
        }
        if (date) {
            this->by_drawing_date.emplace(*date, deal);
        }
    }
}

auto DealDataBase::changeApprovalDate(
    const BigUint& id, const DatePtr& date, const InternalEmployeePtr& changer
)
{
    auto deal_it = this->by_id.find(id);
    if (deal_it == this->by_id.end()) return;

    DealPtr deal = deal_it->second;

    auto    old_date = deal->getDateApproval();

    if (deal->setDateApproval(date, changer)) {
        if (old_date) {
            safeRemoveFromMap(this->by_approval_date, *old_date, deal, __LINE__, "by_drawing_date");
        }
        if (date) {
            this->by_approval_date.emplace(*date, deal);
        }
    }
}

auto DealDataBase::changeContractNumber(
    const BigUint& id, const std::string& number, const InternalEmployeePtr& changer
)
{
    auto deal_it = this->by_id.find(id);
    if (deal_it == this->by_id.end()) return;

    DealPtr     deal = deal_it->second;

    std::string old_number = deal->getContractNumber();

    if (deal->changeContractNumber(number, changer)) {
        safeRemoveFromMap(
            this->by_contract_number, old_number, deal, __LINE__, "by_contract_number"
        );
        this->by_contract_number.emplace(number, deal);
    }
}

auto DealDataBase::changeTitle(
    const BigUint& id, const std::string& title, const InternalEmployeePtr& changer
)
{
    auto deal_it = this->by_id.find(id);
    if (deal_it == this->by_id.end()) return;

    DealPtr     deal = deal_it->second;

    std::string old_title = deal->getTitle();

    if (deal->changeTitle(title, changer)) {
        if (!old_title.empty()) {
            auto old_key = old_title;
            std::transform(old_key.begin(), old_key.end(), old_key.begin(), ::tolower);
            safeRemoveFromMap(
                this->by_title_substr_search, old_key, deal, __LINE__, "by_title_substr_search"
            );
        }
        if (!title.empty()) {
            auto new_key = title;
            std::transform(new_key.begin(), new_key.end(), new_key.begin(), ::tolower);
            this->by_title_substr_search.emplace(new_key, deal);
        }
    }
}

void DealDataBase::removeInternalEmployee(const BigUint& id)
{
    this->by_owner.erase(id);
    this->by_manager.erase(id);
}

void DealDataBase::safeRemoveFromMap(
    auto&              map,
    const auto&        key,
    const DealPtr&     deal,
    const size_t       line,
    const std::string& index_name
)
{
    auto range = map.equal_range(key);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second == deal) {
            map.erase(it);
            return;
        }
    }
    this->logEmptyContainer(__FILE__, line, deal->getId().num, index_name);
}

void DealDataBase::safeRemoveFromVector(
    auto&              map,
    const auto&        key,
    const DealPtr&     deal,
    const size_t       line,
    const std::string& index_name
)
{
    auto& vec = map[key];
    if (vec.empty()) {
        this->logEmptyContainer(__FILE__, line, deal->getId().num, index_name);

    } else {
        vec.erase(std::remove(vec.begin(), vec.end(), deal), vec.end());
        if (vec.empty()) {
            map.erase(key);
        }
    }
}

void DealDataBase::logEmptyContainer(
    const std::string& file,
    const size_t       line,
    const std::string& employee_id,
    const std::string& index_name
)
{
    EventLog::getInstance().log(
        LOG_LEVEL::ERROR,
        file,
        line,
        "Data inconsistency in " + index_name + "\nDeal: " + employee_id +
            "\nExpected entry is missing."
    );
}