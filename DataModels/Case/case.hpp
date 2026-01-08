#pragma once
#pragma once
#include <vector>

#include "BigNum/big_uint.hpp"
#include "DateTime/date.hpp"
#include "Interaction/priority.hpp"
#include "Note/note.hpp"
#include "Usings/type_usings.hpp"

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
        const WeakInternalEmployee&     assigned_to,
        const WeakClientPtr&            related_client,
        std::vector<Note>               notes,
        std::vector<BaseInteractionPtr> related_interactions
    );

    /// @name Getters
    /// @{
    auto getId() const -> const BigUint&;
    auto getTitle() const -> const std::string&;
    auto getDescription() const -> const OptionalStr&;
    auto getStatus() const -> CaseStatus;
    auto getPriority() const -> Priority;
    auto getCreatedDate() const -> const Date&;
    auto getResolvedDate() const -> const DatePtr&;
    auto getAssignedTo() const -> const WeakInternalEmployee&;
    auto getRelatedClient() const -> const WeakClientPtr&;
    auto getNotes() const -> const std::vector<Note>&;
    auto getRelatedInteractions() const -> const std::vector<BaseInteractionPtr>&;
    auto getChangeLogs() const -> const std::vector<ChangeLogPtr>&;
    /// @}

    /// @name Change functions
    /// @{
    bool setTitle(const std::string& title, const InternalEmployeePtr& changer);
    bool setDescription(const OptionalStr& description, const InternalEmployeePtr& changer);
    bool setStatus(const CaseStatus& status, const InternalEmployeePtr& changer);
    bool setPriority(const Priority& priority, const InternalEmployeePtr& changer);
    bool setResolvedDate(const DatePtr& resolved_date, const InternalEmployeePtr& changer);
    bool setAssignedTo(const WeakInternalEmployee& assigned_to, const InternalEmployeePtr& changer);
    bool setRelatedClient(const WeakClientPtr& related_client, const InternalEmployeePtr& changer);
    bool addNote(const Note& note, const InternalEmployeePtr& changer);
    bool delNote(size_t index, const InternalEmployeePtr& changer);
    bool addRelatedInteraction(
        const BaseInteractionPtr& interaction, const InternalEmployeePtr& changer
    );
    bool delRelatedInteraction(size_t index, const InternalEmployeePtr& changer);
    /// @}
private:
    BigUint              id;
    std::string          title;
    OptionalStr          description;
    CaseStatus           status;
    Priority             priority;
    Date                 create_date = Date();
    DatePtr              resolved_date;
    WeakInternalEmployee assigned_to;
    WeakClientPtr        related_client;
    std::vector<Note>    notes;
    //
    std::vector<BaseInteractionPtr> related_interactions;
    std::vector<ChangeLogPtr>       change_logs;
};