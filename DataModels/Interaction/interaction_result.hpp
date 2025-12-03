#pragma once
#include <memory>
#include <string>
#include <vector>

#include "file_metadata.hpp"

struct Document;
struct Deal;
struct BaseInteraction;
struct Date;
class ChangeLog;
class InternalEmployee;

using DealPtr        = std::shared_ptr<Deal>;
using DocumentPtr    = std::shared_ptr<Document>;
using InteractionPtr = std::shared_ptr<BaseInteraction>;
using FilePtr        = std::shared_ptr<FileMetadata>;
using StringPair     = std::pair<std::string, std::string>;
using InternalEmployeePtr    = std::shared_ptr<InternalEmployee>;

struct InteractionResult {
    enum class ResultStatus : uint8_t {
        Success,
        Failure,
        PartialSuccess,
        FollowUpNeeded,
        Canceled,
        Postponed,
        IssueIdentified,
        NoOutcome,
        other,
        COUNT
    };

    InteractionResult() = default;
    InteractionResult(
        const std::string&          interaction_title,
        const std::string&          description,
        const ResultStatus          result_status,
        const std::string&          other_result_status,
        const std::string&          identified_issue,
        std::vector<DocumentPtr>    documents,
        std::vector<DealPtr>        deals,
        std::vector<InteractionPtr> planned_interactions,
        std::vector<FilePtr>        files,
        std::vector<StringPair>     more_data,
        std::vector<std::string>    tags
    );

public:
    /// @name Getters
    /// @{
    auto getTitle() const -> const std::string&;
    auto getDescription() const -> const std::string&;
    auto getDocuments() const -> const std::vector<DocumentPtr>&;
    auto getDeals() const -> const std::vector<DealPtr>&;
    auto getPlannedInteractions() const -> const std::vector<InteractionPtr>&;
    auto getFiles() const -> const std::vector<FilePtr>&;
    auto getResultStatus() const -> const ResultStatus;
    auto getOtherResultStatus() const -> const std::string&;
    auto getIdentifiedIssue() const -> const std::string&;
    auto getMoreData() const -> const std::vector<StringPair>&;
    auto getTags() const -> const std::vector<std::string>&;
    auto getChangeLogs() const -> const std::vector<ChangeLogPtr>&;
    /// @}

    /// @name Change functions
    /// @{
    void setInteractionResultTitle(const std::string& title, const InternalEmployeePtr& changer);
    void setDescription(const std::string& description, const InternalEmployeePtr& changer);

    void addDocument(const DocumentPtr& document, const InternalEmployeePtr& changer);
    void delDocument(const size_t id, const InternalEmployeePtr& changer);

    void addDeal(const DealPtr& deal, const InternalEmployeePtr& changer);
    void delDeal(const size_t id, const InternalEmployeePtr& changer);

    void addPlannedInteraction(const InteractionPtr& interaction, const InternalEmployeePtr& changer);
    void delPlannedInteraction(const size_t id, const InternalEmployeePtr& changer);

    void addFile(const FilePtr& file, const InternalEmployeePtr& changer);
    void delFile(const size_t id, const InternalEmployeePtr& changer);

    void setResultStatus(const ResultStatus result_status, const InternalEmployeePtr& changer);
    void setOtherResultStatus(const std::string& other_result_status, const InternalEmployeePtr& changer);

    void setIdentifiedIssue(const std::string& issue, const InternalEmployeePtr& changer);

    void addMoreData(const std::string& title, const std::string& data, const InternalEmployeePtr& changer);
    void delMoreData(const size_t id, const InternalEmployeePtr& changer);

    void addTag(const std::string& tag, const InternalEmployeePtr& changer);
    void delTag(const size_t id, const InternalEmployeePtr& changer);
    /// @}

private:
    Date                        create_date = Date();
    std::string                 interaction_result_title;
    std::string                 description;
    ResultStatus                result_status = ResultStatus::other;
    std::string                 other_result_status;

    std::vector<DocumentPtr>    documents;
    std::vector<DealPtr>        deals;
    std::vector<InteractionPtr> planned_interactions;

    std::vector<FilePtr>        files;

    std::string                 identified_issue;

    std::vector<std::string>    tags;
    std::vector<StringPair>     more_data;

    std::vector<ChangeLogPtr>   change_logs;
};