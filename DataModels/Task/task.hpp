#pragma once
#include <memory>
#include <optional>
#include <vector>

#include "big_uint.hpp"
#include "date.hpp"
#include "file_metadata.hpp"
#include "priority.hpp"
#include "time_duration.hpp"
class ChangeLog;
class InternalEmployee;
class Person;
class Task;
class FileMetadata;
using TaskPtr             = std::shared_ptr<Task>;
using ChangeLogPtr        = std::shared_ptr<ChangeLog>;
using OptionalStr         = std::optional<std::string>;
using DatePtr             = std::shared_ptr<Date>;
using DurationPtr         = std::shared_ptr<TimeDuration>;
using InternalEmployeePtr = std::shared_ptr<InternalEmployee>;
using PersonPtr           = std::shared_ptr<Person>;
using StringPair          = std::pair<std::string, std::string>;
using FilePtr             = std::shared_ptr<FileMetadata>;

class Task {
public:
    enum class Status : uint8_t { NotStarted, InProgress, Completed, Overdue, COUNT };

    Task(const BigUint& id);
    Task(
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
    );

public:
    /// @name Getters
    /// @{
    auto getId() const -> const BigUint&;
    auto getTitle() const -> const std::string&;
    auto getDescription() const -> const OptionalStr&;
    auto getSubject() const -> const OptionalStr&;
    auto getStatus() const -> const Status;
    auto getPriority() const -> const Priority;
    auto getCreatedDate() const -> const Date&;
    auto getDeadline() const -> const DatePtr&;
    auto getStartDate() const -> const DatePtr&;
    auto getETC() const -> const DurationPtr&;
    auto getATS() const -> const DurationPtr&;
    auto getCreatedBy() const -> const InternalEmployeePtr&;
    auto getManager() const -> const InternalEmployeePtr&;
    auto getFiles() const -> const std::vector<FilePtr>&;
    auto getTasks() const -> const std::vector<TaskPtr>&;
    auto getNotes() const -> const std::vector<std::string>&;
    auto getMoreData() const -> const std::vector<StringPair>&;
    auto getTeem() const -> const std::vector<PersonPtr>&;
    auto getChangeLogs() const -> const std::vector<ChangeLogPtr>&;
    /// @}

    /// @name Change functions
    /// @{
    void setTitle(const std::string& title, const InternalEmployeePtr& changer);
    void setDescription(const OptionalStr& description, const InternalEmployeePtr& changer);
    void setSubject(const OptionalStr& subject, const InternalEmployeePtr& changer);
    void setStatus(const Status& status, const InternalEmployeePtr& changer);
    void setPriority(const Priority& priority, const InternalEmployeePtr& changer);
    void setDeadline(const DatePtr& deadline, const InternalEmployeePtr& changer);
    void setStartDate(const DatePtr& start_date, const InternalEmployeePtr& changer);
    void setETC(const DurationPtr& ETC, const InternalEmployeePtr& changer);
    void setATS(const DurationPtr& ATS, const InternalEmployeePtr& changer);
    void setManager(const InternalEmployeePtr& manager, const InternalEmployeePtr& changer);

    void addTask(const TaskPtr& task, const InternalEmployeePtr& changer);
    void delTask(size_t index, const InternalEmployeePtr& changer);

    void addFile(const FilePtr& file, const InternalEmployeePtr& changer);
    void delFile(size_t index, const InternalEmployeePtr& changer);

    void addNote(const std::string& note, const InternalEmployeePtr& changer);
    void delNote(size_t index, const InternalEmployeePtr& changer);

    void addMoreData(
        const std::string& title, const std::string& data, const InternalEmployeePtr& changer
    );
    void delMoreData(size_t index, const InternalEmployeePtr& changer);

    void addTeemMember(const PersonPtr& member, const InternalEmployeePtr& changer);
    void delTeemMember(size_t index, const InternalEmployeePtr& changer);
    /// @}

private:
    BigUint             id;
    std::string         title;
    OptionalStr         description;
    OptionalStr         subject;
    Status              status;
    Priority            priority;

    Date                created_date = Date();
    DatePtr             deadline;
    DatePtr             start_date;
    DurationPtr         ETC;  ///< Estimated Time of Completion
    DurationPtr         ATS;  ///< Actual Time Spent

    InternalEmployeePtr created_by;
    InternalEmployeePtr manager;

    //
    std::vector<TaskPtr>      attachment_tasks;
    std::vector<FilePtr>      attachment_files;
    std::vector<std::string>  notes;
    std::vector<StringPair>   more_data;
    std::vector<PersonPtr>    teem;

    std::vector<ChangeLogPtr> change_logs;
};
