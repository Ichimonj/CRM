#pragma once
#include "base_interaction.hpp"
#include "meeting.hpp"

struct MeetingThread : public BaseInteraction {
    MeetingThread(const BigUint& id);

    MeetingThread(
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
        std::vector<MeetingPtr>            meetings,
        std::vector<WeakClientPtr>         clients,
        std::vector<WeakInternalEmployee>  employees
    );

public:
    /// @name Getters
    /// @{
    auto getMeetings() const -> const std::vector<MeetingPtr>&;
    auto getClients() const -> const std::vector<WeakClientPtr>&;
    auto getEmployees() const -> const std::vector<WeakInternalEmployee>&;
    /// @}

    /// @name Change functions
    /// @{
    bool addMeeting(const MeetingPtr& meeting, const InternalEmployeePtr& changer);
    bool delMeeting(const size_t id, const InternalEmployeePtr& changer);

    bool addClient(const WeakClientPtr& client, const InternalEmployeePtr& changer);
    bool delClient(const size_t id, const InternalEmployeePtr& changer);

    bool addEmployee(const WeakInternalEmployee& employee, const InternalEmployeePtr& changer);
    bool delEmployee(const size_t id, const InternalEmployeePtr& changer);
    /// @}

private:
    std::vector<MeetingPtr>           meetings;  ///< Collection of meetings in the thread or series
    std::vector<WeakClientPtr>        clients;   ///< Clients associated with the meeting thread
    std::vector<WeakInternalEmployee> employees;  ///< Employees involved in the meeting thread
};