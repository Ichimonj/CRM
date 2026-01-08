#pragma once
#include "base_interaction.hpp"

struct EmailLetter : public BaseInteraction {
    enum class EmailStatus : uint8_t {
        Sent,
        Delivered,
        Failed,
        Draft,
        Scheduled,
        Replied,
        Forwarded,
        COUNT
    };
    enum class EmailLetterType : uint8_t { incoming, outgoing, COUNT };

    EmailLetter(const BigUint& id);

    EmailLetter(
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
        const std::string&                 from_email_address,
        const std::string&                 to_email_address,
        const EmailLetterType&             letter_type,
        const EmailStatus&                 email_status,
        std::vector<std::string>           cc_email_addresses,
        std::vector<std::string>           bcc_email_addresses,
        const WeakPersonPtr&               sender,
        const WeakPersonPtr&               recipient,
        const std::string&                 body,
        const DatePtr&                     send_date,
        const DatePtr&                     received_date,
        const DatePtr&                     read_time,
        const std::string&                 email_provider,
        const EmailLetterPtr&              previous_letter,
        const EmailLetterPtr&              next_letter,
        bool                               is_read,
        bool                               is_flagged
    );

public:
    /// @name Getters
    /// @{
    auto getFromEmailAddress() const -> const std::string&;
    auto getToEmailAddress() const -> const std::string&;
    auto getLetterType() const -> EmailLetterType;
    auto getEmailStatus() const -> EmailStatus;
    auto getCcEmailAddresses() const -> const std::vector<std::string>&;
    auto getBccEmailAddresses() const -> const std::vector<std::string>&;
    auto getSender() const -> const WeakPersonPtr&;
    auto getRecipient() const -> const WeakPersonPtr&;
    auto getBody() const -> const std::string&;
    auto getSendDate() const -> const DatePtr;
    auto getReceivedDate() const -> const DatePtr;
    auto getReadTime() const -> const DatePtr;
    auto getEmailProvider() const -> const std::string&;
    auto getPreviousLetter() const -> const EmailLetterPtr;
    auto getNextLetter() const -> const EmailLetterPtr;
    auto getIsRead() const -> bool;
    auto getIsFlagged() const -> bool;
    /// @}

    /// @name Change functions
    /// @{
    bool setFromEmailAddress(const std::string& email, const InternalEmployeePtr& changer);
    bool setToEmailAddress(const std::string& email, const InternalEmployeePtr& changer);
    bool setLetterType(EmailLetterType type, const InternalEmployeePtr& changer);
    bool setEmailStatus(EmailStatus status, const InternalEmployeePtr& changer);

    bool addCcEmailAddress(const std::string& address, const InternalEmployeePtr& changer);
    bool delCcEmailAddress(size_t id, const InternalEmployeePtr& changer);

    bool addBccEmailAddress(const std::string& address, const InternalEmployeePtr& changer);
    bool delBccEmailAddress(size_t id, const InternalEmployeePtr& changer);

    bool setSender(const WeakPersonPtr& sender, const InternalEmployeePtr& changer);
    bool setRecipient(const WeakPersonPtr& recipient, const InternalEmployeePtr& changer);
    bool setBody(const std::string& body, const InternalEmployeePtr& changer);
    bool setSendDate(const DatePtr& date, const InternalEmployeePtr& changer);
    bool setReceivedDate(const DatePtr& date, const InternalEmployeePtr& changer);
    bool setReadTime(const DatePtr& time, const InternalEmployeePtr& changer);
    bool setEmailProvider(const std::string& provider, const InternalEmployeePtr& changer);
    bool setPreviousLetter(const EmailLetterPtr& letter, const InternalEmployeePtr& changer);
    bool setNextLetter(const EmailLetterPtr& letter, const InternalEmployeePtr& changer);
    bool setIsRead(bool is_read, const InternalEmployeePtr& changer);
    bool setIsFlagged(bool is_flagged, const InternalEmployeePtr& changer);
    /// @}

private:
    std::string              from_email_address;
    std::string              to_email_address;

    EmailLetterType          letter_type;
    EmailStatus              email_status;

    std::vector<std::string> cc_email_addresses;
    std::vector<std::string> bcc_email_addresses;

    WeakPersonPtr            sender;
    WeakPersonPtr            recipient;

    std::string              body;

    DatePtr                  send_date;
    DatePtr                  received_date;
    DatePtr                  read_time;

    std::string              email_provider;

    EmailLetterPtr           previous_letter;
    EmailLetterPtr           next_letter;

    bool                     is_read;
    bool                     is_flagged;
};