#pragma once
#include <vector>

#include "BigNum/big_uint.hpp"
#include "DateTime/date.hpp"
#include "DateTime/time_duration.hpp"
#include "FileMetadata/file_metadata.hpp"
#include "Interaction/priority.hpp"
#include "Note/note.hpp"
#include "Usings/type_usings.hpp"

class Task {
public:
    enum class Status : uint8_t { NotStarted, InProgress, Completed, Overdue, COUNT };

    Task(const BigUint& id);
    Task(
        const BigUint&              id,
        const std::string&          title,
        const OptionalStr&          description,
        const OptionalStr&          subject,
        const Status&               status,
        const Priority&             priority,
        const DatePtr&              deadline,
        const DatePtr&              start_date,
        const DurationPtr&          ETC,
        const DurationPtr&          ATS,
        const WeakInternalEmployee& created_by,
        const WeakInternalEmployee& manager,
        std::vector<WeakDealPtr>    deals,
        std::vector<Note>           notes,
        std::vector<StringPair>     more_data,
        std::vector<WeakPersonPtr>  teem
    );

public:
    /// @name Getters
    /// @{
    auto getId() const -> const BigUint&;
    auto getTitle() const -> const std::string&;
    auto getDescription() const -> const OptionalStr&;
    auto getSubject() const -> const OptionalStr&;
    auto getStatus() const -> Status;
    auto getPriority() const -> Priority;
    auto getCreatedDate() const -> const Date&;
    auto getDeadline() const -> const DatePtr&;
    auto getStartDate() const -> const DatePtr&;
    auto getETC() const -> const DurationPtr&;
    auto getATS() const -> const DurationPtr&;
    auto getCreatedBy() const -> const WeakInternalEmployee&;
    auto getManager() const -> const WeakInternalEmployee&;
    auto getDeals() const -> const std::vector<WeakDealPtr>&;
    auto getFiles() const -> const std::vector<FilePtr>&;
    auto getTasks() const -> const std::vector<TaskPtr>&;
    auto getNotes() const -> const std::vector<Note>&;
    auto getMoreData() const -> const std::vector<StringPair>&;
    auto getTeem() const -> const std::vector<WeakPersonPtr>&;
    auto getChangeLogs() const -> const std::vector<ChangeLogPtr>&;
    /// @}

    /// @name Change functions
    /// @{
    bool setTitle(const std::string& title, const InternalEmployeePtr& changer);
    bool setDescription(const OptionalStr& description, const InternalEmployeePtr& changer);
    bool setSubject(const OptionalStr& subject, const InternalEmployeePtr& changer);
    bool setStatus(const Status& status, const InternalEmployeePtr& changer);
    bool setPriority(const Priority& priority, const InternalEmployeePtr& changer);
    bool setDeadline(const DatePtr& deadline, const InternalEmployeePtr& changer);
    bool setStartDate(const DatePtr& start_date, const InternalEmployeePtr& changer);
    bool setETC(const DurationPtr& ETC, const InternalEmployeePtr& changer);
    bool setATS(const DurationPtr& ATS, const InternalEmployeePtr& changer);
    bool setManager(const WeakInternalEmployee& weak_manager, const InternalEmployeePtr& changer);

    bool addDeal(const WeakDealPtr& deal, const InternalEmployeePtr& changer);
    bool delDeal(size_t index, const InternalEmployeePtr& changer);

    bool addTask(const TaskPtr& task, const InternalEmployeePtr& changer);
    bool delTask(size_t index, const InternalEmployeePtr& changer);

    bool addFile(const FilePtr& file, const InternalEmployeePtr& changer);
    bool delFile(size_t index, const InternalEmployeePtr& changer);

    bool addNote(const Note& note, const InternalEmployeePtr& changer);
    bool delNote(size_t index, const InternalEmployeePtr& changer);

    bool addMoreData(
        const std::string& title, const std::string& data, const InternalEmployeePtr& changer
    );
    bool delMoreData(size_t index, const InternalEmployeePtr& changer);

    bool addTeemMember(const WeakPersonPtr& member, const InternalEmployeePtr& changer);
    bool delTeemMember(size_t index, const InternalEmployeePtr& changer);
    /// @}

    /// @name Auxiliary functions
    /// @{
    void clearTeem();
    /// @}

private:
    BigUint              id;
    std::string          title;
    OptionalStr          description;
    OptionalStr          subject;
    Status               status;
    Priority             priority;

    Date                 created_date = Date();
    DatePtr              deadline;
    DatePtr              start_date;
    DurationPtr          ETC;  ///< Estimated Time of Completion
    DurationPtr          ATS;  ///< Actual Time Spent

    WeakInternalEmployee created_by;
    WeakInternalEmployee manager;

    //
    std::vector<WeakDealPtr>   deals;
    std::vector<TaskPtr>       attachment_tasks;
    std::vector<FilePtr>       attachment_files;
    std::vector<Note>          notes;
    std::vector<StringPair>    more_data;
    std::vector<WeakPersonPtr> teem;

    std::vector<ChangeLogPtr>  change_logs;
};
