#include "correspondence.hpp"

#include "change_log.hpp"

Correspondence::Correspondence(const BigUint& id)
    :BaseInteraction(id, InteractionType::correspondence)
{
}

Correspondence::Correspondence(
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
    std::vector<MessagePtr>            messages,
    const std::string&                 platform
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
          InteractionType::correspondence,
          std::move(tags),
          std::move(results),
          std::move(notes),
          std::move(more_data),
          std::move(related_interactions),
          std::move(attachment_files),
          std::move(participants)
      )
    , messages(std::move(messages))
    , platform(platform)
{
}

auto Correspondence::getMessages() const -> const std::vector<MessagePtr>&
{
    return this->messages;
}
auto Correspondence::getPlatform() const -> const std::string& { return this->platform; }

void Correspondence::addMessage(const MessagePtr& message, const InternalEmployeePtr& changer)
{
    if (std::find(this->messages.begin(), this->messages.end(), message) == this->messages.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(message),
            CorrespondenceFields::Messages,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Message,
            ChangeLog::Action::Add
        ));
        this->messages.push_back(message);
    }
}

void Correspondence::delMessage(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->messages.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->messages[id]),
            std::nullopt,
            CorrespondenceFields::Messages,
            ChangeLog::FieldType::Message,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->messages.erase(this->messages.begin() + id);
    }
}

void Correspondence::setPlatform(const std::string& platform, const InternalEmployeePtr& changer)
{
    if (this->platform != platform) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(this->platform
            )),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(platform)),
            CorrespondenceFields::Platform,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->platform = platform;
    }
}
