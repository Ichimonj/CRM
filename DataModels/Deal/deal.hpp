#pragma once
#include <vector>

#include "BigNum/big_uint.hpp"
#include "BigNum/money.hpp"
#include "Currencies/currencies.hpp"
#include "DateTime/date.hpp"
#include "Document/document.hpp"
#include "Interaction/priority.hpp"
#include "Offering/offer_deal.hpp"
#include "Payment/payment.hpp"
#include "Usings/type_usings.hpp"

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
        const std::vector<PaymentPtr>&                      payment_transactions,
        const Status&                          status,
        const OptionalStr&                     other_status,
        const Priority&                        deal_priority,
        const DatePtr&                         drawing_date,
        const DatePtr&                         date_approval,
        const Date&                            creation_date,
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
    auto getPaymentTransactions() const -> const std::vector<PaymentPtr>&;
    auto getStatus() const -> const Status&;
    auto getOtherStatus() const -> const OptionalStr&;
    auto getDealPriority() const -> const Priority&;
    auto getDrawingDate() const -> const DatePtr&;
    auto getDateApproval() const -> const DatePtr&;
    auto getCreationDate() const -> const Date&;
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
    bool changeContractNumber(const std::string& number, const InternalEmployeePtr& changer);
    bool changeTitle(const std::string& title, const InternalEmployeePtr& changer);
    bool changeDescription(const OptionalStr& description, const InternalEmployeePtr& changer);
    bool changeSource(const OptionalStr& source, const InternalEmployeePtr& changer);
    bool addTag(const std::string& tag, const InternalEmployeePtr& changer);
    bool delTag(const size_t index, const InternalEmployeePtr& changer);
    bool addBuyer(
        const std::shared_ptr<Person>& buyer, const Money& money, const InternalEmployeePtr& changer
    );
    bool delBuyer(const size_t index, const InternalEmployeePtr& changer);
    bool updateBuyerMoney(size_t index, const Money& newMoney, const InternalEmployeePtr& changer);
    bool updateTotalAmount(const Money& amount, const InternalEmployeePtr& changer);
    bool updatePaidAmount(const Money& amount, const InternalEmployeePtr& changer);
    bool addPaymentTransaction(
        const std::shared_ptr<Payment>& payment, const InternalEmployeePtr& changer
    );
    bool delPaymentTransaction(size_t index, const InternalEmployeePtr& changer);
    bool changeStatus(const Status status, const InternalEmployeePtr& changer);
    bool changeOtherStatus(const OptionalStr& status, const InternalEmployeePtr& changer);
    bool changeDealPriority(const Priority priority, const InternalEmployeePtr& changer);
    bool setDrawingDate(const DatePtr& date, const InternalEmployeePtr& changer);
    bool setDateApproval(const DatePtr& date, const InternalEmployeePtr& changer);

    bool addAssignedEmployee(
        const InternalEmployeePtr& employee, const InternalEmployeePtr& changer
    );
    bool delAssignedEmployee(size_t index, const InternalEmployeePtr& changer);

    bool addOffer(const OfferDealPtr& offer, const InternalEmployeePtr& changer);
    bool delOffer(size_t index, const InternalEmployeePtr& changer);

    bool addDocument(const DocumentPtr& document, const InternalEmployeePtr& changer);
    bool delDocument(size_t index, const InternalEmployeePtr& changer);

    bool addTask(const TaskPtr& task, const InternalEmployeePtr& changer);
    bool delTask(size_t index, const InternalEmployeePtr& changer);

    bool setOwner(const std::weak_ptr<Person>& owner, const InternalEmployeePtr& changer);
    bool setDealManager(
        const std::weak_ptr<InternalEmployee>& manager, const InternalEmployeePtr& changer
    );

    bool addOffering(const OfferDealPtr& offering, const InternalEmployeePtr& changer);
    bool delOffering(size_t index, const InternalEmployeePtr& changer);
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
    std::vector<PaymentPtr>                       payment_transactions;
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
