#pragma once
#include <memory>

#include "BigNum/big_uint.hpp"
#include "Company/company.hpp"
#include "Currencies/currencies.hpp"
#include "DateTime/date.hpp"
#include "Document/document.hpp"
#include "BigNum/money.hpp"
#include "Person/person.hpp"

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
    auto getPaymentStatus() const -> PaymentStatus;
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
    bool setRequestedAmount(const MoneyPtr& requested_amount, const InternalEmployeePtr& changer);
    bool setSendingAmount(const MoneyPtr& sending_amount, const InternalEmployeePtr& changer);
    bool setReceivedAmount(const MoneyPtr& received_amount, const InternalEmployeePtr& changer);
    bool setTaxAmount(const MoneyPtr& tax_amount, const InternalEmployeePtr& changer);
    bool setCurrency(const Currencies& currency, const InternalEmployeePtr& changer);
    bool setSendingDate(const DatePtr& sending_date, const InternalEmployeePtr& changer);
    bool setReceivedDate(const DatePtr& received_date, const InternalEmployeePtr& changer);
    bool setCreationDate(const DatePtr& creation_date, const InternalEmployeePtr& changer);
    bool setPaymentStatus(const PaymentStatus status, const InternalEmployeePtr& changer);
    bool setPaymentMethod(const OptionalStr& payment_method, const InternalEmployeePtr& changer);
    bool setDeal(const WDealPtr& deal, const InternalEmployeePtr& changer);
    bool setPayer(const PersonPtr& payer, const InternalEmployeePtr& changer);
    bool setPayerCompany(const CompanyPtr& payer_company, const InternalEmployeePtr& changer);
    bool setInvoiceNumber(const OptionalStr& invoice_number, const InternalEmployeePtr& changer);
    bool setTransactionId(const OptionalStr& transaction_id, const InternalEmployeePtr& changer);
    bool addDocument(const DocumentPtr& document, const InternalEmployeePtr& changer);
    bool delDocument(size_t index, const InternalEmployeePtr& changer);
    bool addComment(const std::string& comment, const InternalEmployeePtr& changer);
    bool delComment(size_t index, const InternalEmployeePtr& changer);
    bool setPaymentPurpose(const OptionalStr& payment_purpose, const InternalEmployeePtr& changer);
    bool setCreatedBy(const InternalEmployeePtr& created_by, const InternalEmployeePtr& changer);
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