#pragma once
#pragma once
#include <map>
#include <unordered_map>

#include "Deal/deal.hpp"
#include "Usings/type_usings.hpp"

class DealDataBase {
public:
    void add(const DealPtr& deal);
    void soft_remove(const BigUint& id);
    void hard_remove(const size_t index);
    /// @name Get functions
    /// @{
    auto getAll() const -> const std::unordered_map<BigUint, DealPtr>&;
    auto getByManager() const -> const std::unordered_map<BigUint, std::vector<DealPtr>>&;
    auto getByOwner() const -> const std::unordered_map<BigUint, std::vector<DealPtr>>&;
    auto getByTotalAmount() const -> const std::multimap<Money, DealPtr>&;
    auto getByPaidAmount() const -> const std::multimap<Money, DealPtr>&;
    auto getByStatus() const -> const std::unordered_map<Deal::Status, std::vector<DealPtr>>&;
    auto getByPriority() const -> const std::unordered_map<Priority, std::vector<DealPtr>>&;
    auto getByCreationDate() const -> const std::multimap<Date, DealPtr>&;
    auto getByDrawingDate() const -> const std::multimap<Date, DealPtr>&;
    auto getByApprovalDate() const -> const std::multimap<Date, DealPtr>&;
    auto getByContractNumber() const -> const std::unordered_map<std::string, DealPtr>&;
    auto getByTitleSubstr() const -> const std::multimap<std::string, DealPtr>&;
    /// @}

    /// @name Find functions
    /// @{
    auto findById(const BigUint& id) const -> const DealPtr;
    auto findByManager(const BigUint& manager_id) const -> const std::vector<DealPtr>&;
    auto findByOwner(const BigUint& owner_id) const -> const std::vector<DealPtr>&;

    auto findByTotalAmount(const Money& amount) const -> std::vector<DealPtr>;
    auto findByPaidAmount(const Money& amount) const -> std::vector<DealPtr>;

    auto findByStatus(Deal::Status status) const -> const std::vector<DealPtr>&;
    auto findByPriority(Priority priority) const -> const std::vector<DealPtr>&;

    auto findByCreationDate(const Date& date) const -> std::vector<DealPtr>;
    auto findByDrawingDate(const Date& date) const -> std::vector<DealPtr>;
    auto findByApprovalDate(const Date& date) const -> std::vector<DealPtr>;

    auto findByContractNumber(const std::string& contract_number) const -> const DealPtr;
    auto findByTitleSubstr(const std::string& substr) const -> std::vector<DealPtr>;
    /// @}

    /// @name Change functions
    /// @{
    auto changeManager(
        const BigUint& id, const WeakInternalEmployee& manager, const InternalEmployeePtr& changer
    );
    auto changeOwner(
        const BigUint& id, const WeakPersonPtr& owner, const InternalEmployeePtr& changer
    );
    auto changeTotalAmount(
        const BigUint& id, const Money& total_amount, const InternalEmployeePtr& changer
    );
    auto changePaidAmount(
        const BigUint& id, const Money& paid_amount, const InternalEmployeePtr& changer
    );
    auto changeStatus(
        const BigUint& id, const Deal::Status status, const InternalEmployeePtr& changer
    );
    auto changeOtherStatus(
        const BigUint& id, const OptionalStr& status, const InternalEmployeePtr& changer
    );
    auto changePriority(
        const BigUint& id, const Priority priority, const InternalEmployeePtr& changer
    );
    auto changeCreationDate(
        const BigUint& id, const Date& date, const InternalEmployeePtr& changer
    );
    auto changeDrawingDate(
        const BigUint& id, const DatePtr& date, const InternalEmployeePtr& changer
    );
    auto changeApprovalDate(
        const BigUint& id, const DatePtr& date, const InternalEmployeePtr& changer
    );
    auto changeContractNumber(
        const BigUint& id, const std::string& number, const InternalEmployeePtr& changer
    );
    auto changeTitle(
        const BigUint& id, const std::string& title, const InternalEmployeePtr& changer
    );
    /// @}

    /// @name Auxiliary functions
    /// @{
    void removeInternalEmployee(const BigUint& id);
    /// @}

private:
    static const std::vector<DealPtr>                 empty_vector;

    std::unordered_map<BigUint, DealPtr>              by_id;
    std::unordered_map<BigUint, std::vector<DealPtr>> by_manager;
    std::unordered_map<BigUint, std::vector<DealPtr>> by_owner;

    //
    std::multimap<Money, DealPtr> by_total_amount;
    std::multimap<Money, DealPtr> by_paid_amount;

    //
    std::unordered_map<Deal::Status, std::vector<DealPtr>> by_status;
    std::unordered_map<std::string, std::vector<DealPtr>>  by_other_status;
    std::unordered_map<Priority, std::vector<DealPtr>>     by_priority;

    //
    std::multimap<Date, DealPtr> by_creation_date;
    std::multimap<Date, DealPtr> by_drawing_date;
    std::multimap<Date, DealPtr> by_approval_date;

    //
    std::unordered_map<std::string, DealPtr> by_contract_number;
    std::multimap<std::string, DealPtr>      by_title_substr_search;
    std::vector<std::pair<Date, DealPtr>>    removed;
    //
    void safeRemoveFromMap(
        auto&              map,
        const auto&        key,
        const DealPtr&     deal,
        const size_t       line,
        const std::string& index_name
    );
    void safeRemoveFromVector(
        auto&              map,
        const auto&        key,
        const DealPtr&     deal,
        const size_t       line,
        const std::string& index_name
    );

    void logEmptyContainer(
        const std::string& file,
        const size_t       line,
        const std::string& employee_id,
        const std::string& index_name
    );
};