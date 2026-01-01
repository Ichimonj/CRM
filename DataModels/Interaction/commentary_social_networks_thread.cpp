#include "commentary_social_networks_thread.hpp"

#include "ChangeLog/change_log.hpp"

CommentarySocialNetworksThread::CommentarySocialNetworksThread(const BigUint& id)
    : BaseInteraction(id, InteractionType::commentarySocialNetworksThread)
{
}

CommentarySocialNetworksThread::CommentarySocialNetworksThread(
    const BigUint&                           id,
    const std::string&                       title,
    const OptionalStr&                       external_id,
    const OptionalStr&                       description,
    const OptionalStr&                       subject,
    const std::optional<TimeDuration>&       interaction_duration,
    const Priority&                          priority,
    const InternalEmployeePtr&               manager,
    const DatePtr&                           start_date,
    const DatePtr&                           end_date,
    const InternalEmployeePtr&               checker,
    std::vector<std::string>                 tags,
    std::vector<InteractionResult>           results,
    std::vector<Note>                        notes,
    std::vector<StringPair>                  more_data,
    std::vector<InteractionPtr>              related_interactions,
    std::vector<FilePtr>                     attachment_files,
    std::vector<PersonPtr>                   participants,
    std::vector<CommentarySocialNetworksPtr> comments
)
    : BaseInteraction(
          id,
          title,
          external_id,
          description,
          subject,
          interaction_duration,
          priority,
          manager,
          start_date,
          end_date,
          checker,
          InteractionType::commentarySocialNetworksThread,
          std::move(tags),
          std::move(results),
          std::move(notes),
          std::move(more_data),
          std::move(related_interactions),
          std::move(attachment_files),
          std::move(participants)
      )
    , comments(std::move(comments))
{
}

auto CommentarySocialNetworksThread::getComments() const
    -> const std::vector<CommentarySocialNetworksPtr>&
{
    return this->comments;
}

bool CommentarySocialNetworksThread::addComment(
    const CommentarySocialNetworksPtr& comment, const InternalEmployeePtr& changer
)
{
    if (std::find(this->comments.begin(), this->comments.end(), comment) == this->comments.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(comment),
            CommentarySocialNetworksThreadFields::Comments,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::CommentarySocialNetworks,
            ChangeLog::Action::Add
        ));
        this->comments.push_back(comment);
        return true;
    }
    return false;
}

bool CommentarySocialNetworksThread::delComment(const size_t id, const InternalEmployeePtr& changer)
{
    if (this->comments.size() > id) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->comments[id]),
            std::nullopt,
            CommentarySocialNetworksThreadFields::Comments,
            ChangeLog::FieldType::CommentarySocialNetworks,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->comments.erase(this->comments.begin() + id);
        return true;
    }
    return false;
}