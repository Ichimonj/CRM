#include "meeting_thread.hpp"

#include "ChangeLog/change_log.hpp"

MeetingThread::MeetingThread(const BigUint& id)
    : BaseInteraction(id, InteractionType::meetingThread)
{
}

MeetingThread::MeetingThread(
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
    std::vector<MeetingPtr>            meetings,
    std::vector<ClientPtr>             clients,
    std::vector<InternalEmployeePtr>   employees
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
          InteractionType::meetingThread,
          std::move(tags),
          std::move(results),
          std::move(notes),
          std::move(more_data),
          std::move(related_interactions),
          std::move(attachment_files),
          std::move(participants)
      )
    , meetings(std::move(meetings))
    , clients(std::move(clients))
    , employees(std::move(employees))
{
}

auto MeetingThread::getMeetings() const -> const std::vector<MeetingPtr> { return this->meetings; }
auto MeetingThread::getClients() const -> const std::vector<ClientPtr> { return this->clients; }
auto MeetingThread::getEmployees() const -> const std::vector<InternalEmployeePtr>
{
    return this->employees;
}
bool MeetingThread::addMeeting(const MeetingPtr& meeting, const InternalEmployeePtr& changer)
{
    if (std::find(this->meetings.begin(), this->meetings.end(), meeting) == this->meetings.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(meeting),
            MeetingThreadFields::Meetings,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Meeting,
            ChangeLog::Action::Add
        ));
        this->meetings.push_back(meeting);
        return true;
    }
    return false;
}

bool MeetingThread::delMeeting(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->meetings.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->meetings[id]),
            std::nullopt,
            MeetingThreadFields::Meetings,
            ChangeLog::FieldType::Meeting,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->meetings.erase(this->meetings.begin() + id);
        return true;
    }
    return false;
}

bool MeetingThread::addClient(const ClientPtr& client, const InternalEmployeePtr& changer)
{
    if (std::find(this->clients.begin(), this->clients.end(), client) == this->clients.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(client),
            MeetingThreadFields::Clients,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Client,
            ChangeLog::Action::Add
        ));
        this->clients.push_back(client);
        return true;
    }
    return false;
}

bool MeetingThread::delClient(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->clients.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->clients[id]),
            std::nullopt,
            MeetingThreadFields::Clients,
            ChangeLog::FieldType::Client,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->clients.erase(this->clients.begin() + id);
        return true;
    }
    return false;
}

bool MeetingThread::addEmployee(
    const InternalEmployeePtr& employee, const InternalEmployeePtr& changer
)
{
    if (std::find(this->employees.begin(), this->employees.end(), employee) ==
        this->employees.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(employee),
            MeetingThreadFields::Employees,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::InternalEmployee,
            ChangeLog::Action::Add
        ));
        this->employees.push_back(employee);
        return true;
    }
    return false;
}

bool MeetingThread::delEmployee(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->employees.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->employees[id]),
            std::nullopt,
            MeetingThreadFields::Employees,
            ChangeLog::FieldType::InternalEmployee,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->employees.erase(this->employees.begin() + id);
        return true;
    }
    return false;
}