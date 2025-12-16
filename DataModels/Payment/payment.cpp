#include "payment.hpp"

#include "change_log.hpp"
#include "deal.hpp"

Payment::Payment(const BigUint& id) : id(id), status(PaymentStatus::pending) {}

Payment::Payment(
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
)
    : id(id)
    , requested_amount(requested_amount)
    , sending_amount(sending_amount)
    , received_amount(received_amount)
    , tax_amount(tax_amount)
    , currency(currency)
    , sending_date(sending_date)
    , received_date(received_date)
    , creation_date(creation_date)
    , status(status)
    , payment_method(payment_method)
    , deal(deal)
    , payer(payer)
    , payer_company(payer_company)
    , invoice_number(invoice_number)
    , transaction_id(transaction_id)
    , payment_purpose(payment_purpose)
    , created_by(created_by)
    , documents(std::move(documents))
    , comments(std::move(comments))

{
}

auto Payment::getId() const -> const BigUint& { return this->id; }
auto Payment::getRequestedAmount() const -> const MoneyPtr& { return this->requested_amount; }
auto Payment::getSendingAmount() const -> const MoneyPtr& { return this->sending_amount; }
auto Payment::getReceivedAmount() const -> const MoneyPtr& { return this->received_amount; }
auto Payment::getTaxAmount() const -> const MoneyPtr& { return this->tax_amount; }
auto Payment::getCurrency() const -> const Currencies& { return this->currency; }
auto Payment::getSendingDate() const -> const DatePtr& { return this->sending_date; }
auto Payment::getReceivedDate() const -> const DatePtr& { return this->received_date; }
auto Payment::getCreationDate() const -> const DatePtr& { return this->creation_date; }
auto Payment::getPaymentStatus() const -> const PaymentStatus { return this->status; }
auto Payment::getPaymentMethod() const -> const OptionalStr& { return this->payment_method; }
auto Payment::getDeal() const -> const WDealPtr& { return this->deal; }
auto Payment::getPayer() const -> const PersonPtr& { return this->payer; }
auto Payment::getPayerCompany() const -> const CompanyPtr& { return this->payer_company; }
auto Payment::getInvoiceNumber() const -> const OptionalStr& { return this->invoice_number; }
auto Payment::getTransactionId() const -> const OptionalStr& { return this->transaction_id; }
auto Payment::getDocuments() const -> const std::vector<DocumentPtr>& { return this->documents; }
auto Payment::getComments() const -> const std::vector<std::string>& { return this->comments; }
auto Payment::getPaymentPurpose() const -> const OptionalStr& { return this->payment_purpose; }
auto Payment::getCreatedBy() const -> const InternalEmployeePtr& { return this->created_by; }
auto Payment::getChangeLogs() const -> const std::vector<ChangeLogPtr>&
{
    return this->change_logs;
}

bool Payment::setRequestedAmount(
    const MoneyPtr& requested_amount, const InternalEmployeePtr& changer
)
{
    if (this->requested_amount == nullptr || requested_amount == nullptr) {
        if (this->requested_amount == requested_amount) {
            return false;
        }
    } else if (*this->requested_amount == *requested_amount) {
        return false;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->requested_amount),
        PTR_TO_OPTIONAL(requested_amount),
        PaymentFields::RequestedAmount,
        this->requested_amount ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        requested_amount ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->requested_amount = requested_amount;
    return true;
}

bool Payment::setSendingAmount(const MoneyPtr& sending_amount, const InternalEmployeePtr& changer)
{
    if (this->sending_amount == nullptr || sending_amount == nullptr) {
        if (this->sending_amount == sending_amount) {
            return false;
        }
    } else if (*this->sending_amount == *sending_amount) {
        return false;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->sending_amount),
        PTR_TO_OPTIONAL(sending_amount),
        PaymentFields::SendingAmount,
        this->sending_amount ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        sending_amount ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->sending_amount = sending_amount;
    return true;
}

bool Payment::setReceivedAmount(const MoneyPtr& received_amount, const InternalEmployeePtr& changer)
{
    if (this->received_amount == nullptr || received_amount == nullptr) {
        if (this->received_amount == received_amount) {
            return false;
        }
    } else if (*this->received_amount == *received_amount) {
        return false;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->received_amount),
        PTR_TO_OPTIONAL(received_amount),
        PaymentFields::ReceivedAmount,
        this->received_amount ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        received_amount ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->received_amount = received_amount;
    return true;
}

bool Payment::setTaxAmount(const MoneyPtr& tax_amount, const InternalEmployeePtr& changer)
{
    if (this->tax_amount == nullptr || tax_amount == nullptr) {
        if (this->tax_amount == tax_amount) {
            return false;
        }
    } else if (*this->tax_amount == *tax_amount) {
        return false;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->tax_amount),
        PTR_TO_OPTIONAL(tax_amount),
        PaymentFields::TaxAmount,
        this->tax_amount ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        tax_amount ? ChangeLog::FieldType::Money : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->tax_amount = tax_amount;
    return true;
}

bool Payment::setCurrency(const Currencies& currency, const InternalEmployeePtr& changer)
{
    if (this->currency != currency) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->currency),
            std::make_optional<ChangeLog::ValueVariant>(currency),
            PaymentFields::Currencies,
            ChangeLog::FieldType::Currencies,
            ChangeLog::FieldType::Currencies,
            ChangeLog::Action::Change
        ));
        this->currency = currency;
        return true;
    }
    return false;
}

bool Payment::setSendingDate(const DatePtr& sending_date, const InternalEmployeePtr& changer)
{
    if (this->sending_date == nullptr || sending_date == nullptr) {
        if (this->sending_date == sending_date) {
            return false;
        }
    } else if (*this->sending_date == *sending_date) {
        return false;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->sending_date),
        PTR_TO_OPTIONAL(sending_date),
        PaymentFields::SendingDate,
        this->sending_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        sending_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->sending_date = sending_date;
    return true;
}

bool Payment::setReceivedDate(const DatePtr& received_date, const InternalEmployeePtr& changer)
{
    if (this->received_date == nullptr || received_date == nullptr) {
        if (this->received_date == received_date) {
            return false;
        }
    } else if (*this->received_date == *received_date) {
        return false;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->received_date),
        PTR_TO_OPTIONAL(received_date),
        PaymentFields::ReceivedDate,
        this->received_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        received_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->received_date = received_date;
    return true;
}

bool Payment::setCreationDate(const DatePtr& creation_date, const InternalEmployeePtr& changer)
{
    if (this->creation_date == nullptr || creation_date == nullptr) {
        if (this->creation_date == creation_date) {
            return false;
        }
    } else if (*this->creation_date == *creation_date) {
        return false;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->creation_date),
        PTR_TO_OPTIONAL(creation_date),
        PaymentFields::CreationDate,
        this->creation_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        creation_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->creation_date = creation_date;
    return true;
}

bool Payment::setPaymentStatus(const PaymentStatus status, const InternalEmployeePtr& changer)
{
    if (this->status != status) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->status),
            std::make_optional<ChangeLog::ValueVariant>(status),
            PaymentFields::PaymentStatus,
            ChangeLog::FieldType::PaymentStatus,
            ChangeLog::FieldType::PaymentStatus,
            ChangeLog::Action::Change
        ));
        this->status = status;
        return true;
    }
    return false;
}

bool Payment::setPaymentMethod(
    const OptionalStr& payment_method, const InternalEmployeePtr& changer
)
{
    if (this->payment_method != payment_method) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->payment_method),
            OPTIONAL_STR_TO_VALUE(payment_method),
            PaymentFields::PaymentMethod,
            this->payment_method ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            payment_method ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->payment_method = payment_method;
        return true;
    }
    return false;
}

bool Payment::setDeal(const WDealPtr& deal, const InternalEmployeePtr& changer)
{
    if (this->deal.lock() != deal.lock()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->deal.lock()),
            PTR_TO_OPTIONAL(deal.lock()),
            PaymentFields::Deal,
            this->deal.lock() ? ChangeLog::FieldType::Deal : ChangeLog::FieldType::null,
            deal.lock() ? ChangeLog::FieldType::Deal : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->deal = deal;
        return true;
    }
    return false;
}

bool Payment::setPayer(const PersonPtr& payer, const InternalEmployeePtr& changer)
{
    if (this->payer != payer) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->payer),
            PTR_TO_OPTIONAL(payer),
            PaymentFields::Payer,
            this->payer ? ChangeLog::FieldType::Person : ChangeLog::FieldType::null,
            payer ? ChangeLog::FieldType::Person : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->payer = payer;
        return true;
    }
    return false;
}

bool Payment::setPayerCompany(const CompanyPtr& payer_company, const InternalEmployeePtr& changer)
{
    if (this->payer_company != payer_company) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->payer_company),
            PTR_TO_OPTIONAL(payer_company),
            PaymentFields::PayerCompany,
            this->payer_company ? ChangeLog::FieldType::Company : ChangeLog::FieldType::null,
            payer_company ? ChangeLog::FieldType::Company : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->payer_company = payer_company;
        return true;
    }
    return false;
}

bool Payment::setInvoiceNumber(
    const OptionalStr& invoice_number, const InternalEmployeePtr& changer
)
{
    if (this->invoice_number != invoice_number) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->invoice_number),
            OPTIONAL_STR_TO_VALUE(invoice_number),
            PaymentFields::InvoiceNumber,
            this->invoice_number ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            invoice_number ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->invoice_number = invoice_number;
        return true;
    }
    return false;
}

bool Payment::setTransactionId(
    const OptionalStr& transaction_id, const InternalEmployeePtr& changer
)
{
    if (this->transaction_id != transaction_id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->transaction_id),
            OPTIONAL_STR_TO_VALUE(transaction_id),
            PaymentFields::TransactionId,
            this->transaction_id ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            transaction_id ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->transaction_id = transaction_id;
        return true;
    }
    return false;
}

bool Payment::addDocument(const DocumentPtr& document, const InternalEmployeePtr& changer)
{
    if (std::find(this->documents.begin(), this->documents.end(), document) ==
        this->documents.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(document),
            PaymentFields::Documents,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Document,
            ChangeLog::Action::Add
        ));
        this->documents.push_back(document);
        return true;
    }
    return false;
}

bool Payment::delDocument(size_t index, const InternalEmployeePtr& changer)
{
    if (index < this->documents.size()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->documents[index]),
            std::nullopt,
            PaymentFields::Documents,
            ChangeLog::FieldType::Document,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->documents.erase(this->documents.begin() + index);
        return true;
    }
    return false;
}

bool Payment::addComment(const std::string& comment, const InternalEmployeePtr& changer)
{
    if (std::find(this->comments.begin(), this->comments.end(), comment) == this->comments.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(comment)),
            PaymentFields::Comments,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Add
        ));
        this->comments.push_back(comment);
        return true;
    }
    return false;
}

bool Payment::delComment(size_t index, const InternalEmployeePtr& changer)
{
    if (index < this->comments.size()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<std::string>(this->comments[index])
            ),
            std::nullopt,
            PaymentFields::Comments,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->comments.erase(this->comments.begin() + index);
        return true;
    }
    return false;
}

bool Payment::setPaymentPurpose(
    const OptionalStr& payment_purpose, const InternalEmployeePtr& changer
)
{
    if (this->payment_purpose != payment_purpose) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->payment_purpose),
            OPTIONAL_STR_TO_VALUE(payment_purpose),
            PaymentFields::PaymentPurpose,
            this->payment_purpose ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            payment_purpose ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->payment_purpose = payment_purpose;
        return true;
    }
    return false;
}

bool Payment::setCreatedBy(
    const InternalEmployeePtr& created_by, const InternalEmployeePtr& changer
)
{
    if (this->created_by != created_by) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->created_by),
            PTR_TO_OPTIONAL(created_by),
            PaymentFields::CreatedBy,
            this->created_by ? ChangeLog::FieldType::InternalEmployee : ChangeLog::FieldType::null,
            created_by ? ChangeLog::FieldType::InternalEmployee : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->created_by = created_by;
        return true;
    }
    return false;
}