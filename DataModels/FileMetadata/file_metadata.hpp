#pragma once
#include <vector>

#include "BigNum/big_uint.hpp"
#include "DateTime/date.hpp"
#include "Usings/type_usings.hpp"

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
    auto getFileSize() const -> bool;
    auto getUploadDate() const -> const Date&;
    auto getChangeLogs() const -> const std::vector<ChangeLogPtr>&;
    auto getHach() const -> const std::string&;

    bool setFileName(
        const std::string& file_name, const std::shared_ptr<InternalEmployee>& changer
    );
    bool setFileFormat(
        const std::string& file_format, const std::shared_ptr<InternalEmployee>& changer
    );
    bool setFilePath(
        const std::string& file_path, const std::shared_ptr<InternalEmployee>& changer
    );
    bool setFileSize(const bool size, const std::shared_ptr<InternalEmployee>& changer);
    bool setUploadDate(const Date& date, const std::shared_ptr<InternalEmployee>& changer);
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
