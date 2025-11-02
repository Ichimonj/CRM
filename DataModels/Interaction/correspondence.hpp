#pragma once
#include "base_interaction.hpp"
#include "date.hpp"

struct Message;
using MessagePtr = std::shared_ptr<Message>;

struct Correspondence : public BaseInteraction {
    Correspondence(const BigUint& id);
    Correspondence(
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
        std::vector<std::string>           tags,
        std::vector<InteractionResult>     results,
        std::vector<Note>                  notes,
        std::vector<StringPair>            more_data,
        std::vector<InteractionPtr>        related_interactions,
        std::vector<FilePtr>               attachment_files,
        std::vector<PersonPtr>             participants,
        std::vector<MessagePtr>            messages,
        const std::string&                 platform
    );

public:
    /// @name Getters
    /// @{
    auto getMessages() const -> const std::vector<MessagePtr>&;
    auto getPlatform() const -> const std::string&;
    /// @}

    /// @name Change functions
    /// @{
    void addMessage(const MessagePtr& message, const InternalEmployeePtr& changer);
    void delMessage(const size_t id, const InternalEmployeePtr& changer);
    void setPlatform(const std::string& platform, const InternalEmployeePtr& changer);
    /// @}

private:
    std::vector<MessagePtr> messages;
    std::string             platform;
};