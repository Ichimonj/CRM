#pragma once
#include "DateTime/date.hpp"
#include "base_interaction.hpp"

struct Message : public BaseInteraction {
    Message(const BigUint& id);
    Message(
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
        const WeakPersonPtr&               author,
        const std::string&                 message,
        const std::string&                 platform,
        const Date&                        date_sending
    );

    /// @name Getters
    /// @{
    auto getNickname() const -> const std::string&;
    auto getAuthor() const -> const WeakPersonPtr&;
    auto getMessage() const -> const std::string&;
    auto getPlatform() const -> const std::string&;
    auto getDateSending() const -> const Date&;
    /// @}

    /// @name Change functions
    /// @{
    bool setNickname(const std::string& nickname, const InternalEmployeePtr& changer);
    bool setAuthor(const WeakPersonPtr& author, const InternalEmployeePtr& changer);
    bool setMessage(const std::string& message, const InternalEmployeePtr& changer);
    bool setPlatform(const std::string& platform, const InternalEmployeePtr& changer);
    bool setDateSending(const Date& date, const InternalEmployeePtr& changer);
    /// @}

private:
    std::string   nickname;
    WeakPersonPtr author;
    std::string   message;
    std::string   platform;
    Date          date_sending;
};