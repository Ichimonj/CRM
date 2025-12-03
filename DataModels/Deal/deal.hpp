#pragma once
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "big_uint.hpp"
#include "currencies.hpp"
#include "date.hpp"
#include "document.hpp"
#include "money.hpp"
#include "offer_deal.hpp"
#include "payment.hpp"
#include "priority.hpp"

class ChangeLog;
class Task;
class Client;
class InternalEmployee;
class Person;

using BuyerShare          = std::pair<std::shared_ptr<Person>, Money>;
using PaymentArr          = std::vector<std::shared_ptr<Payment>>;
using DatePtr             = std::shared_ptr<Date>;
using InternalEmployeePtr = std::shared_ptr<InternalEmployee>;
using OfferDealPtr        = std::shared_ptr<OfferDeal>;
using DocumentPtr         = std::shared_ptr<Document>;
using ChangeLogPtr        = std::shared_ptr<ChangeLog>;
using TaskPtr             = std::shared_ptr<Task>;

struct Deal {
    enum class Status : uint8_t {
        Draft,
        ReadyForCoordination,
        ReadyForSigned,
        Coordination,
        SignedByCounterparty,
        SignedBySecondSide,
        AllSigned,
        Deleted,
        Canceled,
        Registered,
        BeginningDealBroken,
        EndDealBroken,
        ObligationsAreProcess,
        ObligationsAreFulfilled,
        ObligationsAreNotFulfilled,
        Other,
        COUNT
    };

    Deal(const BigUint& id);

    Deal(
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
        std::vector<OfferDealPtr>              offers,
        std::vector<DocumentPtr>               documents,
        std::vector<TaskPtr>                   tasks,
        const std::weak_ptr<Person>&           owner,
        const std::weak_ptr<InternalEmployee>& deal_manager,
        std::vector<OfferDealPtr>              offerings
    );

    /// @name Getters
    /// @{
    auto getId() const -> const BigUint&;
    auto getContractNumber() const -> const std::string&;
    auto getTitle() const -> const std::string&;
    auto getDescription() const -> const OptionalStr&;
    auto getSource() const -> const OptionalStr&;
    auto getTags() const -> const std::vector<std::string>&;
    auto getBuyers() const -> const std::vector<BuyerShare>&;
    auto getTotalAmount() const -> const Money&;
    auto getPaidAmount() const -> const Money&;
    auto getCurrency() const -> const std::optional<Currencies>&;
    auto getOtherCurrency() const -> const OptionalStr&;
    auto getPaymentTransactions() const -> const PaymentArr&;
    auto getStatus() const -> const Status&;
    auto getOtherStatus() const -> const OptionalStr&;
    auto getDealPriority() const -> const Priority&;
    auto getDrawingDate() const -> const DatePtr&;
    auto getDateApproval() const -> const DatePtr&;
    auto getCreationDate() const -> const Date&;
    auto getManager() const -> const InternalEmployeePtr&;
    auto getAssignedEmployees() const -> const std::vector<InternalEmployeePtr>&;
    auto getOffers() const -> const std::vector<OfferDealPtr>&;
    auto getDocuments() const -> const std::vector<DocumentPtr>&;
    auto getTasks() const -> const std::vector<TaskPtr>&;
    auto getOwner() const -> const std::weak_ptr<Person>&;
    auto getDealManager() const -> const std::weak_ptr<InternalEmployee>&;
    auto getOfferings() const -> const std::vector<OfferDealPtr>&;
    auto getChangeLogs() const -> const std::vector<ChangeLogPtr>&;
    /// @}

    /// @name Change functions
    /// @{
    void changeContractNumber(const std::string& number, const InternalEmployeePtr& changer);
    void changeTitle(const std::string& title, const InternalEmployeePtr& changer);
    void changeDescription(const OptionalStr& description, const InternalEmployeePtr& changer);
    void changeSource(const OptionalStr& source, const InternalEmployeePtr& changer);
    void addTag(const std::string& tag, const InternalEmployeePtr& changer);
    void delTag(const size_t index, const InternalEmployeePtr& changer);
    void addBuyer(
        const std::shared_ptr<Person>& buyer, const Money& money, const InternalEmployeePtr& changer
    );
    void delBuyer(const size_t index, const InternalEmployeePtr& changer);
    void updateBuyerMoney(size_t index, const Money& newMoney, const InternalEmployeePtr& changer);
    void updateTotalAmount(const Money& amount, const InternalEmployeePtr& changer);
    void updatePaidAmount(const Money& amount, const InternalEmployeePtr& changer);
    void changeCurrency(
        const std::optional<Currencies>& currency, const InternalEmployeePtr& changer
    );
    void changeOtherCurrency(const OptionalStr& currency, const InternalEmployeePtr& changer);
    void addPaymentTransaction(
        const std::shared_ptr<Payment>& payment, const InternalEmployeePtr& changer
    );
    void delPaymentTransaction(size_t index, const InternalEmployeePtr& changer);
    void changeStatus(const Status status, const InternalEmployeePtr& changer);
    void changeOtherStatus(const OptionalStr& status, const InternalEmployeePtr& changer);
    void changeDealPriority(const Priority priority, const InternalEmployeePtr& changer);
    void setDrawingDate(const DatePtr& date, const InternalEmployeePtr& changer);
    void setDateApproval(const DatePtr& date, const InternalEmployeePtr& changer);
    void changeManager(const InternalEmployeePtr& manager, const InternalEmployeePtr& changer);

    void addAssignedEmployee(
        const InternalEmployeePtr& employee, const InternalEmployeePtr& changer
    );
    void delAssignedEmployee(size_t index, const InternalEmployeePtr& changer);

    void addOffer(const OfferDealPtr& offer, const InternalEmployeePtr& changer);
    void delOffer(size_t index, const InternalEmployeePtr& changer);

    void addDocument(const DocumentPtr& document, const InternalEmployeePtr& changer);
    void delDocument(size_t index, const InternalEmployeePtr& changer);

    void addTask(const TaskPtr& task, const InternalEmployeePtr& changer);
    void delTask(size_t index, const InternalEmployeePtr& changer);

    void setOwner(const std::weak_ptr<Person>& owner, const InternalEmployeePtr& changer);
    void setDealManager(
        const std::weak_ptr<InternalEmployee>& manager, const InternalEmployeePtr& changer
    );

    void addOffering(const OfferDealPtr& offering, const InternalEmployeePtr& changer);
    void delOffering(size_t index, const InternalEmployeePtr& changer);
    /// @}

private:
    BigUint                          id;
    std::string                      contract_number;
    std::string                      title;
    OptionalStr                      description;
    OptionalStr                      source;
    std::vector<std::string>         tags;
    std::vector<BuyerShare>          buyers;
    Money                            total_amount = Money("");
    Money                            paid_amount  = Money("");
    std::optional<Currencies>        currency     = std::nullopt;
    OptionalStr                      other_currency;
    PaymentArr                       payment_transactions;
    Status                           status = Status::Draft;
    OptionalStr                      other_status;
    Priority                         deal_priority = Priority::Medium;
    DatePtr                          drawing_date;
    DatePtr                          date_approval;
    Date                             creation_date = Date();
    InternalEmployeePtr              manager;
    std::vector<InternalEmployeePtr> assigned_employees;
    std::vector<OfferDealPtr>        offers;  // Merged (purchased + considered)
    std::vector<DocumentPtr>         documents;
    std::vector<TaskPtr>             tasks;

    std::weak_ptr<Person> owner;  // Person (Client/Employee) or CompanyPtr if company-level
    std::weak_ptr<InternalEmployee> deal_manager;  // Manager for accountability
    std::vector<OfferDealPtr>       offerings;     // Internal offers in this deal

    std::vector<ChangeLogPtr>       change_logs = {};
};
