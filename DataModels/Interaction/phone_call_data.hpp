#pragma once
#include "base_interaction.hpp"

struct PhoneCallData : public BaseInteraction {
    enum class CallType : uint8_t { incoming, outgoing, missed, COUNT };

    PhoneCallData(const BigUint& id);

    PhoneCallData(
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
        const PhoneNumberPtr&              from_number,
        const PhoneNumberPtr&              to_number,
        const DatePtr&                     start_call,
        const DatePtr&                     end_call,
        const WeakPersonPtr&               call_creator,
        const std::string&                 call_provider,
        const std::optional<CallType>&     call_type
    );
    /// @name Getters
    /// @{
    auto getFromNumber() const -> const PhoneNumberPtr;
    auto getToNumber() const -> const PhoneNumberPtr;
    auto getStartCall() const -> const DatePtr;
    auto getEndCall() const -> const DatePtr;
    auto getCallType() const -> const std::optional<CallType>;
    auto getCallCreator() const -> const WeakPersonPtr&;
    auto getCallProvider() const -> const std::string&;
    /// @}

    /// @name Change functions
    /// @{
    bool setFromNumber(const PhoneNumberPtr& number, const InternalEmployeePtr& changer);
    bool setToNumber(const PhoneNumberPtr& number, const InternalEmployeePtr& changer);
    bool setStartCall(const DatePtr& start, const InternalEmployeePtr& changer);
    bool setEndCall(const DatePtr& end, const InternalEmployeePtr& changer);
    bool setCallType(const std::optional<CallType>& type, const InternalEmployeePtr& changer);
    bool setCallCreator(const WeakPersonPtr& creator, const InternalEmployeePtr& changer);
    bool setCallProvider(const std::string& provider, const InternalEmployeePtr& changer);
    /// @}

private:
    PhoneNumberPtr          from_number;  ///< Phone number that initiated the call
    PhoneNumberPtr          to_number;    ///< Phone number that received the call

    DatePtr                 start_call;  ///< Date and time when the call started
    DatePtr                 end_call;    ///< Date and time when the call ended

    WeakPersonPtr           call_creator;  ///< Person who created or initiated the call

    std::string             call_provider;  ///< Telecommunications provider used for the call

    std::optional<CallType> call_type;  ///< Type of call (incoming, outgoing, conference, etc.)
};