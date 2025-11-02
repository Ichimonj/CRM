#include "email_letter.hpp"

#include "change_log.hpp"
#include "date.hpp"

EmailLetter::EmailLetter(const BigUint& id)
    : BaseInteraction(id, InteractionType::emailLetter)
    , email_status(EmailStatus::Draft)
    , is_flagged(false)
    , is_read(false)
    , letter_type(EmailLetterType::incoming)
{
}

EmailLetter::EmailLetter(
    const BigUint&                     id,
    const std::string&                 title,
    const OptionalStr&                 external_id,
    const OptionalStr&                 description,
    const OptionalStr&                 subject,
    const std::optional<TimeDuration>& interaction_duration,
    const Priority&                    priority,
    const InternalEmployeePtr&         manager,
    const DatePtr&                     start_date,
    const DatePtr&                     end_date,
    const InternalEmployeePtr&         checker,
    std::vector<std::string>           tags,
    std::vector<InteractionResult>     results,
    std::vector<Note>                  notes,
    std::vector<StringPair>            more_data,
    std::vector<InteractionPtr>        related_interactions,
    std::vector<FilePtr>               attachment_files,
    std::vector<PersonPtr>             participants,
    const std::string&                 from_email_address,
    const std::string&                 to_email_address,
    const EmailLetterType&             letter_type,
    const EmailStatus&                 email_status,
    std::vector<std::string>           cc_email_addresses,
    std::vector<std::string>           bcc_email_addresses,
    const PersonPtr&                   sender,
    const PersonPtr&                   recipient,
    const std::string&                 body,
    const DatePtr&                     send_date,
    const DatePtr&                     received_date,
    const DatePtr&                     read_time,
    const std::string&                 email_provider,
    const EmailLetterPtr&              previous_letter,
    const EmailLetterPtr&              next_letter,
    bool                               is_read,
    bool                               is_flagged
)
    : BaseInteraction(
          id,
          title,
          external_id,
          description,
          subject,
          interaction_duration,
          priority,
          manager,
          start_date,
          end_date,
          checker,
          InteractionType::emailLetter,
          std::move(tags),
          std::move(results),
          std::move(notes),
          std::move(more_data),
          std::move(related_interactions),
          std::move(attachment_files),
          std::move(participants)
      )
    , from_email_address(from_email_address)
    , to_email_address(to_email_address)
    , letter_type(letter_type)
    , email_status(email_status)
    , cc_email_addresses(std::move(cc_email_addresses))
    , bcc_email_addresses(std::move(bcc_email_addresses))
    , sender(sender)
    , recipient(recipient)
    , body(body)
    , send_date(send_date)
    , received_date(received_date)
    , read_time(read_time)
    , email_provider(email_provider)
    , previous_letter(previous_letter)
    , next_letter(next_letter)
    , is_read(is_read)
    , is_flagged(is_flagged)
{
}

auto EmailLetter::getFromEmailAddress() const -> const std::string&
{
    return this->from_email_address;
}
auto EmailLetter::getToEmailAddress() const -> const std::string& { return this->to_email_address; }
auto EmailLetter::getLetterType() const -> EmailLetterType { return this->letter_type; }
auto EmailLetter::getEmailStatus() const -> EmailStatus { return this->email_status; }
auto EmailLetter::getCcEmailAddresses() const -> const std::vector<std::string>&
{
    return this->cc_email_addresses;
}
auto EmailLetter::getBccEmailAddresses() const -> const std::vector<std::string>&
{
    return this->bcc_email_addresses;
}
auto EmailLetter::getSender() const -> const PersonPtr { return this->sender; }
auto EmailLetter::getRecipient() const -> const PersonPtr { return this->recipient; }
auto EmailLetter::getBody() const -> const std::string& { return this->body; }
auto EmailLetter::getSendDate() const -> const DatePtr { return this->send_date; }
auto EmailLetter::getReceivedDate() const -> const DatePtr { return this->received_date; }
auto EmailLetter::getReadTime() const -> const DatePtr { return this->read_time; }
auto EmailLetter::getEmailProvider() const -> const std::string& { return this->email_provider; }
auto EmailLetter::getPreviousLetter() const -> const EmailLetterPtr
{
    return this->previous_letter;
}
auto EmailLetter::getNextLetter() const -> const EmailLetterPtr { return this->next_letter; }
auto EmailLetter::getIsRead() const -> bool { return this->is_read; }
auto EmailLetter::getIsFlagged() const -> bool { return this->is_flagged; }

void EmailLetter::setFromEmailAddress(const std::string& email, const InternalEmployeePtr& changer)
{
    if (this->from_email_address != email) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<std::string>(this->from_email_address)
            ),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(email)),
            EmailLetterFields::FromEmailAddress,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->from_email_address = email;
    }
}

void EmailLetter::setToEmailAddress(const std::string& email, const InternalEmployeePtr& changer)
{
    if (this->to_email_address != email) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<std::string>(this->to_email_address)
            ),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(email)),
            EmailLetterFields::ToEmailAddress,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->to_email_address = email;
    }
}

void EmailLetter::setLetterType(EmailLetterType type, const InternalEmployeePtr& changer)
{
    if (this->letter_type != type) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->letter_type),
            std::make_optional<ChangeLog::ValueVariant>(type),
            EmailLetterFields::LetterType,
            ChangeLog::FieldType::EmailLetterType,
            ChangeLog::FieldType::EmailLetterType,
            ChangeLog::Action::Change
        ));
        this->letter_type = type;
    }
}

void EmailLetter::setEmailStatus(EmailStatus status, const InternalEmployeePtr& changer)
{
    if (this->email_status != status) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->email_status),
            std::make_optional<ChangeLog::ValueVariant>(status),
            EmailLetterFields::EmailStatus,
            ChangeLog::FieldType::EmailStatus,
            ChangeLog::FieldType::EmailStatus,
            ChangeLog::Action::Change
        ));
        this->email_status = status;
    }
}

void EmailLetter::addCcEmailAddress(const std::string& address, const InternalEmployeePtr& changer)
{
    if (std::find(this->cc_email_addresses.begin(), this->cc_email_addresses.end(), address) ==
        this->cc_email_addresses.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(address)),
            EmailLetterFields::CcEmailAddresses,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Add
        ));
        this->cc_email_addresses.push_back(address);
    }
}

void EmailLetter::delCcEmailAddress(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->cc_email_addresses.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<std::string>(this->cc_email_addresses[id])
            ),
            std::nullopt,
            EmailLetterFields::CcEmailAddresses,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->cc_email_addresses.erase(this->cc_email_addresses.begin() + id);
    }
}

void EmailLetter::addBccEmailAddress(const std::string& address, const InternalEmployeePtr& changer)
{
    if (std::find(this->bcc_email_addresses.begin(), this->bcc_email_addresses.end(), address) ==
        this->bcc_email_addresses.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(address)),
            EmailLetterFields::BccEmailAddresses,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Add
        ));
        this->bcc_email_addresses.push_back(address);
    }
}

void EmailLetter::delBccEmailAddress(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->bcc_email_addresses.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<std::string>(this->bcc_email_addresses[id])
            ),
            std::nullopt,
            EmailLetterFields::BccEmailAddresses,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->bcc_email_addresses.erase(this->bcc_email_addresses.begin() + id);
    }
}

void EmailLetter::setSender(const PersonPtr& sender, const InternalEmployeePtr& changer)
{
    if (this->sender != sender) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->sender),
            PTR_TO_OPTIONAL(sender),
            EmailLetterFields::Sender,
            this->sender ? ChangeLog::FieldType::Person : ChangeLog::FieldType::null,
            sender ? ChangeLog::FieldType::Person : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->sender = sender;
    }
}

void EmailLetter::setRecipient(const PersonPtr& recipient, const InternalEmployeePtr& changer)
{
    if (this->recipient != recipient) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->recipient),
            PTR_TO_OPTIONAL(recipient),
            EmailLetterFields::Recipient,
            this->recipient ? ChangeLog::FieldType::Person : ChangeLog::FieldType::null,
            recipient ? ChangeLog::FieldType::Person : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->recipient = recipient;
    }
}

void EmailLetter::setBody(const std::string& body, const InternalEmployeePtr& changer)
{
    if (this->body != body) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(this->body)),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(body)),
            EmailLetterFields::Body,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->body = body;
    }
}

void EmailLetter::setSendDate(const DatePtr& date, const InternalEmployeePtr& changer)
{
    if (this->send_date == nullptr || date == nullptr) {
        if (this->send_date == date) {
            return;
        }
    } else if (*this->send_date == *date) {
        return;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->send_date),
        PTR_TO_OPTIONAL(send_date),
        EmailLetterFields::SendDate,
        this->send_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        send_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->send_date = date;
}

void EmailLetter::setReceivedDate(const DatePtr& date, const InternalEmployeePtr& changer)
{
    if (this->received_date == nullptr || date == nullptr) {
        if (this->received_date == date) {
            return;
        }
    } else if (*this->received_date == *date) {
        return;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->received_date),
        PTR_TO_OPTIONAL(received_date),
        EmailLetterFields::ReceivedDate,
        this->received_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        received_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->received_date = date;
}

void EmailLetter::setReadTime(const DatePtr& time, const InternalEmployeePtr& changer)
{
    if (this->read_time == nullptr || time == nullptr) {
        if (this->read_time == time) {
            return;
        }
    } else if (*this->read_time == *time) {
        return;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->read_time),
        PTR_TO_OPTIONAL(time),
        EmailLetterFields::ReadTime,
        this->read_time ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        time ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->read_time = time;
}

void EmailLetter::setEmailProvider(const std::string& provider, const InternalEmployeePtr& changer)
{
    if (this->email_provider != provider) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<std::string>(this->email_provider)
            ),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(provider)),
            EmailLetterFields::EmailProvider,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->email_provider = provider;
    }
}

void EmailLetter::setPreviousLetter(
    const EmailLetterPtr& letter, const InternalEmployeePtr& changer
)
{
    if (this->previous_letter != letter) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->previous_letter),
            std::make_optional<ChangeLog::ValueVariant>(letter),
            EmailLetterFields::PreviousLetter,
            ChangeLog::FieldType::EmailLetter,
            ChangeLog::FieldType::EmailLetter,
            ChangeLog::Action::Change
        ));
        this->previous_letter = letter;
    }
}

void EmailLetter::setNextLetter(const EmailLetterPtr& letter, const InternalEmployeePtr& changer)
{
    if (this->next_letter != letter) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->next_letter),
            std::make_optional<ChangeLog::ValueVariant>(letter),
            EmailLetterFields::NextLetter,
            ChangeLog::FieldType::EmailLetter,
            ChangeLog::FieldType::EmailLetter,
            ChangeLog::Action::Change
        ));
        this->next_letter = letter;
    }
}

void EmailLetter::setIsRead(bool is_read, const InternalEmployeePtr& changer)
{
    if (this->is_read != is_read) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->is_read),
            std::make_optional<ChangeLog::ValueVariant>(is_read),
            EmailLetterFields::IsRead,
            ChangeLog::FieldType::Bool,
            ChangeLog::FieldType::Bool,
            ChangeLog::Action::Change
        ));
        this->is_read = is_read;
    }
}

void EmailLetter::setIsFlagged(bool is_flagged, const InternalEmployeePtr& changer)
{
    if (this->is_flagged != is_flagged) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->is_flagged),
            std::make_optional<ChangeLog::ValueVariant>(is_flagged),
            EmailLetterFields::IsFlagged,
            ChangeLog::FieldType::Bool,
            ChangeLog::FieldType::Bool,
            ChangeLog::Action::Change
        ));
        this->is_flagged = is_flagged;
    }
}
