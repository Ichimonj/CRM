#include "task.hpp"

#include "change_log.hpp"
Task::Task(const BigUint& id) : id(id), priority(Priority::Medium), status(Status::NotStarted) {}

Task::Task(
    const BigUint&             id,
    const std::string&         title,
    const OptionalStr&         description,
    const OptionalStr&         subject,
    const Status&              status,
    const Priority&            priority,
    const DatePtr&             deadline,
    const DatePtr&             start_date,
    const DurationPtr&         ETC,
    const DurationPtr&         ATS,
    const InternalEmployeePtr& created_by,
    const InternalEmployeePtr& manager,
    std::vector<std::string>   notes,
    std::vector<StringPair>    more_data,
    std::vector<PersonPtr>     teem
)
    : id(id)
    , title(title)
    , description(description)
    , subject(subject)
    , status(status)
    , priority(priority)
    , deadline(deadline)
    , start_date(start_date)
    , ETC(ETC)
    , ATS(ATS)
    , created_by(created_by)
    , manager(manager)
    , notes(std::move(notes))
    , more_data(std::move(more_data))
    , teem(std::move(teem))
{
}

auto Task::getId() const -> const BigUint& { return id; }
auto Task::getTitle() const -> const std::string& { return title; }
auto Task::getDescription() const -> const OptionalStr& { return description; }
auto Task::getSubject() const -> const OptionalStr& { return subject; }
auto Task::getStatus() const -> const Status { return status; }
auto Task::getPriority() const -> const Priority { return priority; }
auto Task::getCreatedDate() const -> const Date& { return created_date; }
auto Task::getDeadline() const -> const DatePtr& { return deadline; }
auto Task::getStartDate() const -> const DatePtr& { return start_date; }
auto Task::getETC() const -> const DurationPtr& { return ETC; }
auto Task::getATS() const -> const DurationPtr& { return ATS; }
auto Task::getCreatedBy() const -> const InternalEmployeePtr& { return created_by; }
auto Task::getFiles() const -> const std::vector<FilePtr>& { return this->attachment_files; }
auto Task::getTasks() const -> const std::vector<TaskPtr>& { return this->attachment_tasks; }
auto Task::getManager() const -> const InternalEmployeePtr& { return manager; }
auto Task::getNotes() const -> const std::vector<std::string>& { return notes; }
auto Task::getMoreData() const -> const std::vector<StringPair>& { return more_data; }
auto Task::getTeem() const -> const std::vector<PersonPtr>& { return teem; }
auto Task::getChangeLogs() const -> const std::vector<ChangeLogPtr>& { return this->change_logs; }

void Task::setTitle(const std::string& title, const InternalEmployeePtr& changer)
{
    if (this->title != title) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<std::string>(this->title)),
            std::make_optional(std::make_shared<std::string>(title)),
            TaskFields::Title,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->title = title;
    }
}

void Task::setDescription(const OptionalStr& description, const InternalEmployeePtr& changer)
{
    if (this->description != description) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->description),
            OPTIONAL_STR_TO_VALUE(description),
            TaskFields::Description,
            this->description ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            description ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->description = description;
    }
}

void Task::setSubject(const OptionalStr& subject, const InternalEmployeePtr& changer)
{
    if (this->subject != subject) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->subject),
            OPTIONAL_STR_TO_VALUE(subject),
            TaskFields::Subject,
            this->subject ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            subject ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->subject = subject;
    }
}

void Task::setStatus(const Status& status, const InternalEmployeePtr& changer)
{
    if (this->status != status) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->status),
            std::make_optional(status),
            TaskFields::Status,
            ChangeLog::FieldType::TaskStatus,
            ChangeLog::FieldType::TaskStatus,
            ChangeLog::Action::Change
        ));
        this->status = status;
    }
}

void Task::setPriority(const Priority& priority, const InternalEmployeePtr& changer)
{
    if (this->priority != priority) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->priority),
            std::make_optional(priority),
            TaskFields::Priority,
            ChangeLog::FieldType::Priority,
            ChangeLog::FieldType::Priority,
            ChangeLog::Action::Change
        ));
        this->priority = priority;
    }
}

void Task::setDeadline(const DatePtr& deadline, const InternalEmployeePtr& changer)
{
    if (this->deadline == nullptr || deadline == nullptr) {
        if (this->deadline == deadline) {
            return;
        }
    } else if (*this->deadline == *deadline) {
        return;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->deadline),
        PTR_TO_OPTIONAL(deadline),
        TaskFields::Deadline,
        this->deadline ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        deadline ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->deadline = deadline;
}

void Task::setStartDate(const DatePtr& start_date, const InternalEmployeePtr& changer)
{
    if (this->start_date == nullptr || start_date == nullptr) {
        if (this->start_date == start_date) {
            return;
        }
    } else if (*this->start_date == *start_date) {
        return;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->start_date),
        PTR_TO_OPTIONAL(start_date),
        TaskFields::StartDate,
        this->start_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        start_date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->start_date = start_date;
}

void Task::setETC(const DurationPtr& ETC, const InternalEmployeePtr& changer)
{
    if (this->ETC == nullptr || ETC == nullptr) {
        if (this->ETC == ETC) {
            return;
        }
    } else if (*this->ETC == *ETC) {
        return;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->ETC),
        PTR_TO_OPTIONAL(ETC),
        TaskFields::ETC,
        this->ETC ? ChangeLog::FieldType::TimeDuration : ChangeLog::FieldType::null,
        ETC ? ChangeLog::FieldType::TimeDuration : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->ETC = ETC;
}

void Task::setATS(const DurationPtr& ATS, const InternalEmployeePtr& changer)
{
    if (this->ATS == nullptr || ATS == nullptr) {
        if (this->ATS == ATS) {
            return;
        }
    } else if (*this->ATS == *ATS) {
        return;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->ATS),
        PTR_TO_OPTIONAL(ATS),
        TaskFields::ATS,
        this->ATS ? ChangeLog::FieldType::TimeDuration : ChangeLog::FieldType::null,
        ATS ? ChangeLog::FieldType::TimeDuration : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->ATS = ATS;
}

void Task::setManager(const InternalEmployeePtr& manager, const InternalEmployeePtr& changer)
{
    if (this->manager != manager) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->manager),
            PTR_TO_OPTIONAL(manager),
            TaskFields::Manager,
            this->manager ? ChangeLog::FieldType::InternalEmployee : ChangeLog::FieldType::null,
            manager ? ChangeLog::FieldType::InternalEmployee : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->manager = manager;
    }
}
void Task::addTask(const TaskPtr& task, const InternalEmployeePtr& changer)
{
    if (std::find(this->attachment_tasks.begin(), this->attachment_tasks.end(), task) ==
        this->attachment_tasks.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(task),
            TaskFields::Task,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Task,
            ChangeLog::Action::Add
        ));
        this->attachment_tasks.push_back(task);
    }
}

void Task::delTask(size_t index, const InternalEmployeePtr& changer)
{
    if (this->attachment_tasks.size() > index) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->attachment_tasks[index]),
            std::nullopt,
            TaskFields::Task,
            ChangeLog::FieldType::Task,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->attachment_tasks.erase(this->attachment_tasks.begin() + index);
    }
}

void Task::addFile(const FilePtr& file, const InternalEmployeePtr& changer)
{
    if (std::find(this->attachment_files.begin(), this->attachment_files.end(), file) ==
        this->attachment_files.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(file),
            TaskFields::File,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::FileMetadata,
            ChangeLog::Action::Add
        ));
        this->attachment_files.push_back(file);
    }
}
void Task::delFile(size_t index, const InternalEmployeePtr& changer)
{
    if (this->attachment_files.size() > index) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->attachment_files[index]),
            std::nullopt,
            TaskFields::File,
            ChangeLog::FieldType::FileMetadata,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->attachment_files.erase(this->attachment_files.begin() + index);
    }
}

void Task::addNote(const std::string& note, const InternalEmployeePtr& changer)
{
    if (std::find(this->notes.begin(), this->notes.end(), note) == this->notes.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(std::make_shared<std::string>(note)),
            TaskFields::Notes,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Add
        ));
        this->notes.push_back(note);
    }
}

void Task::delNote(size_t index, const InternalEmployeePtr& changer)
{
    if (this->notes.size() > index) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<std::string>(this->notes[index])),
            std::nullopt,
            TaskFields::Notes,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->notes.erase(this->notes.begin() + index);
    }
}

void Task::addMoreData(
    const std::string& title, const std::string& data, const InternalEmployeePtr& changer
)
{
    auto pair = std::make_pair(title, data);

    if (std::find(this->more_data.begin(), this->more_data.end(), pair) == this->more_data.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(
                std::make_shared<std::pair<const std::string, const std::string>>(pair)
            ),
            TaskFields::MoreData,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::StringPair,
            ChangeLog::Action::Add
        ));
        this->more_data.push_back(pair);
    }
}

void Task::delMoreData(size_t index, const InternalEmployeePtr& changer)
{
    if (this->more_data.size() > index) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<std::pair<const std::string, const std::string>>(
                this->more_data[index]
            )),
            std::nullopt,
            TaskFields::MoreData,
            ChangeLog::FieldType::StringPair,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->more_data.erase(this->more_data.begin() + index);
    }
}

void Task::addTeemMember(const PersonPtr& member, const InternalEmployeePtr& changer)
{
    if (std::find(this->teem.begin(), this->teem.end(), member) == this->teem.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(member),
            TaskFields::Teem,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Person,
            ChangeLog::Action::Add
        ));
        this->teem.push_back(member);
    }
}

void Task::delTeemMember(size_t index, const InternalEmployeePtr& changer)
{
    if (this->teem.size() > index) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->teem[index]),
            std::nullopt,
            TaskFields::Teem,
            ChangeLog::FieldType::Person,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->teem.erase(this->teem.begin() + index);
    }
}