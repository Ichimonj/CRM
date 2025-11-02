#pragma once
#include "base_interaction.hpp"
#include "date.hpp"

class Client;
struct Address;
struct Meeting;

using MeetingPtr = std::shared_ptr<Meeting>;
using AddressPtr = std::shared_ptr<Address>;
using ClientPtr  = std::shared_ptr<Client>;

struct Meeting : public BaseInteraction {
    enum class MeetingType : uint8_t { Negotiation, Presentation, Training, Other };
    enum class MeetingOutcome : uint8_t {
        ClosedWon,
        ClosedLost,
        ProgressMade,
        FollowUpScheduled,
        InformationProvided,
        DecisionPending,
        AdditionalInfoNeeded,
        Postponed,
        Canceled,
        Redirected,
        IssueIdentified,
        Other
    };
    enum class MeetingStatus : uint8_t { Scheduled, InProgress, Completed, Canceled, Postponed };
   
    Meeting(const BigUint& id);
    
    Meeting(
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
        const AddressPtr&                  location,
        const MeetingStatus&               meeting_status,
        const MeetingType&                 meeting_type,
        std::vector<MeetingOutcome>        outcomes,
        std::vector<std::string>           other_outcomes,
        const std::string&                 other_type,
        const std::string&                 record,
        std::vector<ClientPtr>             clients,
        std::vector<InternalEmployeePtr>   employees,
        std::vector<PersonPtr>             invitees,
        const MeetingPtr&                  previous_meeting,
        const MeetingPtr&                  next_meeting,
        const Date&                        created_date,
        bool                               is_confirmed,
        bool                               is_virtual
    );

public:
    /// @name Getters
    /// @{
    auto getLocation() const -> const AddressPtr;
    auto getMeetingStatus() const -> MeetingStatus;
    auto getMeetingType() const -> MeetingType;
    auto getOutcomes() const -> const std::vector<MeetingOutcome>&;
    auto getOtherOutcomes() const -> const std::vector<std::string>&;
    auto getOtherType() const -> const std::string&;
    auto getRecord() const -> const std::string&;
    auto getClients() const -> const std::vector<ClientPtr>&;
    auto getEmployees() const -> const std::vector<InternalEmployeePtr>&;
    auto getInvitees() const -> const std::vector<PersonPtr>&;
    auto getPreviousMeeting() const -> const MeetingPtr;
    auto getNextMeeting() const -> const MeetingPtr;
    auto getCreatedDate() const -> const Date&;
    auto getIsConfirmed() const -> bool;
    auto getIsVirtual() const -> bool;
    /// @}

    /// @name Change functions
    /// @{
    void setLocation(const AddressPtr& location, const InternalEmployeePtr& changer);
    void setMeetingStatus(MeetingStatus status, const InternalEmployeePtr& changer);
    void setMeetingType(MeetingType type, const InternalEmployeePtr& changer);

    void addOutcome(const MeetingOutcome outcome, const InternalEmployeePtr& changer);
    void delOutcome(size_t id, const InternalEmployeePtr& changer);

    void addOtherOutcome(const std::string& outcome, const InternalEmployeePtr& changer);
    void delOtherOutcome(size_t id, const InternalEmployeePtr& changer);

    void setOtherType(const std::string& type, const InternalEmployeePtr& changer);
    void setRecord(const std::string& record, const InternalEmployeePtr& changer);

    void addClient(const ClientPtr& client, const InternalEmployeePtr& changer);
    void delClient(size_t id, const InternalEmployeePtr& changer);

    void addEmployee(const InternalEmployeePtr& employee, const InternalEmployeePtr& changer);
    void delEmployee(size_t id, const InternalEmployeePtr& changer);

    void addInvitee(const PersonPtr& invitee, const InternalEmployeePtr& changer);
    void delInvitee(size_t id, const InternalEmployeePtr& changer);

    void setPreviousMeeting(const MeetingPtr& meeting, const InternalEmployeePtr& changer);
    void setNextMeeting(const MeetingPtr& meeting, const InternalEmployeePtr& changer);
    void setIsConfirmed(bool is_confirmed, const InternalEmployeePtr& changer);
    void setIsVirtual(bool is_virtual, const InternalEmployeePtr& changer);
    /// @}

private:
    AddressPtr                       location;

    MeetingStatus                    meeting_status;
    MeetingType                      meeting_type;

    std::vector<MeetingOutcome>      outcomes;
    std::vector<std::string>         other_outcomes;

    std::string                      other_type;

    std::string                      record;

    std::vector<ClientPtr>           clients;
    std::vector<InternalEmployeePtr> employees;
    std::vector<PersonPtr>           invitees;

    MeetingPtr                       previous_meeting;
    MeetingPtr                       next_meeting;

    Date                             created_date;

    bool                             is_confirmed;
    bool                             is_virtual;
};
