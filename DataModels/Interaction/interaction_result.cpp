#include "interaction_result.hpp"

#include "change_log.hpp"

InteractionResult::InteractionResult(
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
)
    : interaction_result_title(interaction_title)
    , description(description)
    , result_status(result_status)
    , other_result_status(other_result_status)
    , identified_issue(identified_issue)
    , documents(std::move(documents))
    , deals(std::move(deals))
    , planned_interactions(std::move(planned_interactions))
    , files(std::move(files))
    , more_data(std::move(more_data))
    , tags(std::move(tags))
{
}

auto InteractionResult::getTitle() const -> const std::string&
{
    return this->interaction_result_title;
}
auto InteractionResult::getDescription() const -> const std::string& { return this->description; }
auto InteractionResult::getDocuments() const -> const std::vector<DocumentPtr>&
{
    return this->documents;
}
auto InteractionResult::getDeals() const -> const std::vector<DealPtr>& { return this->deals; }
auto InteractionResult::getPlannedInteractions() const -> const std::vector<InteractionPtr>&
{
    return this->planned_interactions;
}
auto InteractionResult::getFiles() const -> const std::vector<FilePtr>& { return this->files; }
auto InteractionResult::getResultStatus() const -> const ResultStatus
{
    return this->result_status;
}
auto InteractionResult::getOtherResultStatus() const -> const std::string&
{
    return this->other_result_status;
}
auto InteractionResult::getIdentifiedIssue() const -> const std::string&
{
    return this->identified_issue;
}
auto InteractionResult::getMoreData() const -> const std::vector<StringPair>&
{
    return this->more_data;
}
auto InteractionResult::getTags() const -> const std::vector<std::string>& { return this->tags; }
auto InteractionResult::getChangeLogs() const -> const std::vector<ChangeLogPtr>&
{
    return this->change_logs;
}

void InteractionResult::setInteractionResultTitle(
    const std::string& title, const InternalEmployeePtr& changer
)
{
    if (this->interaction_result_title != title) {
        auto changeLog = std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<std::string>(this->interaction_result_title)
            ),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(title)),
            InteractionResultFields::InteractionResultTitle,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        );
        this->change_logs.emplace_back(changeLog);
        this->interaction_result_title = title;
    }
}

void InteractionResult::setDescription(const std::string& description, const InternalEmployeePtr& changer)
{
    if (this->description != description) {
        auto changeLog = std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<std::string>(this->description)
            ),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(description)),
            InteractionResultFields::Description,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        );
        this->change_logs.emplace_back(changeLog);
        this->description = description;
    }
}

void InteractionResult::addDocument(const DocumentPtr& document, const InternalEmployeePtr& changer)
{
    if (std::find(this->documents.begin(), this->documents.end(), document) ==
        this->documents.end()) {
        auto changeLog = std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(document),
            InteractionResultFields::Documents,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Document,
            ChangeLog::Action::Add
        );
        this->change_logs.emplace_back(changeLog);
        this->documents.push_back(document);
    }
}

void InteractionResult::delDocument(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->documents.size() > id) {
        auto changeLog = std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->documents[id]),
            std::nullopt,
            InteractionResultFields::Documents,
            ChangeLog::FieldType::Document,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        );
        this->change_logs.emplace_back(changeLog);
        this->documents.erase(this->documents.begin() + id);
    }
}

void InteractionResult::addDeal(const DealPtr& deal, const InternalEmployeePtr& changer)
{
    if (std::find(this->deals.begin(), this->deals.end(), deal) == this->deals.end()) {
        auto changeLog = std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(deal),
            InteractionResultFields::Deals,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Deal,
            ChangeLog::Action::Add
        );
        this->change_logs.emplace_back(changeLog);
        this->deals.push_back(deal);
    }
}

void InteractionResult::delDeal(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->deals.size() > id) {
        auto changeLog = std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->deals[id]),
            std::nullopt,
            InteractionResultFields::Deals,
            ChangeLog::FieldType::Deal,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        );
        this->change_logs.emplace_back(changeLog);
        this->deals.erase(this->deals.begin() + id);
    }
}

void InteractionResult::addPlannedInteraction(
    const InteractionPtr& interaction, const InternalEmployeePtr& changer
)
{
    if (std::find(
            this->planned_interactions.begin(), this->planned_interactions.end(), interaction
        ) == this->planned_interactions.end()) {
        auto changeLog = std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(interaction),
            InteractionResultFields::PlannedInteractions,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::BaseInteraction,
            ChangeLog::Action::Add
        );
        this->change_logs.emplace_back(changeLog);
        this->planned_interactions.push_back(interaction);
    }
}

void InteractionResult::delPlannedInteraction(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->planned_interactions.size() > id) {
        auto changeLog = std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->planned_interactions[id]),
            std::nullopt,
            InteractionResultFields::PlannedInteractions,
            ChangeLog::FieldType::BaseInteraction,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        );
        this->change_logs.emplace_back(changeLog);
        this->planned_interactions.erase(this->planned_interactions.begin() + id);
    }
}

void InteractionResult::addFile(const FilePtr& file, const InternalEmployeePtr& changer)
{
    if (std::find(this->files.begin(), this->files.end(), file) == this->files.end()) {
        auto changeLog = std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(file),
            InteractionResultFields::Files,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::FileMetadata,
            ChangeLog::Action::Add
        );
        this->change_logs.emplace_back(changeLog);
        this->files.push_back(file);
    }
}

void InteractionResult::delFile(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->files.size() > id) {
        auto changeLog = std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->files[id]),
            std::nullopt,
            InteractionResultFields::Files,
            ChangeLog::FieldType::FileMetadata,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        );
        this->change_logs.emplace_back(changeLog);
        this->files.erase(this->files.begin() + id);
    }
}

void InteractionResult::setResultStatus(
    const ResultStatus result_status, const InternalEmployeePtr& changer
)
{
    if (this->result_status != result_status) {
        bool isOther = !this->other_result_status.empty();

        auto changeLog = std::make_shared<ChangeLog>(
            changer,
            isOther ? std::make_optional<ChangeLog::ValueVariant>(
                          std::make_shared<std::string>(this->other_result_status)
                      )
                    : std::make_optional<ChangeLog::ValueVariant>(this->result_status),
            std::make_optional<ChangeLog::ValueVariant>(result_status),
            InteractionResultFields::ResultStatus,
            isOther ? ChangeLog::FieldType::String : ChangeLog::FieldType::ResultStatus,
            ChangeLog::FieldType::ResultStatus,
            ChangeLog::Action::Change
        );
        this->change_logs.emplace_back(changeLog);
        this->other_result_status.clear();
        this->result_status = result_status;
    }
}

void InteractionResult::setOtherResultStatus(
    const std::string& other_result_status, const InternalEmployeePtr& changer
)
{
    if (this->other_result_status != other_result_status) {
        bool isOther = !this->other_result_status.empty();

        auto changeLog = std::make_shared<ChangeLog>(
            changer,
            isOther ? std::make_optional<ChangeLog::ValueVariant>(
                          std::make_shared<std::string>(this->other_result_status)
                      )
                    : std::make_optional<ChangeLog::ValueVariant>(this->result_status),
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<std::string>(other_result_status)
            ),
            InteractionResultFields::ResultStatus,
            isOther ? ChangeLog::FieldType::String : ChangeLog::FieldType::ResultStatus,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        );
        this->change_logs.emplace_back(changeLog);
        this->result_status       = ResultStatus::other;
        this->other_result_status = other_result_status;
    }
}

void InteractionResult::setIdentifiedIssue(const std::string& issue, const InternalEmployeePtr& changer)
{
    if (this->identified_issue != issue) {
        auto changeLog = std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<std::string>(this->identified_issue)
            ),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(issue)),
            InteractionResultFields::IdentifiedIssue,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        );
        this->change_logs.emplace_back(changeLog);
        this->identified_issue = issue;
    }
}

void InteractionResult::addMoreData(
    const std::string& title, const std::string& data, const InternalEmployeePtr& changer
)
{
    auto pair = std::make_pair(title, data);
    if (std::find(this->more_data.begin(), this->more_data.end(), pair) == this->more_data.end()) {
        auto changeLog = std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<std::pair<const std::string, const std::string>>(pair)
            ),
            InteractionResultFields::MoreData,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::StringPair,
            ChangeLog::Action::Add
        );
        this->change_logs.emplace_back(changeLog);
        this->more_data.push_back(pair);
    }
}

void InteractionResult::delMoreData(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->more_data.size() > id) {
        auto changeLog = std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<std::pair<const std::string, const std::string>>(
                    this->more_data[id]
                )
            ),
            std::nullopt,
            InteractionResultFields::MoreData,
            ChangeLog::FieldType::StringPair,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        );
        this->change_logs.emplace_back(changeLog);
        this->more_data.erase(this->more_data.begin() + id);
    }
}

void InteractionResult::addTag(const std::string& tag, const InternalEmployeePtr& changer)
{
    if (std::find(this->tags.begin(), this->tags.end(), tag) == this->tags.end()) {
        auto changeLog = std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(tag)),
            InteractionResultFields::Tags,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Add
        );
        this->change_logs.emplace_back(changeLog);
        this->tags.push_back(tag);
    }
}

void InteractionResult::delTag(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->tags.size() > id) {
        auto changeLog = std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(this->tags[id]
            )),
            std::nullopt,
            InteractionResultFields::Tags,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        );
        this->change_logs.emplace_back(changeLog);
        this->tags.erase(this->tags.begin() + id);
    }
}