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
enum Gender { male, female, unknown };
class Person {
public:
    Person(const std::string& name, const std::string& surname, const OptionalStr& patronymic);
    Person(
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
    auto getName() const -> const std::string&;
    auto getSurname() const -> const std::string&;
    auto getPatronymic() const -> const OptionalStr&;
    auto getPreferredLanguage() const -> const OptionalStr&;
    auto getBirthday() const -> const DatePtr;
    auto getPhoneNumber() const -> const PhoneNumberPtr;
    auto getAddress() const -> const AddressPtr;
    auto getEmail() const -> const OptionalStr&;
    auto getGender() const -> const Gender;

    auto getMorePhoneNumbers() const -> const std::vector<PhoneNumber>&;
    auto getMoreAddresses() const -> const std::vector<Address>&;
    auto getMoreEmail() const -> const std::vector<std::string>&;

    auto getOtherDocuments() const -> const std::vector<DocumentPtr>&;
    auto getOtherFiles() const -> const std::vector<FileMetadataPtr>&;
    auto getInteractionHistory() const -> const std::vector<InteractionPtr>&;
    auto getNotes() const -> const std::vector<Note>&;
    auto getChangeLogs() const -> const std::vector<ChangeLogPtr>&;
    /// @}

    /// @name Change functions
    void setName(const std::string& name, const InternalEmployeePtr& changer);
    void setSurname(const std::string& surname, const InternalEmployeePtr& changer);
    void setPatronymic(const OptionalStr& patronymic, const InternalEmployeePtr& changer);
    void setPreferredLanguage(const OptionalStr& lan, const InternalEmployeePtr& changer);
    void setBirthday(const DatePtr& birthday, const InternalEmployeePtr& changer);
    void setPhoneNumber(const PhoneNumberPtr& number, const InternalEmployeePtr& changer);
    void setAddress(const AddressPtr& address, const InternalEmployeePtr& changer);
    void setEmail(const OptionalStr& email, const InternalEmployeePtr& changer);
    void setGender(const Gender gender, const InternalEmployeePtr& changer);

    void addRelatedDeals(
        const DealPtr& deal, const InternalEmployeePtr& changer, const Date& change_date = Date()
    );
    void delRelatedDeals(const DealPtr& deal, const InternalEmployeePtr& changer, const Date& change_date = Date());
    
    void addMorePhoneNumber(const PhoneNumber& number, const InternalEmployeePtr& changer);
    void delMorePhoneNumber(size_t index, const InternalEmployeePtr& changer);

    void addMoreAddress(const Address& address, const InternalEmployeePtr& changer);
    void delMoreAddress(size_t index, const InternalEmployeePtr& changer);

    void addMoreEmails(const std::string& email, const InternalEmployeePtr& changer);
    void delMoreEmails(size_t index, const InternalEmployeePtr& changer);

    void addOtherDocument(const DocumentPtr& document, const InternalEmployeePtr& changer);
    void delOtherDocument(size_t index, const InternalEmployeePtr& changer);

    void addOtherFile(const FileMetadataPtr& file, const InternalEmployeePtr& changer);
    void delOtherFile(size_t index, const InternalEmployeePtr& changer);

    void addInteraction(const InteractionPtr& interaction, const InternalEmployeePtr& changer);
    void delInteraction(size_t index, const InternalEmployeePtr& changer);

    void addTag(const std::string& tag, const InternalEmployeePtr& changer);
    void delTag(size_t index, const InternalEmployeePtr& changer);

    void addNote(const Note& note, const InternalEmployeePtr& changer);
    void delNote(size_t index, const InternalEmployeePtr& changer);

    void updateAt(const Date& date);
    /// @}

private:
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

protected:
    std::vector<ChangeLogPtr> change_logs;
};