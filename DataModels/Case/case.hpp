#pragma once
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "big_uint.hpp"
#include "date.hpp"
#include "note.hpp"
#include "priority.hpp"

struct BaseInteraction;
class InternalEmployee;
class Client;
class ChangeLog;

using OptionalStr         = std::optional<std::string>;
using DatePtr             = std::shared_ptr<Date>;
using InternalEmployeePtr = std::shared_ptr<InternalEmployee>;
using ClientPtr           = std::shared_ptr<Client>;
using BaseInteractionPtr  = std::shared_ptr<BaseInteraction>;
using ChangeLogPtr        = std::shared_ptr<ChangeLog>;
enum class CaseStatus : uint8_t { Open, InProgress, Resolved, Closed, COUNT };

class Case {
public:
    Case(const BigUint& id);
    Case(
        const BigUint&                  id,
        const std::string&              title,
        const OptionalStr&              description,
        const CaseStatus&               status,
        const Priority&                 priority,
        const Date&                     create_date,
        const DatePtr&                  resolved_date,
        const InternalEmployeePtr&      assigned_to,
        const ClientPtr&                related_client,
        std::vector<Note>               notes,
        std::vector<BaseInteractionPtr> related_interactions
    );

    /// @name Getters
    /// @{
    auto getId() const -> const BigUint&;
    auto getTitle() const -> const std::string&;
    auto getDescription() const -> const OptionalStr&;
    auto getStatus() const -> const CaseStatus;
    auto getPriority() const -> const Priority;
    auto getCreatedDate() const -> const Date&;
    auto getResolvedDate() const -> const DatePtr&;
    auto getAssignedTo() const -> const InternalEmployeePtr&;
    auto getRelatedClient() const -> const ClientPtr&;
    auto getNotes() const -> const std::vector<Note>&;
    auto getRelatedInteractions() const -> const std::vector<BaseInteractionPtr>&;
    auto getChangeLogs() const -> const std::vector<ChangeLogPtr>&;
    /// @}

    /// @name Change functions
    /// @{
    void setTitle(const std::string& title, const InternalEmployeePtr& changer);
    void setDescription(const OptionalStr& description, const InternalEmployeePtr& changer);
    void setStatus(const CaseStatus& status, const InternalEmployeePtr& changer);
    void setPriority(const Priority& priority, const InternalEmployeePtr& changer);
    void setResolvedDate(const DatePtr& resolved_date, const InternalEmployeePtr& changer);
    void setAssignedTo(const InternalEmployeePtr& assigned_to, const InternalEmployeePtr& changer);
    void setRelatedClient(const ClientPtr& related_client, const InternalEmployeePtr& changer);
    void addNote(const Note& note, const InternalEmployeePtr& changer);
    void delNote(size_t index, const InternalEmployeePtr& changer);
    void addRelatedInteraction(
        const BaseInteractionPtr& interaction, const InternalEmployeePtr& changer
    );
    void delRelatedInteraction(size_t index, const InternalEmployeePtr& changer);
    /// @}
private:
    BigUint             id;
    std::string         title;
    OptionalStr         description;
    CaseStatus          status;
    Priority            priority;
    Date                create_date = Date();
    DatePtr             resolved_date;
    InternalEmployeePtr assigned_to;
    ClientPtr           related_client;
    std::vector<Note>   notes;
    //
    std::vector<BaseInteractionPtr> related_interactions;
    std::vector<ChangeLogPtr>       change_logs;
};