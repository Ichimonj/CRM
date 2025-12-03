#pragma once
#include <memory>

#include "big_uint.hpp"
#include "company.hpp"
#include "currencies.hpp"
#include "date.hpp"
#include "document.hpp"
#include "money.hpp"
#include "person.hpp"

class ChangeLog;
struct Deal;
enum class PaymentStatus {
    pending,    // Ожидает оплаты
    completed,  // Завершён
    failed,     // Неуспешный
    refunded,   // Возвращён
    partial,    // Частично оплачен
    overdue,    // Просрочен
    COUNT
};

using MoneyPtr            = std::shared_ptr<Money>;
using WDealPtr            = std::weak_ptr<Deal>;
using CompanyPtr          = std::shared_ptr<Company>;
using InternalEmployeePtr = std::shared_ptr<InternalEmployee>;
struct Payment {
    Payment(const BigUint& id);
    Payment(
        const BigUint&             id,
        const MoneyPtr&            requested_amount,
        const MoneyPtr&            sending_amount,
        const MoneyPtr&            received_amount,
        const MoneyPtr&            tax_amount,
        const Currencies&          currency,
        const DatePtr&             sending_date,
        const DatePtr&             received_date,
        const DatePtr&             creation_date,
        const PaymentStatus&       status,
        const OptionalStr&         payment_method,
        const WDealPtr&            deal,
        const PersonPtr&           payer,
        const CompanyPtr&          payer_company,
        const OptionalStr&         invoice_number,
        const OptionalStr&         transaction_id,
        const OptionalStr&         payment_purpose,
        const InternalEmployeePtr& created_by,
        std::vector<DocumentPtr>   documents,
        std::vector<std::string>   comments
    );

    /// @name Getters
    /// @{
    auto getId() const -> const BigUint&;
    auto getRequestedAmount() const -> const MoneyPtr&;
    auto getSendingAmount() const -> const MoneyPtr&;
    auto getReceivedAmount() const -> const MoneyPtr&;
    auto getTaxAmount() const -> const MoneyPtr&;
    auto getCurrency() const -> const Currencies&;
    auto getSendingDate() const -> const DatePtr&;
    auto getReceivedDate() const -> const DatePtr&;
    auto getCreationDate() const -> const DatePtr&;
    auto getPaymentStatus() const -> const PaymentStatus;
    auto getPaymentMethod() const -> const OptionalStr&;
    auto getDeal() const -> const WDealPtr&;
    auto getPayer() const -> const PersonPtr&;
    auto getPayerCompany() const -> const CompanyPtr&;
    auto getInvoiceNumber() const -> const OptionalStr&;
    auto getTransactionId() const -> const OptionalStr&;
    auto getDocuments() const -> const std::vector<DocumentPtr>&;
    auto getComments() const -> const std::vector<std::string>&;
    auto getPaymentPurpose() const -> const OptionalStr&;
    auto getCreatedBy() const -> const InternalEmployeePtr&;
    auto getChangeLogs() const -> const std::vector<ChangeLogPtr>&;
    /// @}

    /// @name Change functions
    /// @{
    void setRequestedAmount(const MoneyPtr& requested_amount, const InternalEmployeePtr& changer);
    void setSendingAmount(const MoneyPtr& sending_amount, const InternalEmployeePtr& changer);
    void setReceivedAmount(const MoneyPtr& received_amount, const InternalEmployeePtr& changer);
    void setTaxAmount(const MoneyPtr& tax_amount, const InternalEmployeePtr& changer);
    void setCurrency(const Currencies& currency, const InternalEmployeePtr& changer);
    void setSendingDate(const DatePtr& sending_date, const InternalEmployeePtr& changer);
    void setReceivedDate(const DatePtr& received_date, const InternalEmployeePtr& changer);
    void setCreationDate(const DatePtr& creation_date, const InternalEmployeePtr& changer);
    void setPaymentStatus(const PaymentStatus status, const InternalEmployeePtr& changer);
    void setPaymentMethod(const OptionalStr& payment_method, const InternalEmployeePtr& changer);
    void setDeal(const WDealPtr& deal, const InternalEmployeePtr& changer);
    void setPayer(const PersonPtr& payer, const InternalEmployeePtr& changer);
    void setPayerCompany(const CompanyPtr& payer_company, const InternalEmployeePtr& changer);
    void setInvoiceNumber(const OptionalStr& invoice_number, const InternalEmployeePtr& changer);
    void setTransactionId(const OptionalStr& transaction_id, const InternalEmployeePtr& changer);
    void addDocument(const DocumentPtr& document, const InternalEmployeePtr& changer);
    void delDocument(size_t index, const InternalEmployeePtr& changer);
    void addComment(const std::string& comment, const InternalEmployeePtr& changer);
    void delComment(size_t index, const InternalEmployeePtr& changer);
    void setPaymentPurpose(const OptionalStr& payment_purpose, const InternalEmployeePtr& changer);
    void setCreatedBy(const InternalEmployeePtr& created_by, const InternalEmployeePtr& changer);
    /// @}

private:
    BigUint       id;

    MoneyPtr      requested_amount;
    MoneyPtr      sending_amount;
    MoneyPtr      received_amount;
    MoneyPtr      tax_amount;
    Currencies    currency;

    DatePtr       sending_date;
    DatePtr       received_date;
    DatePtr       creation_date;

    PaymentStatus status;

    OptionalStr   payment_method;

    WDealPtr      deal;

    PersonPtr     payer;

    CompanyPtr    payer_company;

    OptionalStr   invoice_number;
    OptionalStr   transaction_id;
    OptionalStr   payment_purpose;
    //
    std::vector<DocumentPtr>  documents;
    std::vector<std::string>  comments;
    InternalEmployeePtr       created_by;
    std::vector<ChangeLogPtr> change_logs;
};