#include "file_metadata.hpp"

#include "ChangeLog/change_log.hpp"

FileMetadata::FileMetadata(const BigUint& id) : id(id) {}

FileMetadata::FileMetadata(
    const BigUint&     id,
    const std::string& fileName,
    const std::string& fileFormat,
    const std::string& filePath,
    const bool         fileSize,
    const Date         uploadDate
)
    : id(id)
    , name(fileName)
    , format(fileFormat)
    , path(filePath)
    , size(fileSize)
    , upload_date(uploadDate)
{
}

auto FileMetadata::getId() const -> const BigUint& { return this->id; }
auto FileMetadata::getFileName() const -> const std::string& { return this->name; }
auto FileMetadata::getFileFormat() const -> const std::string& { return this->format; }
auto FileMetadata::getFilePath() const -> const std::string& { return this->path; }
auto FileMetadata::getFileSize() const -> bool { return this->size; }
auto FileMetadata::getUploadDate() const -> const Date& { return this->upload_date; }
auto FileMetadata::getChangeLogs() const -> const std::vector<ChangeLogPtr>&
{
    return this->change_logs;
}
auto FileMetadata::getHach() const -> const std::string& { return this->content_hash; }

bool FileMetadata::setFileName(
    const std::string& file_name, const std::shared_ptr<InternalEmployee>& changer
)
{
    if (this->name != file_name) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(this->name)),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(file_name)),
            FileMetadataFields::FileName,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->name = file_name;
        return true;
    }
    return false;
}

bool FileMetadata::setFileFormat(
    const std::string& file_format, const std::shared_ptr<InternalEmployee>& changer
)
{
    if (this->format != file_format) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(this->format)
            ),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(file_format)),
            FileMetadataFields::FileFormat,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->format = file_format;
        return true;
    }
    return false;
}

bool FileMetadata::setFilePath(
    const std::string& file_path, const std::shared_ptr<InternalEmployee>& changer
)
{
    if (this->path != file_path) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(this->path)),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(file_path)),
            FileMetadataFields::FilePath,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->path = file_path;
        return true;
    }
    return false;
}

bool FileMetadata::setFileSize(const bool size, const std::shared_ptr<InternalEmployee>& changer)
{
    if (this->size != size) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->size),
            std::make_optional<ChangeLog::ValueVariant>(size),
            FileMetadataFields::FileSize,
            ChangeLog::FieldType::Uint,
            ChangeLog::FieldType::Uint,
            ChangeLog::Action::Change
        ));
        this->size = size;
        return true;
    }
    return false;
}

bool FileMetadata::setUploadDate(const Date& date, const std::shared_ptr<InternalEmployee>& changer)
{
    if (this->upload_date != date) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<Date>(this->upload_date)),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<Date>(date)),
            FileMetadataFields::UploadDate,
            ChangeLog::FieldType::Date,
            ChangeLog::FieldType::Date,
            ChangeLog::Action::Change
        ));
        this->upload_date = date;
        return true;
    }
    return false;
}