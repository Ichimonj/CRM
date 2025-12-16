#pragma once
#include "base_interaction.hpp"

class Client;
struct EmailLetter;
using EmailLetterPtr = std::shared_ptr<EmailLetter>;
using ClientPtr      = std::shared_ptr<Client>;

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
        std::vector<EmailLetterPtr>        letters,
        std::vector<ClientPtr>             clients,
        std::vector<InternalEmployeePtr>   employees
    );

public:
    /// @name Getters
    /// @{
    auto getLetters() const -> const std::vector<EmailLetterPtr>&;
    auto getClients() const -> const std::vector<ClientPtr>&;
    auto getEmployees() const -> const std::vector<InternalEmployeePtr>&;
    /// @}

    /// @name Change functions
    /// @{
    bool addLetter(const EmailLetterPtr& letter, const InternalEmployeePtr& changer);
    bool delLetter(const size_t id, const InternalEmployeePtr& changer);

    bool addClient(const ClientPtr& client, const InternalEmployeePtr& changer);
    bool delClient(const size_t id, const InternalEmployeePtr& changer);

    bool addEmployee(const InternalEmployeePtr& employee, const InternalEmployeePtr& changer);
    bool delEmployee(const size_t id, const InternalEmployeePtr& changer);
    /// @}

private:
    std::vector<EmailLetterPtr> letters;  ///< Collection of email letters in the thread or folder
    std::vector<ClientPtr>      clients;  ///< Clients associated with this entity
    std::vector<InternalEmployeePtr> employees;  ///< Employees involved or responsible
};