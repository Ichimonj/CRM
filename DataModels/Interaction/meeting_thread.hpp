#pragma once
#include "base_interaction.hpp"
#include "meeting.hpp"

using ClientPtr = std::shared_ptr<Client>;
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
        std::vector<MeetingPtr>            meetings,
        std::vector<ClientPtr>             clients,
        std::vector<InternalEmployeePtr>   employees
    );

public:
    /// @name Getters
    /// @{
    auto getMeetings() const -> const std::vector<MeetingPtr>;
    auto getClients() const -> const std::vector<ClientPtr>;
    auto getEmployees() const -> const std::vector<InternalEmployeePtr>;
    /// @}

    /// @name Change functions
    /// @{
    void addMeeting(const MeetingPtr& meeting, const InternalEmployeePtr& changer);
    void delMeeting(const size_t id, const InternalEmployeePtr& changer);

    void addClient(const ClientPtr& client, const InternalEmployeePtr& changer);
    void delClient(const size_t id, const InternalEmployeePtr& changer);

    void addEmployee(const InternalEmployeePtr& employee, const InternalEmployeePtr& changer);
    void delEmployee(const size_t id, const InternalEmployeePtr& changer);
    /// @}

private:
    std::vector<MeetingPtr>          meetings;   ///< Collection of meetings in the thread or series
    std::vector<ClientPtr>           clients;    ///< Clients associated with the meeting thread
    std::vector<InternalEmployeePtr> employees;  ///< Employees involved in the meeting thread
};