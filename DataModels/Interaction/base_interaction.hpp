#pragma once
#include <memory>
#include <optional>
#include <vector>

#include "big_uint.hpp"
#include "file_metadata.hpp"
#include "interaction_result.hpp"
#include "note.hpp"
#include "priority.hpp"
#include "time_duration.hpp"

class Person;
struct Date;
struct InteractionResult;
class ChangeLog;
class Campaign;

using DatePtr             = std::shared_ptr<Date>;
using InternalEmployeePtr = std::shared_ptr<InternalEmployee>;
using PersonPtr           = std::shared_ptr<Person>;
using InteractionPtr      = std::shared_ptr<BaseInteraction>;
using FilePtr             = std::shared_ptr<FileMetadata>;
using ChangeLogPtr        = std::shared_ptr<ChangeLog>;
using StringPair          = std::pair<std::string, std::string>;
using OptionalStr         = std::optional<std::string>;
using CampaignWPTR        = std::weak_ptr<Campaign>;
struct BaseInteraction {
    enum class InteractionType : uint8_t {
        phoneCall,
        emailLetter,
        emailThread,
        meeting,
        meetingThread,
        message,
        correspondence,
        commentarySocialNetworks,
        commentarySocialNetworksThread,
        unknown,
        COUNT
    };
    BaseInteraction(const BigUint& id, InteractionType type);

    BaseInteraction(
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
        const InteractionType&             type,
        std::vector<std::string>           tags,
        std::vector<InteractionResult>     results,
        std::vector<Note>                  notes,
        std::vector<StringPair>            more_data,
        std::vector<InteractionPtr>        related_interactions,
        std::vector<FilePtr>               attachment_files,
        std::vector<PersonPtr>             participants
    );
    virtual ~BaseInteraction() = default;

public:
    /// @name Getters
    /// @{
    auto getId() const -> const BigUint&;
    auto getTitle() const -> const std::string&;
    auto getExternalId() const -> const OptionalStr&;
    auto getDescription() const -> const OptionalStr&;
    auto getSubject() const -> const OptionalStr&;
    auto getInteractionDuration() const -> const std::optional<TimeDuration>&;
    auto getPriority() const -> Priority;
    auto getTags() const -> const std::vector<std::string>&;
    auto getResults() const -> const std::vector<InteractionResult>&;
    auto getManager() const -> const InternalEmployeePtr&;
    auto getNotes() const -> const std::vector<Note>&;
    auto getMoreData() const -> const std::vector<StringPair>&;
    auto getRelatedInteractions() const -> const std::vector<InteractionPtr>&;
    auto getAttachmentFiles() const -> const std::vector<FilePtr>&;
    auto getCreatedDate() const -> const Date&;
    auto getStartDate() const -> const DatePtr&;
    auto getEndDate() const -> const DatePtr&;
    auto getChecker() const -> const InternalEmployeePtr&;
    auto getParticipants() const -> const std::vector<PersonPtr>&;
    auto getType() const -> InteractionType;
    auto getChangeLogs() const -> const std::vector<ChangeLogPtr>&;
    /// @}

    /// @name Change functions
    /// @{
    bool setTitle(const std::string& title, const InternalEmployeePtr& changer);
    bool setExternalId(const OptionalStr& id, const InternalEmployeePtr& changer);
    bool setDescription(const OptionalStr& description, const InternalEmployeePtr& changer);
    bool setDuration(
        const std::optional<TimeDuration>& duration, const InternalEmployeePtr& changer
    );
    bool setPriority(const Priority& priority, const InternalEmployeePtr& changer);

    bool addTag(const std::string& tag, const InternalEmployeePtr& changer);
    bool delTag(const size_t index, const InternalEmployeePtr& changer);

    bool addResult(const InteractionResult& result, const InternalEmployeePtr& changer);
    bool delResult(const size_t index, const InternalEmployeePtr& changer);

    bool setManager(const InternalEmployeePtr& manager, const InternalEmployeePtr& changer);

    bool addNote(const Note& note, const InternalEmployeePtr& changer);
    bool delNote(const size_t index, const InternalEmployeePtr& changer);

    bool addMoreData(
        const std::string& title, const std::string& data, const InternalEmployeePtr& changer
    );
    bool delMoreData(const size_t index, const InternalEmployeePtr& changer);

    bool addRelatedInteractions(
        const InteractionPtr& interaction, const InternalEmployeePtr& changer
    );
    bool delRelatedInteractions(const size_t index, const InternalEmployeePtr& changer);

    bool addAttachmentFiles(const FilePtr& file, const InternalEmployeePtr& changer);
    bool delAttachmentFiles(const size_t index, const InternalEmployeePtr& changer);

    bool setSubject(const OptionalStr& subject, const InternalEmployeePtr& changer);
    bool setStartDate(const DatePtr& date, const InternalEmployeePtr& changer);
    bool setEndDate(const DatePtr& date, const InternalEmployeePtr& changer);
    bool setChecker(const InternalEmployeePtr& checker, const InternalEmployeePtr& changer);

    bool addParticipants(const PersonPtr& participant, const InternalEmployeePtr& changer);
    bool delParticipants(const size_t index, const InternalEmployeePtr& changer);

    bool addCampaign(const CampaignWPTR& campaign, const InternalEmployeePtr& changer);
    bool delCampaign(size_t index, const InternalEmployeePtr& changer);

    bool setType(const InteractionType& type, const InternalEmployeePtr& changer);
    /// @}

    void addChangeLog(const ChangeLogPtr& changeLog);

private:
    BigUint                        id;
    std::string                    title;
    OptionalStr                    external_id;
    OptionalStr                    description;
    OptionalStr                    subject;

    std::optional<TimeDuration>    interaction_duration;
    Date                           created_date = Date();
    DatePtr                        start_date;
    DatePtr                        end_date;

    InteractionType                type;
    Priority                       priority;
    std::vector<std::string>       tags;
    std::vector<StringPair>        more_data;

    InternalEmployeePtr            manager;
    InternalEmployeePtr            checker;
    std::vector<PersonPtr>         participants;

    std::vector<InteractionResult> results;
    std::vector<Note>              notes;

    std::vector<InteractionPtr>    related_interactions;
    std::vector<FilePtr>           attachment_files;

    std::vector<CampaignWPTR>      campaigns;

protected:
    std::vector<ChangeLogPtr> change_logs;
};