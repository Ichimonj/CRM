#pragma once
#include <map>
#include <unordered_map>

#include "Task/task.hpp"
#include "Usings/type_usings.hpp"

class TaskDataBase {
public:
    void add(const TaskPtr& task);
    void safe_remove(const BigUint& id, const Date& remove_date);
    void hard_remove(const size_t index);

    /// @name Find functions
    /// @{
    auto size() const -> size_t;
    bool empty();
    auto findById(const BigUint& id) const -> const TaskPtr;
    auto findByTitleSubstr(const std::string& title) const -> const std::vector<TaskPtr>;
    auto findByStatus(const Task::Status status) const -> const std::vector<TaskPtr>&;
    auto findByPriority(const Priority priority) const -> const std::vector<TaskPtr>&;
    auto findByCreatedDate(const Date& date) const -> const std::vector<TaskPtr>;
    auto findByDeadline(const Date& date) const -> const std::vector<TaskPtr>;
    auto findByStartDate(const Date& date) const -> const std::vector<TaskPtr>;
    auto findByCreator(const BigUint& id) const -> const std::vector<TaskPtr>&;
    auto findByManager(const BigUint& id) const -> const std::vector<TaskPtr>&;
    auto findByDeal(const BigUint& id) const -> const std::vector<TaskPtr>;
    auto findByParty(const BigUint& id) const -> const std::vector<TaskPtr>&;
    /// @}

    /// @name Change functions
    /// @{
    void changeTitle(
        const BigUint& id, const std::string& title, const InternalEmployeePtr& changer
    );
    void changeStatus(
        const BigUint& id, const Task::Status status, const InternalEmployeePtr& changer
    );
    void changePriority(
        const BigUint& id, const Priority priority, const InternalEmployeePtr& changer
    );
    void changeDeadline(const BigUint& id, const DatePtr& date, const InternalEmployeePtr& changer);
    void changeStartDate(
        const BigUint& id, const DatePtr& date, const InternalEmployeePtr& changer
    );
    void changeManager(
        const BigUint& id, const WeakInternalEmployee& manager, const InternalEmployeePtr& changer
    );
    void addDeal(const BigUint& id, const WeakDealPtr& deal, const InternalEmployeePtr& changer);
    void delDeal(const BigUint& id, const size_t index, const InternalEmployeePtr& changer);

    void addParty(
        const BigUint& id, const WeakPersonPtr& person, const InternalEmployeePtr& changer
    );
    void delParty(const BigUint& id, size_t index, const InternalEmployeePtr& changer);
    /// @}

    /// @name Auxiliary functions
    /// @{
    void removeCreator(const BigUint& id);
    void removeManager(const BigUint& id);
    void removeParty(const BigUint& id);
    /// @}
private:
    std::vector<TaskPtr>                                   empty_vector;

    std::unordered_map<BigUint, TaskPtr>                   by_id;
    std::multimap<std::string, TaskPtr>                    by_title_substr_search;
    std::unordered_map<Task::Status, std::vector<TaskPtr>> by_status;
    std::unordered_map<Priority, std::vector<TaskPtr>>     by_priority;
    std::multimap<Date, TaskPtr>                           by_created_date;
    std::multimap<Date, TaskPtr>                           by_deadline;
    std::multimap<Date, TaskPtr>                           by_start_date;
    std::unordered_map<BigUint, std::vector<TaskPtr>>      by_creator;
    std::unordered_map<BigUint, std::vector<TaskPtr>>      by_manager;
    std::unordered_multimap<BigUint, TaskPtr>              by_deal;
    std::unordered_map<BigUint, std::vector<TaskPtr>>      by_party;

    std::vector<std::pair<Date, TaskPtr>>                  removed;

    void safeRemoveFromMap(
        auto&              map,
        const auto&        key,
        const TaskPtr&     task,
        const size_t       line,
        const std::string& index_name
    );
    void safeRemoveFromVector(
        auto&              map,
        const auto&        key,
        const TaskPtr&     task,
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