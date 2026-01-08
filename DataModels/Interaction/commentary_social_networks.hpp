#pragma once
#include "DateTime/date.hpp"
#include "base_interaction.hpp"

struct CommentarySocialNetworks : public BaseInteraction {
public:
    CommentarySocialNetworks(const BigUint& id);

    CommentarySocialNetworks(
        const BigUint&                     id,
        const std::string&                 title,
        const OptionalStr&                 external_id,
        const OptionalStr&                 description,
        const OptionalStr&                 subject,
        const std::optional<TimeDuration>& interaction_duration,
        const Priority&                    priority,
        const WeakInternalEmployee&        manager,
        const DatePtr&                     start_date,
        const DatePtr&                     end_date,
        const WeakInternalEmployee&        checker,
        const InteractionType&             type,
        std::vector<std::string>           tags,
        std::vector<InteractionResult>     results,
        std::vector<Note>                  notes,
        std::vector<StringPair>            more_data,
        std::vector<InteractionPtr>        related_interactions,
        std::vector<FilePtr>               attachment_files,
        std::vector<WeakPersonPtr>         participants,
        const std::string&                 nickname,
        const PersonPtr&                   author,
        const std::string&                 commentary,
        const CommentarySocialNetworksPtr& answer_to,
        const CommentarySocialNetworksPtr& answer,
        const Date&                        date_sending,
        bool                               is_first
    );

    /// @name Getters
    /// @{
    auto getNickname() const -> const std::string&;
    auto getAuthor() const -> const PersonPtr;
    auto getCommentary() const -> const std::string&;
    auto getAnswerTo() const -> const CommentarySocialNetworksPtr;
    auto getAnswer() const -> const CommentarySocialNetworksPtr;
    auto getDateSending() const -> const Date&;
    auto getIsFirst() const -> bool;
    /// @}

    /// @name Change functions
    /// @{
    bool setNickname(const std::string& nickname, const InternalEmployeePtr& changer);
    bool setAuthor(const PersonPtr& author, const InternalEmployeePtr& changer);
    bool setCommentary(const std::string& commentary, const InternalEmployeePtr& changer);
    bool setAnswerTo(
        const CommentarySocialNetworksPtr& answer_to, const InternalEmployeePtr& changer
    );
    bool setAnswer(const CommentarySocialNetworksPtr& answer, const InternalEmployeePtr& changer);
    bool setDateSending(const Date& date, const InternalEmployeePtr& changer);
    bool setIsFirst(bool first, const InternalEmployeePtr& changer);
    /// @}

private:
    std::string                 nickname;
    PersonPtr                   author;
    std::string                 commentary;

    CommentarySocialNetworksPtr answer_to;
    CommentarySocialNetworksPtr answer;
    Date                        date_sending;
    bool                        is_first;
};