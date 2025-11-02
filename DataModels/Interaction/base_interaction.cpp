#include "base_interaction.hpp"

#include "change_log.hpp"
#include "date.hpp"
#include "task.hpp"

BaseInteraction::BaseInteraction(const BigUint& id, InteractionType type)
    : id(id), priority(Priority::null), type(type)
{
}

BaseInteraction::BaseInteraction(
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
    const InteractionType&             type,
    std::vector<std::string>           tags,
    std::vector<InteractionResult>     results,
    std::vector<Note>                  notes,
    std::vector<StringPair>            more_data,
    std::vector<InteractionPtr>        related_interactions,
    std::vector<FilePtr>               attachment_files,
    std::vector<PersonPtr>             participants
)
    : id(id)
    , external_id(external_id)
    , title(title)
    , description(description)
    , interaction_duration(interaction_duration)
    , priority(priority)
    , manager(manager)
    , subject(subject)
    , start_date(start_date)
    , end_date(end_date)
    , checker(checker)
    , type(type)
    , tags(std::move(tags))
    , results(std::move(results))
    , notes(std::move(notes))
    , more_data(std::move(more_data))
    , related_interactions(std::move(related_interactions))
    , attachment_files(std::move(attachment_files))
    , participants(std::move(participants))
{
}

auto BaseInteraction::getId() const -> const BigUint& { return this->id; }
auto BaseInteraction::getTitle() const -> const std::string& { return this->title; }
auto BaseInteraction::getExternalId() const -> const OptionalStr& { return this->external_id; }
auto BaseInteraction::getDescription() const -> const OptionalStr& { return this->description; }
auto BaseInteraction::getSubject() const -> const OptionalStr& { return this->subject; }
auto BaseInteraction::getInteractionDuration() const -> const std::optional<TimeDuration>&
{
    return this->interaction_duration;
}
auto BaseInteraction::getPriority() const -> Priority { return this->priority; }
auto BaseInteraction::getTags() const -> const std::vector<std::string>& { return this->tags; }
auto BaseInteraction::getResults() const -> const std::vector<InteractionResult>&
{
    return this->results;
}
auto BaseInteraction::getManager() const -> const InternalEmployeePtr& { return this->manager; }
auto BaseInteraction::getNotes() const -> const std::vector<Note>& { return this->notes; }
auto BaseInteraction::getMoreData() const -> const std::vector<StringPair>&
{
    return this->more_data;
}
auto BaseInteraction::getRelatedInteractions() const -> const std::vector<InteractionPtr>&
{
    return this->related_interactions;
}
auto BaseInteraction::getAttachmentFiles() const -> const std::vector<FilePtr>&
{
    return this->attachment_files;
}
auto BaseInteraction::getCreatedDate() const -> const Date& { return this->created_date; }
auto BaseInteraction::getStartDate() const -> const DatePtr& { return this->start_date; }
auto BaseInteraction::getEndDate() const -> const DatePtr& { return this->end_date; }
auto BaseInteraction::getChecker() const -> const InternalEmployeePtr& { return this->checker; }
auto BaseInteraction::getParticipants() const -> const std::vector<PersonPtr>&
{
    return this->participants;
}
auto BaseInteraction::getType() const -> InteractionType { return this->type; }
auto BaseInteraction::getChangeLogs() const -> const std::vector<ChangeLogPtr>&
{
    return this->change_logs;
}
void BaseInteraction::setExternalId(const OptionalStr& id, const InternalEmployeePtr& changer)
{
    if (this->external_id != id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->external_id),
            OPTIONAL_STR_TO_VALUE(id),
            BaseInteractionFields::ExternalID,
            this->external_id ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            id ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->external_id = id;
    }
}

void BaseInteraction::setTitle(const std::string& title, const InternalEmployeePtr& changer)
{
    if (this->title != title) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(this->title)),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(title)),
            BaseInteractionFields::Title,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->title = title;
    }
}

void BaseInteraction::setDescription(
    const OptionalStr& description, const InternalEmployeePtr& changer
)
{
    if (this->description != description) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->description),
            OPTIONAL_STR_TO_VALUE(description),
            BaseInteractionFields::Description,
            this->description ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            description ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->description = description;
    }
}

void BaseInteraction::setDuration(
    const std::optional<TimeDuration>& duration, const InternalEmployeePtr& changer
)
{
    if (this->interaction_duration != duration) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->interaction_duration
                ? std::make_optional<ChangeLog::ValueVariant>(
                      std::make_shared<TimeDuration>(this->interaction_duration.value())
                  )
                : std::nullopt,
            duration ? std::make_optional<ChangeLog::ValueVariant>(
                           std::make_shared<TimeDuration>(duration.value())
                       )
                     : std::nullopt,
            BaseInteractionFields::InteractionDuration,
            this->interaction_duration ? ChangeLog::FieldType::TimeDuration
                                       : ChangeLog::FieldType::null,
            duration ? ChangeLog::FieldType::TimeDuration : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->interaction_duration = duration;
    }
}

void BaseInteraction::setPriority(const Priority& priority, const InternalEmployeePtr& changer)
{
    if (this->priority != priority) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->priority),
            std::make_optional<ChangeLog::ValueVariant>(priority),
            BaseInteractionFields::Priority,
            ChangeLog::FieldType::Priority,
            ChangeLog::FieldType::Priority,
            ChangeLog::Action::Change
        ));
        this->priority = priority;
    }
}

void BaseInteraction::addTag(const std::string& tag, const InternalEmployeePtr& changer)
{
    if (std::find(this->tags.begin(), this->tags.end(), tag) == this->tags.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(tag)),
            BaseInteractionFields::Tags,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Add
        ));
        this->tags.push_back(tag);
    }
}

void BaseInteraction::delTag(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->tags.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(this->tags[id]
            )),
            std::nullopt,
            BaseInteractionFields::Tags,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->tags.erase(this->tags.begin() + id);
    }
}

void BaseInteraction::addResult(const InteractionResult& result, const InternalEmployeePtr& changer)
{
    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        std::nullopt,
        std::make_optional<ChangeLog::ValueVariant>(std::make_shared<InteractionResult>(result)),
        BaseInteractionFields::Results,
        ChangeLog::FieldType::null,
        ChangeLog::FieldType::InteractionResult,
        ChangeLog::Action::Add
    ));
    this->results.push_back(result);
}

void BaseInteraction::delResult(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->results.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<InteractionResult>(this->results[id])
            ),
            std::nullopt,
            BaseInteractionFields::Results,
            ChangeLog::FieldType::InteractionResult,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->results.erase(this->results.begin() + id);
    }
}

void BaseInteraction::setManager(
    const InternalEmployeePtr& manager, const InternalEmployeePtr& changer
)
{
    if (this->manager != manager) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->manager),
            PTR_TO_OPTIONAL(manager),
            BaseInteractionFields::Manager,
            this->manager ? ChangeLog::FieldType::InternalEmployee : ChangeLog::FieldType::null,
            manager ? ChangeLog::FieldType::InternalEmployee : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->manager = manager;
    }
}

void BaseInteraction::addNote(const Note& note, const InternalEmployeePtr& changer)
{
    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        std::nullopt,
        std::make_optional<ChangeLog::ValueVariant>(std::make_shared<Note>(note)),
        BaseInteractionFields::Notes,
        ChangeLog::FieldType::null,
        ChangeLog::FieldType::Note,
        ChangeLog::Action::Add
    ));
    this->notes.push_back(note);
}

void BaseInteraction::delNote(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->notes.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<Note>(this->notes[id])),
            std::nullopt,
            BaseInteractionFields::Notes,
            ChangeLog::FieldType::Note,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->notes.erase(this->notes.begin() + id);
    }
}

void BaseInteraction::addMoreData(
    const std::string& title, const std::string& data, const InternalEmployeePtr& changer
)
{
    auto pair = std::make_pair(title, data);
    if (std::find(this->more_data.begin(), this->more_data.end(), pair) == this->more_data.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<std::pair<const std::string, const std::string>>(pair)
            ),
            BaseInteractionFields::MoreData,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::StringPair,
            ChangeLog::Action::Add
        ));
        this->more_data.push_back(pair);
    }
}

void BaseInteraction::delMoreData(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->more_data.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<std::pair<const std::string, const std::string>>(
                    this->more_data[id]
                )
            ),
            std::nullopt,
            BaseInteractionFields::MoreData,
            ChangeLog::FieldType::StringPair,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->more_data.erase(this->more_data.begin() + id);
    }
}

void BaseInteraction::addRelatedInteractions(
    const InteractionPtr& interaction, const InternalEmployeePtr& changer
)
{
    if (std::find(
            this->related_interactions.begin(), this->related_interactions.end(), interaction
        ) == this->related_interactions.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(interaction),
            BaseInteractionFields::RelatedInteractions,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::BaseInteraction,
            ChangeLog::Action::Add
        ));
        this->related_interactions.push_back(interaction);
    }
}

void BaseInteraction::delRelatedInteractions(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->related_interactions.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->related_interactions[id]),
            std::nullopt,
            BaseInteractionFields::RelatedInteractions,
            ChangeLog::FieldType::BaseInteraction,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->related_interactions.erase(this->related_interactions.begin() + id);
    }
}

void BaseInteraction::addAttachmentFiles(const FilePtr& file, const InternalEmployeePtr& changer)
{
    if (std::find(this->attachment_files.begin(), this->attachment_files.end(), file) ==
        this->attachment_files.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(file),
            BaseInteractionFields::AttachmentFiles,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::FileMetadata,
            ChangeLog::Action::Add
        ));
        this->attachment_files.push_back(file);
    }
}

void BaseInteraction::delAttachmentFiles(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->attachment_files.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->attachment_files[id]),
            std::nullopt,
            BaseInteractionFields::AttachmentFiles,
            ChangeLog::FieldType::FileMetadata,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->attachment_files.erase(this->attachment_files.begin() + id);
    }
}

void BaseInteraction::setSubject(const OptionalStr& subject, const InternalEmployeePtr& changer)
{
    if (this->subject != subject) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->subject),
            OPTIONAL_STR_TO_VALUE(subject),
            BaseInteractionFields::Subject,
            this->subject ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            subject ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->subject = subject;
    }
}

void BaseInteraction::setStartDate(const DatePtr& date, const InternalEmployeePtr& changer)
{
    if (this->start_date == nullptr || date == nullptr) {
        if (this->start_date == date) {
            return;
        }
    } else if (*this->start_date == *date) {
        return;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->start_date),
        PTR_TO_OPTIONAL(date),
        BaseInteractionFields::StartDate,
        this->start_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->start_date = date;
}

void BaseInteraction::setEndDate(const DatePtr& date, const InternalEmployeePtr& changer)
{
    if (this->end_date == nullptr || date == nullptr) {
        if (this->end_date == date) {
            return;
        }
    } else if (*this->end_date == *date) {
        return;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->end_date),
        PTR_TO_OPTIONAL(date),
        BaseInteractionFields::EndDate,
        this->end_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->end_date = date;
}

void BaseInteraction::setChecker(
    const InternalEmployeePtr& checker, const InternalEmployeePtr& changer
)
{
    if (this->checker != checker)
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->checker),
            PTR_TO_OPTIONAL(checker),
            BaseInteractionFields::Checker,
            this->checker ? ChangeLog::FieldType::InternalEmployee : ChangeLog::FieldType::null,
            checker ? ChangeLog::FieldType::InternalEmployee : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
    this->checker = checker;
}

void BaseInteraction::addParticipants(
    const PersonPtr& participant, const InternalEmployeePtr& changer
)
{
    if (std::find(this->participants.begin(), this->participants.end(), participant) ==
        this->participants.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(participant),
            BaseInteractionFields::Participants,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Person,
            ChangeLog::Action::Add
        ));
        this->participants.push_back(participant);
    }
}

void BaseInteraction::delParticipants(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->participants.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->participants[id]),
            std::nullopt,
            BaseInteractionFields::Participants,
            ChangeLog::FieldType::Person,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->participants.erase(this->participants.begin() + id);
    }
}

void BaseInteraction::setType(const InteractionType& type, const InternalEmployeePtr& changer)
{
    if (this->type != type) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->type),
            std::make_optional<ChangeLog::ValueVariant>(type),
            BaseInteractionFields::Type,
            ChangeLog::FieldType::InteractionType,
            ChangeLog::FieldType::InteractionType,
            ChangeLog::Action::Change
        ));
        this->type = type;
    }
}

void BaseInteraction::addChangeLog(const ChangeLogPtr& changeLog)
{
    if (std::find(this->change_logs.begin(), this->change_logs.end(), changeLog) ==
        this->change_logs.end()) {
        this->change_logs.push_back(changeLog);
    }
}

const std::string BaseInteraction::interactionTypeStr(const InteractionType type)
{
    switch (type) {
        case InteractionType::phoneCall:
            return interaction_type_str::phoneCall;
        case InteractionType::emailLetter:
            return interaction_type_str::emailLetter;
        case InteractionType::emailThread:
            return interaction_type_str::emailThread;
        case InteractionType::meeting:
            return interaction_type_str::meeting;
        case InteractionType::meetingThread:
            return interaction_type_str::meetingThread;
        case InteractionType::message:
            return interaction_type_str::message;
        case InteractionType::correspondence:
            return interaction_type_str::correspondence;
        case InteractionType::commentarySocialNetworks:
            return interaction_type_str::commentarySocialNetworks;
        case InteractionType::commentarySocialNetworksThread:
            return interaction_type_str::commentarySocialNetworksThread;
        case InteractionType::unknown:
            return interaction_type_str::unknown;
    }
    return std::string();
}