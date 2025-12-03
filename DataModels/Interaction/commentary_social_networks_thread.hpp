#pragma once
#include "base_interaction.hpp"

struct CommentarySocialNetworks;
using CommentarySocialNetworksPtr = std::shared_ptr<CommentarySocialNetworks>;

struct CommentarySocialNetworksThread : public BaseInteraction {
    CommentarySocialNetworksThread(const BigUint& id);
    CommentarySocialNetworksThread(
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
    );

public:
    /// @name Getter
    /// @{
    auto getComments() const -> const std::vector<CommentarySocialNetworksPtr>&;
    /// @}

    /// @name Change functions
    /// @{
    void addComment(const CommentarySocialNetworksPtr& comment, const InternalEmployeePtr& changer);
    void delComment(const size_t id, const InternalEmployeePtr& changer);
    /// @}

private:
    std::vector<CommentarySocialNetworksPtr> comments;
};