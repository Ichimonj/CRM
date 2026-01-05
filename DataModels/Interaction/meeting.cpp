#include "meeting.hpp"
#include "ChangeLog/change_log.hpp"
#include "Usings/type_usings.hpp"
Meeting::Meeting(const BigUint& id)
    : BaseInteraction(id, InteractionType::meeting)
    , is_confirmed(false)
    , is_virtual(false)
    , meeting_status(MeetingStatus::InProgress)
    , meeting_type(MeetingType::Presentation)
{
}

Meeting::Meeting(
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
    const AddressPtr&                  location,
    const MeetingStatus&               meeting_status,
    const MeetingType&                 meeting_type,
    std::vector<MeetingOutcome>        outcomes,
    std::vector<std::string>           other_outcomes,
    const std::string&                 other_type,
    const std::string&                 record,
    std::vector<ClientPtr>             clients,
    std::vector<InternalEmployeePtr>   employees,
    std::vector<PersonPtr>             invitees,
    const MeetingPtr&                  previous_meeting,
    const MeetingPtr&                  next_meeting,
    const Date&                        created_date,
    bool                               is_confirmed,
    bool                               is_virtual
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
          InteractionType::meeting,
          std::move(tags),
          std::move(results),
          std::move(notes),
          std::move(more_data),
          std::move(related_interactions),
          std::move(attachment_files),
          std::move(participants)
      )
    , location(location)
    , meeting_status(meeting_status)
    , meeting_type(meeting_type)
    , outcomes(std::move(outcomes))
    , other_outcomes(std::move(other_outcomes))
    , other_type(other_type)
    , record(record)
    , clients(std::move(clients))
    , employees(std::move(employees))
    , invitees(std::move(invitees))
    , previous_meeting(previous_meeting)
    , next_meeting(next_meeting)
    , created_date(created_date)
    , is_confirmed(is_confirmed)
    , is_virtual(is_virtual)
{
}

auto Meeting::getLocation() const -> const AddressPtr { return this->location; }
auto Meeting::getMeetingStatus() const -> MeetingStatus { return this->meeting_status; }
auto Meeting::getMeetingType() const -> MeetingType { return this->meeting_type; }
auto Meeting::getOutcomes() const -> const std::vector<MeetingOutcome>& { return this->outcomes; }
auto Meeting::getOtherOutcomes() const -> const std::vector<std::string>&
{
    return this->other_outcomes;
}
auto Meeting::getOtherType() const -> const std::string& { return this->other_type; }
auto Meeting::getRecord() const -> const std::string& { return this->record; }
auto Meeting::getClients() const -> const std::vector<ClientPtr>& { return this->clients; }
auto Meeting::getEmployees() const -> const std::vector<InternalEmployeePtr>&
{
    return this->employees;
}
auto Meeting::getInvitees() const -> const std::vector<PersonPtr>& { return this->invitees; }
auto Meeting::getPreviousMeeting() const -> const MeetingPtr { return this->previous_meeting; }
auto Meeting::getNextMeeting() const -> const MeetingPtr { return this->next_meeting; }
auto Meeting::getCreatedDate() const -> const Date& { return this->created_date; }
auto Meeting::getIsConfirmed() const -> bool { return this->is_confirmed; }
auto Meeting::getIsVirtual() const -> bool { return this->is_virtual; }

bool Meeting::setLocation(const AddressPtr& location, const InternalEmployeePtr& changer)
{
    if (this->location != location) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->location),
            PTR_TO_OPTIONAL(location),
            MeetingFields::Location,
            this->location ? ChangeLog::FieldType::Address : ChangeLog::FieldType::null,
            location ? ChangeLog::FieldType::Address : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->location = location;
        return true;
    }
    return false;
}

bool Meeting::setMeetingStatus(const MeetingStatus status, const InternalEmployeePtr& changer)
{
    if (this->meeting_status != status) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->meeting_status),
            std::make_optional<ChangeLog::ValueVariant>(status),
            MeetingFields::MeetingStatus,
            ChangeLog::FieldType::MeetingStatus,
            ChangeLog::FieldType::MeetingStatus,
            ChangeLog::Action::Change
        ));
        this->meeting_status = status;
        return true;
    }
    return false;
}

bool Meeting::setMeetingType(const MeetingType type, const InternalEmployeePtr& changer)
{
    if (this->meeting_type != type) {
        bool isOtherType = !this->other_type.empty();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            isOtherType ? std::make_optional<ChangeLog::ValueVariant>(
                              std::make_shared<std::string>(this->other_type)
                          )
                        : std::make_optional<ChangeLog::ValueVariant>(this->meeting_type),
            std::make_optional<ChangeLog::ValueVariant>(type),
            MeetingFields::MeetingType,
            isOtherType ? ChangeLog::FieldType::String : ChangeLog::FieldType::MeetingType,
            ChangeLog::FieldType::MeetingType,
            ChangeLog::Action::Change
        ));
        this->meeting_type = type;
        this->other_type.clear();
        return true;
    }
    return false;
}

bool Meeting::addOutcome(const MeetingOutcome outcome, const InternalEmployeePtr& changer)
{
    if (std::find(this->outcomes.begin(), this->outcomes.end(), outcome) == this->outcomes.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(outcome),
            MeetingFields::Outcomes,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::MeetingOutcome,
            ChangeLog::Action::Add
        ));
        this->outcomes.push_back(outcome);
        return true;
    }
    return false;
}

bool Meeting::delOutcome(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->outcomes.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->outcomes[id]),
            std::nullopt,
            MeetingFields::Outcomes,
            ChangeLog::FieldType::MeetingOutcome,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->outcomes.erase(this->outcomes.begin() + id);
        return true;
    }
    return false;
}

bool Meeting::addOtherOutcome(const std::string& outcome, const InternalEmployeePtr& changer)
{
    if (std::find(this->other_outcomes.begin(), this->other_outcomes.end(), outcome) ==
        this->other_outcomes.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(outcome)),
            MeetingFields::OtherOutcomes,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Add
        ));
        this->other_outcomes.push_back(outcome);
        return true;
    }
    return false;
}

bool Meeting::delOtherOutcome(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->other_outcomes.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<std::string>(this->other_outcomes[id])
            ),
            std::nullopt,
            MeetingFields::OtherOutcomes,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->other_outcomes.erase(this->other_outcomes.begin() + id);
        return true;
    }
    return false;
}

bool Meeting::setOtherType(const std::string& type, const InternalEmployeePtr& changer)
{
    if (this->other_type != type) {
        bool isOtherType = !this->other_type.empty();

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            isOtherType ? std::make_optional<ChangeLog::ValueVariant>(
                              std::make_shared<std::string>(this->other_type)
                          )
                        : std::make_optional<ChangeLog::ValueVariant>(this->meeting_type),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(type)),
            MeetingFields::MeetingType,
            isOtherType ? ChangeLog::FieldType::String : ChangeLog::FieldType::MeetingType,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->other_type   = type;
        this->meeting_type = MeetingType::Other;
        return true;
    }
    return false;
}

bool Meeting::setRecord(const std::string& record, const InternalEmployeePtr& changer)
{
    if (this->record != record) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(this->record)
            ),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(record)),
            MeetingFields::Record,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->record = record;
        return true;
    }
    return false;
}

bool Meeting::addClient(const ClientPtr& client, const InternalEmployeePtr& changer)
{
    if (std::find(this->clients.begin(), this->clients.end(), client) == this->clients.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(client),
            MeetingFields::Clients,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Client,
            ChangeLog::Action::Add
        ));
        this->clients.push_back(client);
        return true;
    }
    return false;
}

bool Meeting::delClient(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->clients.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->clients[id]),
            std::nullopt,
            MeetingFields::Clients,
            ChangeLog::FieldType::Client,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->clients.erase(this->clients.begin() + id);
        return true;
    }
    return false;
}

bool Meeting::addEmployee(const InternalEmployeePtr& employee, const InternalEmployeePtr& changer)
{
    if (std::find(this->employees.begin(), this->employees.end(), employee) ==
        this->employees.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(employee),
            MeetingFields::Employees,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::InternalEmployee,
            ChangeLog::Action::Add
        ));
        this->employees.push_back(employee);
        return true;
    }
    return false;
}

bool Meeting::delEmployee(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->employees.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->employees[id]),
            std::nullopt,
            MeetingFields::Employees,
            ChangeLog::FieldType::InternalEmployee,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->employees.erase(this->employees.begin() + id);
        return true;
    }
    return false;
}

bool Meeting::addInvitee(const PersonPtr& invitee, const InternalEmployeePtr& changer)
{
    if (std::find(this->invitees.begin(), this->invitees.end(), invitee) == this->invitees.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(invitee),
            MeetingFields::Invitees,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Person,
            ChangeLog::Action::Add
        ));
        this->invitees.push_back(invitee);
        return true;
    }
    return false;
}

bool Meeting::delInvitee(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->invitees.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->invitees[id]),
            std::nullopt,
            MeetingFields::Invitees,
            ChangeLog::FieldType::Person,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->invitees.erase(this->invitees.begin() + id);
        return true;
    }
    return false;
}

bool Meeting::setPreviousMeeting(const MeetingPtr& meeting, const InternalEmployeePtr& changer)
{
    if (this->previous_meeting != meeting) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->previous_meeting),
            PTR_TO_OPTIONAL(meeting),
            MeetingFields::PreviousMeeting,
            this->previous_meeting ? ChangeLog::FieldType::Meeting : ChangeLog::FieldType::null,
            meeting ? ChangeLog::FieldType::Meeting : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->previous_meeting = meeting;
        return true;
    }
    return false;
}

bool Meeting::setNextMeeting(const MeetingPtr& meeting, const InternalEmployeePtr& changer)
{
    if (this->next_meeting != meeting) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->next_meeting),
            PTR_TO_OPTIONAL(meeting),
            MeetingFields::NextMeeting,
            this->next_meeting ? ChangeLog::FieldType::Meeting : ChangeLog::FieldType::null,
            meeting ? ChangeLog::FieldType::Meeting : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->next_meeting = meeting;
        return true;
    }
    return false;
}

bool Meeting::setIsConfirmed(bool is_confirmed, const InternalEmployeePtr& changer)
{
    if (this->is_confirmed != is_confirmed) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->is_confirmed),
            std::make_optional<ChangeLog::ValueVariant>(is_confirmed),
            MeetingFields::IsConfirmed,
            ChangeLog::FieldType::Bool,
            ChangeLog::FieldType::Bool,
            ChangeLog::Action::Change
        ));
        this->is_confirmed = is_confirmed;
        return true;
    }
    return false;
}

bool Meeting::setIsVirtual(bool is_virtual, const InternalEmployeePtr& changer)
{
    if (this->is_virtual != is_virtual) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->is_virtual),
            std::make_optional<ChangeLog::ValueVariant>(is_virtual),
            MeetingFields::IsVirtual,
            ChangeLog::FieldType::Bool,
            ChangeLog::FieldType::Bool,
            ChangeLog::Action::Change
        ));
        this->is_virtual = is_virtual;
        return true;
    }
    return false;
}