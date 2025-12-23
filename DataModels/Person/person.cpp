#include "person.hpp"

#include "campaign.hpp"
#include "change_log.hpp"
#include "company.hpp"

Person::Person(
    const BigUint&     id,
    const std::string& name,
    const std::string& surname,
    const OptionalStr& patronymic
)
    : id(id), name(name), surname(surname), patronymic(patronymic), gender(Gender::unknown)
{
}

Person::Person(
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
)
    : id(id)
    , name(name)
    , surname(surname)
    , patronymic(patronymic)
    , preferred_language(preferred_language)
    , birthday(birthday)
    , phone_number(phone_number)
    , address(address)
    , email(email)
    , gender(gender)
    , social_networks(std::move(social_networks))
    , more_phone_numbers(std::move(more_phone_numbers))
    , more_addresses(std::move(more_addresses))
    , more_emails(std::move(more_emails))
    , other_documents(std::move(other_documents))
    , other_files(std::move(other_files))
    , interaction_history(std::move(interaction_history))
    , tags(std::move(tags))
    , notes(std::move(notes))
{
    this->created_at = Date();
    this->update_at  = created_at;
}
auto Person::getId() const -> const BigUint& { return this->id; }
auto Person::getName() const -> const std::string& { return this->name; }
auto Person::getSurname() const -> const std::string& { return this->surname; }
auto Person::getPatronymic() const -> const OptionalStr& { return this->patronymic; }
auto Person::getPreferredLanguage() const -> const OptionalStr& { return this->preferred_language; }
auto Person::getBirthday() const -> const DatePtr& { return this->birthday; }
auto Person::getCreatedAt() const -> const Date& { return this->created_at; }
auto Person::getUpdateAt() const -> const Date& { return this->update_at; }
auto Person::getPhoneNumber() const -> const PhoneNumberPtr { return this->phone_number; }
auto Person::getAddress() const -> const AddressPtr { return this->address; }
auto Person::getEmail() const -> const OptionalStr& { return this->email; }
auto Person::getGender() const -> Gender { return this->gender; }

auto Person::getRelatedDeals() const -> const std::vector<DealPtr>& { return this->related_deals; }

auto Person::getSocialNetworks() const -> const std::vector<SocialNetwork>&
{
    return this->social_networks;
}

auto Person::getMorePhoneNumbers() const -> const std::vector<PhoneNumber>&
{
    return this->more_phone_numbers;
}
auto Person::getMoreAddresses() const -> const std::vector<Address>&
{
    return this->more_addresses;
}
auto Person::getMoreEmails() const -> const std::vector<std::string>& { return this->more_emails; }

auto Person::getOtherDocuments() const -> const std::vector<DocumentPtr>&
{
    return this->other_documents;
}

auto Person::getOtherFiles() const -> const std::vector<FileMetadataPtr>&
{
    return this->other_files;
}

auto Person::getInteractionHistory() const -> const std::vector<InteractionPtr>&
{
    return this->interaction_history;
}
auto Person::getTags() const -> const std::vector<std::string>& { return this->tags; }
auto Person::getNotes() const -> const std::vector<Note>& { return this->notes; }
auto Person::getChangeLogs() const -> const std::vector<ChangeLogPtr>& { return this->change_logs; }

bool Person::setName(const std::string& name, const InternalEmployeePtr& changer)
{
    if (this->name != name) {
        Date update     = Date();
        this->update_at = update;
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<std::string>(this->name)),
            std::make_optional(std::make_shared<std::string>(name)),
            PersonFields::Name,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change,
            update
        ));
        this->name = name;
        return true;
    }
    return false;
}

bool Person::setSurname(const std::string& surname, const InternalEmployeePtr& changer)
{
    if (this->surname != surname) {
        Date update     = Date();
        this->update_at = update;
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<std::string>(this->surname)),
            std::make_optional(std::make_shared<std::string>(surname)),
            PersonFields::Surname,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change,
            update
        ));
        this->surname = surname;
        return true;
    }
    return false;
}

bool Person::setPatronymic(const OptionalStr& patronymic, const InternalEmployeePtr& changer)
{
    if (this->patronymic != patronymic) {
        Date update     = Date();
        this->update_at = update;

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->patronymic),
            OPTIONAL_STR_TO_VALUE(patronymic),
            PersonFields::Patronymic,
            this->patronymic ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            patronymic ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change,
            update
        ));
        this->patronymic = patronymic;
        return true;
    }
    return false;
}

bool Person::setPreferredLanguage(const OptionalStr& lan, const InternalEmployeePtr& changer)
{
    if (this->preferred_language != lan) {
        Date update     = Date();
        this->update_at = update;

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->preferred_language),
            OPTIONAL_STR_TO_VALUE(lan),
            PersonFields::PreferredLanguage,
            this->preferred_language ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            lan ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change,
            update
        ));
        this->preferred_language = lan;
        return true;
    }
    return false;
}

bool Person::setBirthday(const DatePtr& birthday, const InternalEmployeePtr& changer)
{
    bool isChanged = false;

    if (this->birthday == nullptr || birthday == nullptr) {
        isChanged = (this->birthday != birthday);
    } else {
        isChanged = !(*this->birthday == *birthday);
    }

    if (isChanged) {
        Date update     = Date();
        this->update_at = update;

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->birthday),
            PTR_TO_OPTIONAL(birthday),
            PersonFields::Birthday,
            this->birthday ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
            birthday ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
            ChangeLog::Action::Change,
            update
        ));
        this->birthday = birthday;
        return true;
    }
    return false;
}

bool Person::setPhoneNumber(const PhoneNumberPtr& number, const InternalEmployeePtr& changer)
{
    if (this->phone_number == nullptr || number == nullptr) {
        if (this->phone_number == number) {
            return false;
        }
    } else if (*this->phone_number == *number) {
        return false;
    }

    Date update     = Date();
    this->update_at = update;

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->phone_number),
        PTR_TO_OPTIONAL(number),
        PersonFields::PhoneNumber,
        this->phone_number ? ChangeLog::FieldType::PhoneNumber : ChangeLog::FieldType::null,
        number ? ChangeLog::FieldType::PhoneNumber : ChangeLog::FieldType::null,
        ChangeLog::Action::Change,
        update
    ));
    this->phone_number = number;
    return true;
}

bool Person::setAddress(const AddressPtr& address, const InternalEmployeePtr& changer)
{
    if (this->address == nullptr || address == nullptr) {
        if (this->address == address) {
            return false;
        }
    } else if (*this->address == *address) {
        return false;
    }

    Date update     = Date();
    this->update_at = update;

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->address),
        PTR_TO_OPTIONAL(address),
        PersonFields::Address,
        this->address ? ChangeLog::FieldType::Address : ChangeLog::FieldType::null,
        address ? ChangeLog::FieldType::Address : ChangeLog::FieldType::null,
        ChangeLog::Action::Change,
        update
    ));
    this->address = address;
    return true;
}

bool Person::setEmail(const OptionalStr& email, const InternalEmployeePtr& changer)
{
    if (this->email != email) {
        Date update     = Date();
        this->update_at = update;

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            OPTIONAL_STR_TO_VALUE(this->email),
            OPTIONAL_STR_TO_VALUE(email),
            PersonFields::Email,
            this->email ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            email ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change,
            update
        ));
        this->email = email;
        return true;
    }
    return false;
}

bool Person::setGender(const Gender gender, const InternalEmployeePtr& changer)
{
    if (this->gender != gender) {
        Date update     = Date();
        this->update_at = update;

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->gender),
            std::make_optional(gender),
            PersonFields::Gender,
            ChangeLog::FieldType::Gender,
            ChangeLog::FieldType::Gender,
            ChangeLog::Action::Change,
            update
        ));
        this->gender = gender;
        return true;
    }
    return false;
}

bool Person::addRelatedDeals(
    const DealPtr& deal, const InternalEmployeePtr& changer, const Date& change_date
)
{
    if (std::find(this->related_deals.begin(), this->related_deals.end(), deal) ==
        this->related_deals.end()) {
        this->update_at = change_date;

        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(deal),
            PersonFields::RelatedDeals,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Deal,
            ChangeLog::Action::Add,
            change_date
        ));
        this->related_deals.push_back(deal);
        return true;
    }
    return false;
}

bool Person::delRelatedDeals(
    const DealPtr& deal, const InternalEmployeePtr& changer, const Date& change_date
)
{
    auto del_deal = std::find(this->related_deals.begin(), this->related_deals.end(), deal);

    if (del_deal != this->related_deals.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(del_deal[0]),
            std::nullopt,
            PersonFields::RelatedDeals,
            ChangeLog::FieldType::Deal,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            change_date
        ));
        this->related_deals.erase(del_deal);
        return true;
    }
    return false;
}

bool Person::addMorePhoneNumber(const PhoneNumber& number, const InternalEmployeePtr& changer)
{
    if (std::find(this->more_phone_numbers.begin(), this->more_phone_numbers.end(), number) ==
        this->more_phone_numbers.end()) {
        Date update     = Date();
        this->update_at = update;
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(std::make_shared<PhoneNumber>(number)),
            PersonFields::MorePhoneNumber,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::PhoneNumber,
            ChangeLog::Action::Add,
            update
        ));
        this->more_phone_numbers.push_back(number);
        return true;
    }
    return false;
}

bool Person::delMorePhoneNumber(size_t index, const InternalEmployeePtr& changer)
{
    if (this->more_phone_numbers.size() > index) {
        Date update     = Date();
        this->update_at = update;
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<PhoneNumber>(this->more_phone_numbers[index])),
            std::nullopt,
            PersonFields::MorePhoneNumber,
            ChangeLog::FieldType::PhoneNumber,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->more_phone_numbers.erase(this->more_phone_numbers.begin() + index);
        return true;
    }
    return false;
}

bool Person::addMoreAddress(const Address& address, const InternalEmployeePtr& changer)
{
    if (std::find(this->more_addresses.begin(), this->more_addresses.end(), address) ==
        this->more_addresses.end()) {
        Date update     = Date();
        this->update_at = update;
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(std::make_shared<Address>(address)),
            PersonFields::MoreAddress,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Address,
            ChangeLog::Action::Add,
            update
        ));
        this->more_addresses.push_back(address);
        return true;
    }
    return false;
}

bool Person::delMoreAddress(size_t index, const InternalEmployeePtr& changer)
{
    if (this->more_addresses.size() > index) {
        Date update     = Date();
        this->update_at = update;
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<Address>(this->more_addresses[index])),
            std::nullopt,
            PersonFields::MoreAddress,
            ChangeLog::FieldType::Address,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->more_addresses.erase(this->more_addresses.begin() + index);
        return true;
    }
    return false;
}

bool Person::addMoreEmails(const std::string& email, const InternalEmployeePtr& changer)
{
    if (std::find(this->more_emails.begin(), this->more_emails.end(), email) ==
        this->more_emails.end()) {
        Date update     = Date();
        this->update_at = update;
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(std::make_shared<std::string>(email)),
            PersonFields::MoreEmail,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Add,
            update
        ));
        this->more_emails.push_back(email);
        return true;
    }
    return false;
}

bool Person::delMoreEmails(size_t index, const InternalEmployeePtr& changer)
{
    if (this->more_emails.size() > index) {
        Date update     = Date();
        this->update_at = update;
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<std::string>(this->more_emails[index])),
            std::nullopt,
            PersonFields::MoreEmail,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->more_emails.erase(this->more_emails.begin() + index);
        return true;
    }
    return false;
}

bool Person::addOtherDocument(const DocumentPtr& document, const InternalEmployeePtr& changer)
{
    if (std::find(this->other_documents.begin(), this->other_documents.end(), document) ==
        this->other_documents.end()) {
        Date update     = Date();
        this->update_at = update;
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(document),
            PersonFields::OtherDocuments,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Document,
            ChangeLog::Action::Add,
            update
        ));
        this->other_documents.push_back(document);
        return true;
    }
    return false;
}

bool Person::delOtherDocument(size_t index, const InternalEmployeePtr& changer)
{
    if (index < this->other_documents.size()) {
        Date update     = Date();
        this->update_at = update;
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->other_documents[index]),
            std::nullopt,
            PersonFields::OtherDocuments,
            ChangeLog::FieldType::Document,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->other_documents.erase(this->other_documents.begin() + index);
        return true;
    }
    return false;
}

bool Person::addOtherFile(const FileMetadataPtr& file, const InternalEmployeePtr& changer)
{
    if (std::find(this->other_files.begin(), this->other_files.end(), file) ==
        this->other_files.end()) {
        Date update     = Date();
        this->update_at = update;
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(file),
            PersonFields::OtherFiles,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::FileMetadata,
            ChangeLog::Action::Add,
            update
        ));
        this->other_files.push_back(file);
        return true;
    }
    return false;
}

bool Person::delOtherFile(size_t index, const InternalEmployeePtr& changer)
{
    if (index < this->other_files.size()) {
        Date update     = Date();
        this->update_at = update;
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->other_files[index]),
            std::nullopt,
            PersonFields::OtherFiles,
            ChangeLog::FieldType::FileMetadata,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->other_files.erase(this->other_files.begin() + index);
        return true;
    }
    return false;
}

bool Person::addInteraction(const InteractionPtr& interaction, const InternalEmployeePtr& changer)
{
    if (std::find(
            this->interaction_history.begin(), this->interaction_history.end(), interaction
        ) == this->interaction_history.end()) {
        Date update     = Date();
        this->update_at = update;
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(interaction),
            PersonFields::InteractionHistory,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::BaseInteraction,
            ChangeLog::Action::Add,
            update
        ));
        this->interaction_history.push_back(interaction);
        return true;
    }
    return false;
}

bool Person::delInteraction(size_t index, const InternalEmployeePtr& changer)
{
    if (index < this->interaction_history.size()) {
        Date update     = Date();
        this->update_at = update;
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->interaction_history[index]),
            std::nullopt,
            PersonFields::InteractionHistory,
            ChangeLog::FieldType::BaseInteraction,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->interaction_history.erase(this->interaction_history.begin() + index);
        return true;
    }
    return false;
}

bool Person::addTag(const std::string& tag, const InternalEmployeePtr& changer)
{
    if (std::find(this->tags.begin(), this->tags.end(), tag) == this->tags.end()) {
        Date update     = Date();
        this->update_at = update;
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(std::make_shared<std::string>(tag)),
            PersonFields::Tags,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Add,
            update
        ));
        this->tags.push_back(tag);
        return true;
    }
    return false;
}

bool Person::delTag(size_t index, const InternalEmployeePtr& changer)
{
    if (index < this->tags.size()) {
        Date update     = Date();
        this->update_at = update;
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<std::string>(this->tags[index])),
            std::nullopt,
            PersonFields::Tags,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->tags.erase(this->tags.begin() + index);
        return true;
    }
    return false;
}

bool Person::addNote(const Note& note, const InternalEmployeePtr& changer)
{
    if (std::find(this->notes.begin(), this->notes.end(), note) == this->notes.end()) {
        Date update     = Date();
        this->update_at = update;
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(std::make_shared<Note>(note)),
            PersonFields::Notes,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::Note,
            ChangeLog::Action::Add,
            update
        ));
        this->notes.push_back(note);
        return true;
    }
    return false;
}

bool Person::delNote(size_t index, const InternalEmployeePtr& changer)
{
    if (index < this->notes.size()) {
        Date update     = Date();
        this->update_at = update;
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<Note>(this->notes[index])),
            std::nullopt,
            PersonFields::Notes,
            ChangeLog::FieldType::Note,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove,
            update
        ));
        this->notes.erase(this->notes.begin() + index);
        return true;
    }
    return false;
}

void Person::updateAt(const Date& date) { this->update_at = date; }
