#include "task_db.hpp"

#include <algorithm>

#include "Logger/events_log.hpp"
#include "Person/Employee/internal_employee.hpp"

const std::vector<TaskPtr> TaskDataBase::empty_vector;
//

void TaskDataBase::add(const TaskPtr& task)
{
    if (task == nullptr) return;

    if (this->by_id.find(task->getId()) != by_id.end()) return;

    this->by_id[task->getId()] = task;

    std::string title = task->getTitle();
    if (!title.empty()) {
        std::transform(title.begin(), title.end(), title.begin(), ::tolower);
        this->by_title_substr_search.emplace(title, task);
    }

    this->by_status[task->getStatus()].push_back(task);
    this->by_priority[task->getPriority()].push_back(task);

    this->by_created_date.emplace(task->getCreatedDate(), task);
    if (task->getDeadline()) {
        this->by_deadline.emplace(*task->getDeadline(), task);
    }
    if (task->getStartDate()) {
        this->by_start_date.emplace(*task->getStartDate(), task);
    }

    if (!task->getCreatedBy().expired()) {
        this->by_creator[task->getCreatedBy().lock()->getId()].push_back(task);
    }

    if (!task->getManager().expired()) {
        this->by_manager[task->getManager().lock()->getId()].push_back(task);
    }

    for (auto& weak_deal : task->getDeals()) {
        if (!weak_deal.expired()) {
            this->by_deal.emplace(weak_deal.lock()->getId(), task);
        }
    }

    for (auto& week_teem : task->getTeem()) {
        if (!week_teem.expired()) {
            this->by_party[week_teem.lock()->getId()].push_back(task);
        }
    }
}

void TaskDataBase::safe_remove(const BigUint& id, const Date& remove_date)
{
    auto id_it = this->by_id.find(id);
    if (id_it == by_id.end()) {
        return;
    }

    TaskPtr     task = id_it->second;

    std::string title = task->getTitle();
    if (!title.empty()) {
        std::transform(title.begin(), title.end(), title.begin(), ::tolower);
        safeRemoveFromMap(
            this->by_title_substr_search, title, task, __LINE__, "by_title_substr_search"
        );
    }
    safeRemoveFromVector(this->by_status, task->getStatus(), task, __LINE__, "by_status");
    safeRemoveFromVector(this->by_priority, task->getPriority(), task, __LINE__, "by_priority");
    safeRemoveFromMap(
        this->by_created_date, task->getCreatedDate(), task, __LINE__, "by_created_date"
    );
    if (task->getDeadline()) {
        safeRemoveFromMap(this->by_deadline, *task->getDeadline(), task, __LINE__, "by_deadline");
    }
    if (task->getStartDate()) {
        safeRemoveFromMap(
            this->by_start_date, *task->getStartDate(), task, __LINE__, "by_start_date"
        );
    }
    if (!task->getCreatedBy().expired()) {
        auto creator_id = task->getCreatedBy().lock()->getId();
        safeRemoveFromVector(this->by_creator, creator_id, task, __LINE__, "by_creator");
    }
    if (!task->getManager().expired()) {
        auto manager_id = task->getManager().lock()->getId();
        safeRemoveFromVector(this->by_manager, manager_id, task, __LINE__, "by_manager");
    }
    if (!task->getDeals().empty()) {
        for (auto& weak_deal : task->getDeals()) {
            if (!weak_deal.expired()) {
                auto deal = weak_deal.lock();
                safeRemoveFromMap(this->by_deal, deal->getId(), task, __LINE__, "by_deal");
            }
        }
    }
    if (!task->getTeem().empty()) {
        for (auto& weak_teem : task->getTeem()) {
            if (!weak_teem.expired()) {
                auto teem = weak_teem.lock();
                safeRemoveFromVector(this->by_party, teem->getId(), task, __LINE__, "by_teem");
            }
        }
    }

    this->removed.push_back({Date(), task});
    this->by_id.erase(task->getId());
}

void TaskDataBase::hard_remove(const size_t index)
{
    if (index < this->removed.size()) {
        this->removed.erase(this->removed.begin() + index);
    }
}

auto TaskDataBase::getAll() const -> const std::unordered_map<BigUint, TaskPtr>&
{
    return this->by_id;
}

auto TaskDataBase::getByTitle() const -> const std::multimap<std::string, TaskPtr>&
{
    return this->by_title_substr_search;
}

auto TaskDataBase::getByStatus() const
    -> const std::unordered_map<Task::Status, std::vector<TaskPtr>>&
{
    return this->by_status;
}

auto TaskDataBase::getByPriority() const
    -> const std::unordered_map<Priority, std::vector<TaskPtr>>&
{
    return this->by_priority;
}

auto TaskDataBase::getByCreatedDate() const -> const std::multimap<Date, TaskPtr>&
{
    return this->by_created_date;
}

auto TaskDataBase::getByDeadline() const -> const std::multimap<Date, TaskPtr>&
{
    return this->by_deadline;
}

auto TaskDataBase::getByStartDate() const -> const std::multimap<Date, TaskPtr>&
{
    return this->by_start_date;
}

auto TaskDataBase::getByCreator() const -> const std::unordered_map<BigUint, std::vector<TaskPtr>>&
{
    return this->by_creator;
}

auto TaskDataBase::getByManager() const -> const std::unordered_map<BigUint, std::vector<TaskPtr>>&
{
    return this->by_manager;
}

auto TaskDataBase::getByDeal() const -> const std::unordered_multimap<BigUint, TaskPtr>&
{
    return this->by_deal;
}

auto TaskDataBase::getByParty() const -> const std::unordered_map<BigUint, std::vector<TaskPtr>>&
{
    return this->by_party;
}

auto TaskDataBase::getRemoved() const -> const std::vector<std::pair<Date, TaskPtr>>&
{
    return this->removed;
}

auto TaskDataBase::size() const -> size_t { return this->by_id.size(); }

bool TaskDataBase::empty() { return this->by_id.empty(); }

auto TaskDataBase::findById(const BigUint& id) const -> const TaskPtr
{
    auto task = this->by_id.find(id);
    if (task != this->by_id.end()) {
        return task->second;
    }
    return nullptr;
}

auto TaskDataBase::findByTitleSubstr(const std::string& title) const -> const std::vector<TaskPtr>
{
    if (title.empty()) return empty_vector;

    std::string key = title;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    auto first = this->by_title_substr_search.lower_bound(key);
    key.back()++;
    auto second = this->by_title_substr_search.lower_bound(key);

    if (first == second) return empty_vector;

    std::vector<TaskPtr> result;
    for (auto it = first; it != second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto TaskDataBase::findByStatus(const Task::Status status) const -> const std::vector<TaskPtr>&
{
    auto task = this->by_status.find(status);
    if (task != this->by_status.end()) {
        return task->second;
    }
    return empty_vector;
}

auto TaskDataBase::findByPriority(const Priority priority) const -> const std::vector<TaskPtr>&
{
    auto task = this->by_priority.find(priority);
    if (task != this->by_priority.end()) {
        return task->second;
    }
    return empty_vector;
}

auto TaskDataBase::findByCreatedDate(const Date& date) const -> const std::vector<TaskPtr>
{
    auto task_range = this->by_created_date.equal_range(date);
    if (task_range.first == task_range.second) return empty_vector;

    std::vector<TaskPtr> result;
    for (auto it = task_range.first; it != task_range.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto TaskDataBase::findByDeadline(const Date& date) const -> const std::vector<TaskPtr>
{
    auto task_range = this->by_deadline.equal_range(date);
    if (task_range.first == task_range.second) return empty_vector;

    std::vector<TaskPtr> result;
    for (auto it = task_range.first; it != task_range.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto TaskDataBase::findByStartDate(const Date& date) const -> const std::vector<TaskPtr>
{
    auto task_range = this->by_start_date.equal_range(date);
    if (task_range.first == task_range.second) return empty_vector;

    std::vector<TaskPtr> result;
    for (auto it = task_range.first; it != task_range.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto TaskDataBase::findByCreator(const BigUint& id) const -> const std::vector<TaskPtr>&
{
    auto task = this->by_creator.find(id);
    if (task != this->by_creator.end()) {
        return task->second;
    }
    return empty_vector;
}

auto TaskDataBase::findByManager(const BigUint& id) const -> const std::vector<TaskPtr>&
{
    auto task = this->by_manager.find(id);
    if (task != this->by_manager.end()) {
        return task->second;
    }
    return empty_vector;
}

auto TaskDataBase::findByDeal(const BigUint& id) const -> const std::vector<TaskPtr>
{
    auto task_range = this->by_deal.equal_range(id);
    if (task_range.first == task_range.second) return empty_vector;

    std::vector<TaskPtr> result;
    for (auto it = task_range.first; it != task_range.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto TaskDataBase::findByParty(const BigUint& id) const -> const std::vector<TaskPtr>&
{
    auto task = this->by_party.find(id);
    if (task != this->by_party.end()) {
        return task->second;
    }
    return empty_vector;
}

void TaskDataBase::changeTitle(
    const BigUint& id, const std::string& title, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    TaskPtr task = id_it->second;
    if (task->getTitle().empty()) return;

    std::string old_title = task->getTitle();
    if (task->setTitle(title, changer)) {
        std::transform(old_title.begin(), old_title.end(), old_title.begin(), ::tolower);

        safeRemoveFromMap(
            this->by_title_substr_search, old_title, task, __LINE__, "by_title_substr_search"
        );

        std::string new_title = title;
        std::transform(new_title.begin(), new_title.end(), new_title.begin(), ::tolower);
        this->by_title_substr_search.emplace(new_title, task);
    }
}

void TaskDataBase::changeStatus(
    const BigUint& id, const Task::Status status, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    TaskPtr task = id_it->second;

    auto    old_status = task->getStatus();
    if (task->setStatus(status, changer)) {
        safeRemoveFromVector(this->by_status, old_status, task, __LINE__, "by_status");
        this->by_status[status].push_back(task);
    }
}

void TaskDataBase::changePriority(
    const BigUint& id, const Priority priority, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    TaskPtr task = id_it->second;

    auto    old_priority = task->getPriority();
    if (task->setPriority(priority, changer)) {
        safeRemoveFromVector(this->by_priority, old_priority, task, __LINE__, "by_priority");
        this->by_priority[priority].push_back(task);
    }
}

void TaskDataBase::changeDeadline(
    const BigUint& id, const DatePtr& date, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    TaskPtr        task = id_it->second;

    const DatePtr& old_date = task->getDeadline();
    if (task->setDeadline(date, changer)) {
        if (old_date) {
            safeRemoveFromMap(this->by_deadline, *old_date, task, __LINE__, "by_deadline");
        }
        if (date) {
            this->by_deadline.emplace(*date, task);
        }
    }
}

void TaskDataBase::changeStartDate(
    const BigUint& id, const DatePtr& date, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    TaskPtr        task = id_it->second;

    const DatePtr& old_date = task->getStartDate();
    if (task->setStartDate(date, changer)) {
        if (old_date) {
            safeRemoveFromMap(this->by_start_date, *old_date, task, __LINE__, "by_deadline");
        }
        if (date) {
            this->by_start_date.emplace(*date, task);
        }
    }
}

void TaskDataBase::changeManager(
    const BigUint& id, const WeakInternalEmployee& manager, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    TaskPtr     task = id_it->second;

    const auto& old_manager = task->getManager();
    if (task->setManager(manager, changer)) {
        if (!old_manager.expired()) {
            const BigUint& old_id = old_manager.lock()->getId();
            safeRemoveFromVector(this->by_manager, old_id, task, __LINE__, "by_manager");
        }
        if (!manager.expired()) {
            const BigUint& new_id = manager.lock()->getId();
            this->by_manager[new_id].push_back(task);
        }
    }
}

void TaskDataBase::addDeal(
    const BigUint& id, const WeakDealPtr& deal, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    TaskPtr task = id_it->second;
    if (task->addDeal(deal, changer)) {
        this->by_deal.emplace(deal.lock()->getId(), task);
    }
}

void TaskDataBase::delDeal(
    const BigUint& id, const size_t index, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    TaskPtr task = id_it->second;
    if (task->getDeals().size() <= index) return;

    auto old_deal = task->getDeals()[index];

    if (task->delDeal(index, changer)) {
        safeRemoveFromMap(this->by_deal, old_deal.lock()->getId(), task, __LINE__, "by_deal");
    }
}

void TaskDataBase::addParty(
    const BigUint& id, const WeakPersonPtr& person, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    TaskPtr task = id_it->second;
    if (task->addTeemMember(person, changer)) {
        this->by_party[person.lock()->getId()].push_back(task);
    }
}

void TaskDataBase::delParty(const BigUint& id, size_t index, const InternalEmployeePtr& changer)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    TaskPtr task = id_it->second;
    if (task->getTeem().size() <= index) return;

    auto old_party = task->getTeem()[index];

    if (task->delTeemMember(index, changer)) {
        safeRemoveFromVector(this->by_party, old_party.lock()->getId(), task, __LINE__, "by_party");
    }
}

void TaskDataBase::removeCreator(const BigUint& id) { this->by_creator.erase(id); }

void TaskDataBase::removeManager(const BigUint& id) { this->by_manager.erase(id); }

void TaskDataBase::removeParty(const BigUint& id) { this->by_party.erase(id); }

void TaskDataBase::removeDeal(const BigUint& id) { this->by_deal.erase(id); }

void TaskDataBase::safeRemoveFromMap(
    auto&              map,
    const auto&        key,
    const TaskPtr&     task,
    const size_t       line,
    const std::string& index_name
)
{
    auto range = map.equal_range(key);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second == task) {
            map.erase(it);
            return;
        }
    }
    this->logEmptyContainer(__FILE__, line, task->getId().num, index_name);
}

void TaskDataBase::safeRemoveFromVector(
    auto&              map,
    const auto&        key,
    const TaskPtr&     task,
    const size_t       line,
    const std::string& index_name
)
{
    auto& vec = map[key];
    if (vec.empty()) {
        this->logEmptyContainer(__FILE__, line, task->getId().num, index_name);

    } else {
        vec.erase(std::remove(vec.begin(), vec.end(), task), vec.end());
        if (vec.empty()) {
            map.erase(key);
        }
    }
}

void TaskDataBase::logEmptyContainer(
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
        "Data inconsistency in " + index_name + "\nTask: " + employee_id +
            "\nExpected entry is missing."
    );
}