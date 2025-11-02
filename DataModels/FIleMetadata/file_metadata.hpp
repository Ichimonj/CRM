#pragma once
#include <memory>
#include <string>
#include <vector>

#include "big_uint.hpp"
#include "date.hpp"

class ChangeLog;
class InternalEmployee;

using ChangeLogPtr = std::shared_ptr<ChangeLog>;

class FileMetadata {
public:
    FileMetadata(const BigUint& id);
    FileMetadata(
        const BigUint&     id,
        const std::string& fileName,
        const std::string& fileFormat,
        const std::string& filePath,
        const bool         fileSize,
        const Date         uploadDate
    );

    auto getId() const -> const BigUint&;
    auto getFileName() const -> const std::string&;
    auto getFileFormat() const -> const std::string&;
    auto getFilePath() const -> const std::string&;
    auto getFileSize() const -> const bool;
    auto getUploadDate() const -> const Date&;
    auto getChangeLogs() const -> const std::vector<ChangeLogPtr>&;
    auto getHach() const -> const std::string&;

    void setFileName(const std::string& file_name, const std::shared_ptr<InternalEmployee>& changer);
    void setFileFormat(const std::string& file_format, const std::shared_ptr<InternalEmployee>& changer);
    void setFilePath(const std::string& file_path, const std::shared_ptr<InternalEmployee>& changer);
    void setFileSize(const bool size, const std::shared_ptr<InternalEmployee>& changer);
    void setUploadDate(const Date& date, const std::shared_ptr<InternalEmployee>& changer);
    void calculateHash();

private:
    BigUint     id;
    std::string name;
    std::string format;
    std::string path;
    bool        size;
    Date        upload_date;
    std::string content_hash;

    //
    std::vector<ChangeLogPtr> change_logs;
};
