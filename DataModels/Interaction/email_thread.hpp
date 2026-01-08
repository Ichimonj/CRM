#pragma once
#include "base_interaction.hpp"

struct EmailThread : public BaseInteraction {
    EmailThread(const BigUint& id);

    EmailThread(
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
        std::vector<EmailLetterPtr>        letters,
        std::vector<WeakClientPtr>         clients,
        std::vector<WeakInternalEmployee>  employees
    );

public:
    /// @name Getters
    /// @{
    auto getLetters() const -> const std::vector<EmailLetterPtr>&;
    auto getClients() const -> const std::vector<WeakClientPtr>&;
    auto getEmployees() const -> const std::vector<WeakInternalEmployee>&;
    /// @}

    /// @name Change functions
    /// @{
    bool addLetter(const EmailLetterPtr& letter, const InternalEmployeePtr& changer);
    bool delLetter(const size_t id, const InternalEmployeePtr& changer);

    bool addClient(const WeakClientPtr& client, const InternalEmployeePtr& changer);
    bool delClient(const size_t id, const InternalEmployeePtr& changer);

    bool addEmployee(const WeakInternalEmployee& employee, const InternalEmployeePtr& changer);
    bool delEmployee(const size_t id, const InternalEmployeePtr& changer);
    /// @}

    /// @name Auxiliary functions
    /// @{
    void clearClients();
    void clearEmployees();
    /// @}

private:
    std::vector<EmailLetterPtr> letters;  ///< Collection of email letters in the thread or folder
    std::vector<WeakClientPtr>  clients;  ///< Clients associated with this entity
    std::vector<WeakInternalEmployee> employees;  ///< Employees involved or responsible
};