#include "email_thread.hpp"

#include "change_log.hpp"

EmailThread::EmailThread(const BigUint& id) : BaseInteraction(id, InteractionType::emailThread) {}

EmailThread::EmailThread(
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
    std::vector<EmailLetterPtr>        letters,
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
          InteractionType::emailThread,
          std::move(tags),
          std::move(results),
          std::move(notes),
          std::move(more_data),
          std::move(related_interactions),
          std::move(attachment_files),
          std::move(participants)
      )
    , letters(std::move(letters))
    , clients(std::move(clients))
    , employees(std::move(employees))
{
}

auto EmailThread::getLetters() const -> const std::vector<EmailLetterPtr>& { return this->letters; }
auto EmailThread::getClients() const -> const std::vector<ClientPtr>& { return this->clients; }
auto EmailThread::getEmployees() const -> const std::vector<InternalEmployeePtr>&
{
    return this->employees;
}

void EmailThread::addLetter(const EmailLetterPtr& letter, const InternalEmployeePtr& changer)
{
    if (std::find(this->letters.begin(), this->letters.end(), letter) == this->letters.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(letter),
            EmailThreadFields::Letters,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::EmailLetter,
            ChangeLog::Action::Add
        ));
        this->letters.push_back(letter);
    }
}

void EmailThread::delLetter(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->letters.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->letters[id]),
            std::nullopt,
            EmailThreadFields::Letters,
            ChangeLog::FieldType::EmailLetter,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->letters.erase(this->letters.begin() + id);
    }
}

void EmailThread::addClient(const ClientPtr& client, const InternalEmployeePtr& changer)
{
    if (std::find(this->clients.begin(), this->clients.end(), client) == this->clients.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(client),
            EmailThreadFields::Clients,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Client,
            ChangeLog::Action::Add
        ));
        this->clients.push_back(client);
    }
}

void EmailThread::delClient(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->clients.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->clients[id]),
            std::nullopt,
            EmailThreadFields::Clients,
            ChangeLog::FieldType::Client,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->clients.erase(this->clients.begin() + id);
    }
}

void EmailThread::addEmployee(
    const InternalEmployeePtr& employee, const InternalEmployeePtr& changer
)
{
    if (std::find(this->employees.begin(), this->employees.end(), employee) ==
        this->employees.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(employee),
            EmailThreadFields::Employees,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::InternalEmployee,
            ChangeLog::Action::Add
        ));
        this->employees.push_back(employee);
    }
}

void EmailThread::delEmployee(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->employees.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->employees[id]),
            std::nullopt,
            EmailThreadFields::Employees,
            ChangeLog::FieldType::InternalEmployee,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->employees.erase(this->employees.begin() + id);
    }
}