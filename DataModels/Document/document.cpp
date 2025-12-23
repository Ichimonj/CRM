#include "document.hpp"

#include <cstring>

#include "change_log.hpp"

Document::Document(const BigUint& id) : id(id), status(DocumentStatus::Draft) {}

Document::Document(
    const BigUint&             id,
    const std::string&         externalId,
    const std::string&         documentTitle,
    const std::string&         documentName,
    const std::string&         documentNumber,
    const std::string&         path,
    const DatePtr&             enteredForce,
    const DatePtr&             stoppedWorking,
    const DocumentStatus&      status,
    const InternalEmployeePtr& createdBy,
    std::vector<PersonPtr>     partners,
    std::vector<FilePtr>       attachmentFiles
)
    : id(id)
    , external_id(externalId)
    , title(documentTitle)
    , name(documentName)
    , number(documentNumber)
    , path(path)
    , entered_force(enteredForce)
    , stopped_working(stoppedWorking)
    , status(status)
    , created_by(createdBy)
    , partners(std::move(partners))
    , attachment_files(std::move(attachmentFiles))
{
}

auto Document::getId() const -> const BigUint& { return this->id; }
auto Document::getTitle() const -> const std::string& { return this->title; }
auto Document::getName() const -> const std::string& { return this->name; }
auto Document::getNumber() const -> const std::string& { return this->number; }
auto Document::getPath() const -> const std::string& { return this->path; }
auto Document::getEnteredForce() const -> const DatePtr& { return this->entered_force; }
auto Document::getStoppedWorking() const -> const DatePtr& { return this->stopped_working; }
auto Document::getStatus() const -> DocumentStatus { return this->status; }
auto Document::getCreatedBy() const -> const InternalEmployeePtr& { return this->created_by; }
auto Document::getPartners() const -> const std::vector<PersonPtr>& { return this->partners; }
auto Document::getFiles() const -> const std::vector<FilePtr>& { return this->attachment_files; }
auto Document::getChangeLogs() const -> const std::vector<ChangeLogPtr>&
{
    return this->change_logs;
}

bool Document::setDocumentTitle(const std::string& title, const InternalEmployeePtr& changer)
{
    if (this->title != title) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(this->title)),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(title)),
            DocumentFields::DocumentTitle,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->title = title;
        return true;
    }
    return false;
}

bool Document::setDocumentName(const std::string& name, const InternalEmployeePtr& changer)
{
    if (this->name != name) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(this->name)),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(name)),
            DocumentFields::DocumentName,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->name = name;
        return true;
    }
    return false;
}

bool Document::setDocumentNumber(const std::string& number, const InternalEmployeePtr& changer)
{
    if (this->number != number) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(this->number)
            ),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(number)),
            DocumentFields::DocumentNumber,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->number = number;
        return true;
    }
    return false;
}

bool Document::setDocumentPath(const std::string& path, const InternalEmployeePtr& changer)
{
    if (this->path != path) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(this->path)),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(path)),
            DocumentFields::DocumentPath,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->path = path;
        return true;
    }
    return false;
}

bool Document::setEnteredForce(const DatePtr& date, const InternalEmployeePtr& changer)
{
    if (this->entered_force == nullptr || date == nullptr) {
        if (this->entered_force == date) {
            return false;
        }
    } else if (*this->entered_force == *date) {
        return false;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->entered_force),
        PTR_TO_OPTIONAL(date),
        DocumentFields::EnteredForce,
        this->entered_force ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->entered_force = date;
    return true;
}

bool Document::setStoppedWorking(const DatePtr& date, const InternalEmployeePtr& changer)
{
    if (this->stopped_working == nullptr || date == nullptr) {
        if (this->stopped_working == date) {
            return false;
        }
    } else if (*this->stopped_working == *date) {
        return false;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->stopped_working),
        PTR_TO_OPTIONAL(date),
        DocumentFields::StoppedWorking,
        this->stopped_working ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        date ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->stopped_working = date;
    return true;
}

bool Document::setStatus(const DocumentStatus& status, const InternalEmployeePtr& changer)
{
    if (this->status != status) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->status),
            std::make_optional<ChangeLog::ValueVariant>(status),
            DocumentFields::Status,
            ChangeLog::FieldType::DocumentStatus,
            ChangeLog::FieldType::DocumentStatus,
            ChangeLog::Action::Change
        ));
        this->status = status;
        return true;
    }
    return false;
}

bool Document::setCreatedBy(const InternalEmployeePtr& creator, const InternalEmployeePtr& changer)
{
    if (this->created_by != creator) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->created_by),
            PTR_TO_OPTIONAL(creator),
            DocumentFields::Creator,
            this->created_by ? ChangeLog::FieldType::InternalEmployee : ChangeLog::FieldType::null,
            creator ? ChangeLog::FieldType::InternalEmployee : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->created_by = creator;
        return true;
    }
    return false;
}

bool Document::addPartner(const PersonPtr& partner, const InternalEmployeePtr& changer)
{
    if (std::find(this->partners.begin(), this->partners.end(), partner) == this->partners.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(partner),
            DocumentFields::Partners,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Person,
            ChangeLog::Action::Add
        ));
        this->partners.push_back(partner);
        return true;
    }
    return false;
}

bool Document::delPartner(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->partners.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->partners[id]),
            std::nullopt,
            DocumentFields::Partners,
            ChangeLog::FieldType::Person,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->partners.erase(this->partners.begin() + id);
        return true;
    }
    return false;
}

bool Document::addFile(const FilePtr& file, const InternalEmployeePtr& changer)
{
    if (std::find(this->attachment_files.begin(), this->attachment_files.end(), file) ==
        this->attachment_files.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(file),
            DocumentFields::File,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::FileMetadata,
            ChangeLog::Action::Add
        ));
        this->attachment_files.push_back(file);
        return true;
    }
    return false;
}

bool Document::delFile(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->attachment_files.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->attachment_files[id]),
            std::nullopt,
            DocumentFields::File,
            ChangeLog::FieldType::FileMetadata,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->attachment_files.erase(this->attachment_files.begin() + id);
        return true;
    }
    return false;
}

bool Document::operator<(const Document& other) const
{
    std::string first = other.number.substr(other.number.find_first_not_of('0'));
    std::string last  = this->number.substr(this->number.find_first_not_of('0'));

    if (first.size() > last.size())
        return true;
    else if (first.size() < last.size())
        return false;

    int a = strcmp(first.c_str(), last.c_str());
    if (a > 0) return true;
    return false;
}