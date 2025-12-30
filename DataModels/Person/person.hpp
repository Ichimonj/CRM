#pragma once
#include <memory>
#include <vector>

#include "address.hpp"
#include "base_interaction.hpp"
#include "date.hpp"
#include "document.hpp"
#include "file_metadata.hpp"
#include "note.hpp"
#include "phone_number.hpp"
#include "social_network.hpp"

#ifdef _DEBUG
class InitPersons;
#endif // _DEBUG

class InternalEmployee;
class ChangeLog;

using DatePtr             = std::shared_ptr<Date>;
using PhoneNumberPtr      = std::shared_ptr<PhoneNumber>;
using AddressPtr          = std::shared_ptr<Address>;
using InternalEmployeePtr = std::shared_ptr<InternalEmployee>;
using ChangeLogPtr        = std::shared_ptr<ChangeLog>;
using FileMetadataPtr     = std::shared_ptr<FileMetadata>;
using DocumentPtr         = std::shared_ptr<Document>;
using InteractionPtr      = std::shared_ptr<BaseInteraction>;
using OptionalStr         = std::optional<std::string>;
enum Gender { male, female, unknown, COUNT };
class Person {
public:
    Person(
        const BigUint&     id,
        const std::string& name,
        const std::string& surname,
        const OptionalStr& patronymic
    );
    Person(
        const BigUint&               id,
        const std::string&           name,
        const std::string&           surname,
        const OptionalStr&           patronymic,
        const OptionalStr&           preferred_language,
        const DatePtr&               birthday,
        const PhoneNumberPtr&        phone_number,
        const AddressPtr&            address,
        const OptionalStr&           email,
        const Gender&                gender,
        std::vector<SocialNetwork>   social_networks,
        std::vector<PhoneNumber>     more_phone_numbers,
        std::vector<Address>         more_addresses,
        std::vector<std::string>     more_emails,
        std::vector<DocumentPtr>     other_documents,
        std::vector<FileMetadataPtr> other_files,
        std::vector<InteractionPtr>  interaction_history,
        std::vector<std::string>     tags,
        std::vector<Note>            notes
    );

    virtual ~Person() noexcept = default;

public:
    /// @name Getters
    /// @{
    auto getId() const -> const BigUint&;
    auto getName() const -> const std::string&;
    auto getSurname() const -> const std::string&;
    auto getPatronymic() const -> const OptionalStr&;
    auto getPreferredLanguage() const -> const OptionalStr&;
    auto getBirthday() const -> const DatePtr&;
    auto getCreatedAt() const -> const Date&;
    auto getUpdateAt() const -> const Date&;
    auto getPhoneNumber() const -> const PhoneNumberPtr;
    auto getAddress() const -> const AddressPtr;
    auto getEmail() const -> const OptionalStr&;
    auto getGender() const -> Gender;

    auto getRelatedDeals() const -> const std::vector<DealPtr>&;
    auto getSocialNetworks() const -> const std::vector<SocialNetwork>&;
    auto getMorePhoneNumbers() const -> const std::vector<PhoneNumber>&;
    auto getMoreAddresses() const -> const std::vector<Address>&;
    auto getMoreEmails() const -> const std::vector<std::string>&;

    auto getOtherDocuments() const -> const std::vector<DocumentPtr>&;
    auto getOtherFiles() const -> const std::vector<FileMetadataPtr>&;
    auto getInteractionHistory() const -> const std::vector<InteractionPtr>&;
    auto getTags() const -> const std::vector<std::string>&;
    auto getNotes() const -> const std::vector<Note>&;
    auto getChangeLogs() const -> const std::vector<ChangeLogPtr>&;
    /// @}

    /// @name Change functions
    // functions called only from the database
private:
    bool setName(const std::string& name, const InternalEmployeePtr& changer);
    bool setEmail(const OptionalStr& email, const InternalEmployeePtr& changer);

    bool addMoreEmails(const std::string& email, const InternalEmployeePtr& changer);
    bool delMoreEmails(size_t index, const InternalEmployeePtr& changer);
    
    bool setPhoneNumber(const PhoneNumberPtr& number, const InternalEmployeePtr& changer);

    bool addMorePhoneNumber(const PhoneNumber& number, const InternalEmployeePtr& changer);
    bool delMorePhoneNumber(size_t index, const InternalEmployeePtr& changer);
   
    //public functions
public:
    bool setSurname(const std::string& surname, const InternalEmployeePtr& changer);
    bool setPatronymic(const OptionalStr& patronymic, const InternalEmployeePtr& changer);
    bool setPreferredLanguage(const OptionalStr& lan, const InternalEmployeePtr& changer);
    bool setBirthday(const DatePtr& birthday, const InternalEmployeePtr& changer);
    bool setAddress(const AddressPtr& address, const InternalEmployeePtr& changer);
    bool setGender(const Gender gender, const InternalEmployeePtr& changer);

    bool addRelatedDeals(
        const DealPtr& deal, const InternalEmployeePtr& changer, const Date& change_date = Date()
    );
    bool delRelatedDeals(
        const DealPtr& deal, const InternalEmployeePtr& changer, const Date& change_date = Date()
    );

    bool addMoreAddress(const Address& address, const InternalEmployeePtr& changer);
    bool delMoreAddress(size_t index, const InternalEmployeePtr& changer);

    bool addOtherDocument(const DocumentPtr& document, const InternalEmployeePtr& changer);
    bool delOtherDocument(size_t index, const InternalEmployeePtr& changer);

    bool addOtherFile(const FileMetadataPtr& file, const InternalEmployeePtr& changer);
    bool delOtherFile(size_t index, const InternalEmployeePtr& changer);

    bool addInteraction(const InteractionPtr& interaction, const InternalEmployeePtr& changer);
    bool delInteraction(size_t index, const InternalEmployeePtr& changer);

    bool addTag(const std::string& tag, const InternalEmployeePtr& changer);
    bool delTag(size_t index, const InternalEmployeePtr& changer);

    bool addNote(const Note& note, const InternalEmployeePtr& changer);
    bool delNote(size_t index, const InternalEmployeePtr& changer);

    void updateAt(const Date& date);
    /// @}

private:
    BigUint        id;
    std::string    name;
    std::string    surname;
    OptionalStr    patronymic;
    OptionalStr    preferred_language;

    DatePtr        birthday;
    Date           created_at;
    Date           update_at;
    PhoneNumberPtr phone_number;

    AddressPtr     address;
    OptionalStr    email;

    Gender         gender;
    //
    std::vector<DealPtr>         related_deals;
    std::vector<SocialNetwork>   social_networks;
    std::vector<PhoneNumber>     more_phone_numbers;
    std::vector<Address>         more_addresses;
    std::vector<std::string>     more_emails;
    std::vector<DocumentPtr>     other_documents;
    std::vector<FileMetadataPtr> other_files;
    std::vector<InteractionPtr>  interaction_history;
    std::vector<std::string>     tags;
    std::vector<Note>            notes;

    friend class ClientDataBase;
    friend class ExternalEmployeeDataBase;
    friend class InternalEmployeeDataBase;
#ifdef _DEBUG
    friend class InitPersons;
#endif // _DEBUG

protected:
    std::vector<ChangeLogPtr> change_logs;
};