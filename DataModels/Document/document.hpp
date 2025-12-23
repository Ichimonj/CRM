#pragma once
#include <memory>
#include <vector>

#include "big_uint.hpp"
#include "date.hpp"
#include "person.hpp"

class InternalEmployee;
class ChangeLog;
class FileMetadata;

using DatePtr             = std::shared_ptr<Date>;
using PersonPtr           = std::shared_ptr<Person>;
using ChangeLogPtr        = std::shared_ptr<ChangeLog>;
using InternalEmployeePtr = std::shared_ptr<InternalEmployee>;
using FilePtr             = std::shared_ptr<FileMetadata>;
struct Document {
public:
    enum DocumentStatus : uint8_t { Draft, Active, Expired, Archived, COUNT };

    Document(const BigUint& id);
    Document(
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
    );

public:
    /// @name Getters
    /// @{
    auto getId() const -> const BigUint&;
    auto getTitle() const -> const std::string&;
    auto getName() const -> const std::string&;
    auto getNumber() const -> const std::string&;
    auto getPath() const -> const std::string&;
    auto getEnteredForce() const -> const DatePtr&;
    auto getStoppedWorking() const -> const DatePtr&;
    auto getStatus() const -> DocumentStatus;
    auto getCreatedBy() const -> const InternalEmployeePtr&;
    auto getPartners() const -> const std::vector<PersonPtr>&;
    auto getFiles() const -> const std::vector<FilePtr>&;
    auto getChangeLogs() const -> const std::vector<ChangeLogPtr>&;
    ///@}

    /// @name Change functions
    /// @{
    bool setDocumentTitle(const std::string& title, const InternalEmployeePtr& changer);
    bool setDocumentName(const std::string& name, const InternalEmployeePtr& changer);
    bool setDocumentNumber(const std::string& number, const InternalEmployeePtr& changer);
    bool setDocumentPath(const std::string& path, const InternalEmployeePtr& changer);
    bool setEnteredForce(const DatePtr& date, const InternalEmployeePtr& changer);
    bool setStoppedWorking(const DatePtr& date, const InternalEmployeePtr& changer);
    bool setStatus(const DocumentStatus& status, const InternalEmployeePtr& changer);
    bool setCreatedBy(const InternalEmployeePtr& creator, const InternalEmployeePtr& changer);

    bool addPartner(const PersonPtr& partner, const InternalEmployeePtr& changer);
    bool delPartner(const size_t id, const InternalEmployeePtr& changer);

    bool addFile(const FilePtr& file, const InternalEmployeePtr& changer);
    bool delFile(const size_t id, const InternalEmployeePtr& changer);
    /// @}

public:
    bool operator<(const Document& other) const;

private:
    BigUint             id;
    std::string         external_id;
    std::string         title;
    std::string         name;
    std::string         number;
    std::string         path;
    DatePtr             entered_force;
    DatePtr             stopped_working;
    DocumentStatus      status;
    InternalEmployeePtr created_by;

    //
    std::vector<PersonPtr>    partners;
    std::vector<FilePtr>      attachment_files;
    std::vector<ChangeLogPtr> change_logs;
};