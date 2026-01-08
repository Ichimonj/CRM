#include "message.hpp"

#include "ChangeLog/change_log.hpp"

Message::Message(const BigUint& id) : BaseInteraction(id, InteractionType::message) {}

Message::Message(
    const BigUint&                     id,
    const std::string&                 title,
    const OptionalStr&                 external_id,
    const OptionalStr&                 description,
    const OptionalStr&                 subject,
    const std::optional<TimeDuration>& interaction_duration,
    const Priority&                    priority,
    const WeakInternalEmployee&        manager,
    const DatePtr&                     start_date,
    const DatePtr&                     end_date,
    const WeakInternalEmployee&        checker,
    const InteractionType&             type,
    std::vector<std::string>           tags,
    std::vector<InteractionResult>     results,
    std::vector<Note>                  notes,
    std::vector<StringPair>            more_data,
    std::vector<InteractionPtr>        related_interactions,
    std::vector<FilePtr>               attachment_files,
    std::vector<WeakPersonPtr>         participants,
    const std::string&                 nickname,
    const PersonPtr&                   author,
    const std::string&                 message,
    const std::string&                 platform,
    const Date&                        date_sending
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
          InteractionType::message,
          std::move(tags),
          std::move(results),
          std::move(notes),
          std::move(more_data),
          std::move(related_interactions),
          std::move(attachment_files),
          std::move(participants)
      )
    , nickname(nickname)
    , author(author)
    , message(message)
    , platform(platform)
    , date_sending(date_sending)
{
}

auto Message::getNickname() const -> const std::string& { return nickname; }
auto Message::getAuthor() const -> const PersonPtr { return author; }
auto Message::getMessage() const -> const std::string& { return message; }
auto Message::getPlatform() const -> const std::string& { return platform; }
auto Message::getDateSending() const -> const Date& { return date_sending; }

bool Message::setNickname(const std::string& nickname, const InternalEmployeePtr& changer)
{
    if (this->nickname != nickname) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(this->nickname
            )),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(nickname)),
            MessageFields::Nickname,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->nickname = nickname;
        return true;
    }
    return false;
}

bool Message::setAuthor(const PersonPtr& author, const InternalEmployeePtr& changer)
{
    if (this->author != author) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->author),
            PTR_TO_OPTIONAL(author),
            MessageFields::Author,
            this->author ? ChangeLog::FieldType::Person : ChangeLog::FieldType::null,
            author ? ChangeLog::FieldType::Person : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->author = author;
        return true;
    }
    return false;
}

bool Message::setMessage(const std::string& message, const InternalEmployeePtr& changer)
{
    if (this->message != message) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(this->message)
            ),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(message)),
            MessageFields::Message,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->message = message;
        return true;
    }
    return false;
}

bool Message::setPlatform(const std::string& platform, const InternalEmployeePtr& changer)
{
    if (this->platform != platform) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(this->platform
            )),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(platform)),
            MessageFields::Platform,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->platform = platform;
        return true;
    }
    return false;
}

bool Message::setDateSending(const Date& date, const InternalEmployeePtr& changer)
{
    if (this->date_sending != date) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<Date>(this->date_sending)),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<Date>(date)),
            MessageFields::DateSending,
            ChangeLog::FieldType::Date,
            ChangeLog::FieldType::Date,
            ChangeLog::Action::Change
        ));
        this->date_sending = date;
        return true;
    }
    return false;
}