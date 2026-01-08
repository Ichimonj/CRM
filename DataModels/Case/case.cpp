#include "case.hpp"

#include "ChangeLog/change_log.hpp"

Case::Case(const BigUint& id) : id(id), status(CaseStatus::Open) {}

Case::Case(
    const BigUint&                  id,
    const std::string&              title,
    const OptionalStr&              description,
    const CaseStatus&               status,
    const Priority&                 priority,
    const Date&                     create_date,
    const DatePtr&                  resolved_date,
    const WeakInternalEmployee&     assigned_to,
    const WeakClientPtr&            related_client,
    std::vector<Note>               notes,
    std::vector<BaseInteractionPtr> related_interactions
)
    : id(id)
    , title(title)
    , description(description)
    , status(status)
    , priority(priority)
    , create_date(create_date)
    , resolved_date(resolved_date)
    , assigned_to(assigned_to)
    , related_client(related_client)
    , notes(std::move(notes))
    , related_interactions(std::move(related_interactions))
{
}
auto Case::getId() const -> const BigUint& { return this->id; }
auto Case::getTitle() const -> const std::string& { return this->title; }
auto Case::getDescription() const -> const OptionalStr& { return this->description; }
auto Case::getStatus() const -> CaseStatus { return this->status; }
auto Case::getPriority() const -> Priority { return this->priority; }
auto Case::getCreatedDate() const -> const Date& { return this->create_date; }
auto Case::getResolvedDate() const -> const DatePtr& { return this->resolved_date; }
auto Case::getAssignedTo() const -> const WeakInternalEmployee& { return this->assigned_to; }
auto Case::getRelatedClient() const -> const WeakClientPtr& { return this->related_client; }
auto Case::getNotes() const -> const std::vector<Note>& { return this->notes; }
auto Case::getRelatedInteractions() const -> const std::vector<BaseInteractionPtr>&
{
    return this->related_interactions;
}
auto Case::getChangeLogs() const -> const std::vector<ChangeLogPtr>& { return this->change_logs; }

bool Case::setTitle(const std::string& title, const InternalEmployeePtr& changer)
{
    if (this->title != title) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<std::string>(this->title)),
            std::make_optional(std::make_shared<std::string>(title)),
            CaseField::Title,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->title = title;
        return true;
    }
    return false;
}

bool Case::setDescription(const OptionalStr& description, const InternalEmployeePtr& changer)
{
    if (this->description != description) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->description),
            OPTIONAL_STR_TO_VALUE(description),
            CaseField::Description,
            this->description ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            description ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->description = description;
        return true;
    }
    return false;
}

bool Case::setStatus(const CaseStatus& status, const InternalEmployeePtr& changer)
{
    if (this->status != status) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->status),
            std::make_optional(status),
            CaseField::Status,
            ChangeLog::FieldType::CaseStatus,
            ChangeLog::FieldType::CaseStatus,
            ChangeLog::Action::Change
        ));
        this->status = status;
        return true;
    }
    return false;
}

bool Case::setPriority(const Priority& priority, const InternalEmployeePtr& changer)
{
    if (this->priority != priority) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->priority),
            std::make_optional(priority),
            CaseField::Priority,
            ChangeLog::FieldType::Priority,
            ChangeLog::FieldType::Priority,
            ChangeLog::Action::Change
        ));
        this->priority = priority;
        return true;
    }
    return false;
}

bool Case::setResolvedDate(const DatePtr& resolved_date, const InternalEmployeePtr& changer)
{
    if (this->resolved_date == nullptr || resolved_date == nullptr) {
        if (this->resolved_date == resolved_date) {
            return false;
        }
    } else if (*this->resolved_date == *resolved_date) {
        return false;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->resolved_date),
        PTR_TO_OPTIONAL(resolved_date),
        CaseField::ResolvedDate,
        this->resolved_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        resolved_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->resolved_date = resolved_date;
    return true;
}

bool Case::setAssignedTo(
    const WeakInternalEmployee& assigned_to, const InternalEmployeePtr& changer
)
{
    if (this->assigned_to.owner_before(assigned_to) ||
        assigned_to.owner_before(this->assigned_to)) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            WEAK_PTR_TO_OPTIONAL(this->assigned_to),
            WEAK_PTR_TO_OPTIONAL(assigned_to),
            CaseField::AssignedTo,
            !this->assigned_to.expired() ? ChangeLog::FieldType::WeakInternalEmployee
                                         : ChangeLog::FieldType::null,
            !assigned_to.expired() ? ChangeLog::FieldType::WeakInternalEmployee
                                   : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->assigned_to = assigned_to;
        return true;
    }
    return false;
}

bool Case::setRelatedClient(const WeakClientPtr& related_client, const InternalEmployeePtr& changer)
{
    if (this->related_client.owner_before(related_client) ||
        related_client.owner_before(this->related_client)) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            WEAK_PTR_TO_OPTIONAL(this->related_client),
            WEAK_PTR_TO_OPTIONAL(related_client),
            CaseField::RelatedClient,
            !this->related_client.expired() ? ChangeLog::FieldType::WeakClient
                                            : ChangeLog::FieldType::null,
            !related_client.expired() ? ChangeLog::FieldType::WeakClient
                                      : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->related_client = related_client;
        return true;
    }
    return false;
}

bool Case::addNote(const Note& note, const InternalEmployeePtr& changer)
{
    if (std::find(this->notes.begin(), this->notes.end(), note) == this->notes.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(std::make_shared<Note>(note)),
            CaseField::Notes,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Note,
            ChangeLog::Action::Add
        ));
        this->notes.push_back(note);
        return true;
    }
    return false;
}

bool Case::delNote(size_t index, const InternalEmployeePtr& changer)
{
    if (this->notes.size() > index) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<Note>(this->notes[index])),
            std::nullopt,
            CaseField::Notes,
            ChangeLog::FieldType::Note,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->notes.erase(this->notes.begin() + index);
        return true;
    }
    return false;
}

bool Case::addRelatedInteraction(
    const BaseInteractionPtr& interaction, const InternalEmployeePtr& changer
)
{
    if (std::find(
            this->related_interactions.begin(), this->related_interactions.end(), interaction
        ) == this->related_interactions.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(interaction),
            CaseField::RelatedInteractions,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::BaseInteraction,
            ChangeLog::Action::Add
        ));
        this->related_interactions.push_back(interaction);
        return true;
    }
    return false;
}

bool Case::delRelatedInteraction(size_t index, const InternalEmployeePtr& changer)
{
    if (this->related_interactions.size() > index) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->related_interactions[index]),
            std::nullopt,
            CaseField::RelatedInteractions,
            ChangeLog::FieldType::BaseInteraction,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->related_interactions.erase(this->related_interactions.begin() + index);
        return true;
    }
    return false;
}