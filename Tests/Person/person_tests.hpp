#include "gtest/gtest.h"
#include "person.hpp"

InternalEmployeePtr changer = nullptr;

namespace unit {
    TEST(PersonTest, SmallConstructor)
    {
        auto name    = "Name";
        auto surname = "Surname";
        auto person  = Person(BigUint("100"), name, surname, std::nullopt);

        SCOPED_TRACE("Person field");
        EXPECT_EQ(person.getName(), name);
        EXPECT_EQ(person.getSurname(), surname);
        EXPECT_EQ(person.getPatronymic(), std::nullopt);
        EXPECT_EQ(person.getPreferredLanguage(), std::nullopt);
        EXPECT_EQ(person.getBirthday(), nullptr);
        EXPECT_EQ(person.getPhoneNumber(), nullptr);
        EXPECT_EQ(person.getPhoneNumber(), nullptr);
        EXPECT_EQ(person.getEmail(), std::nullopt);
        EXPECT_EQ(person.getGender(), unknown);
        EXPECT_EQ(person.getMorePhoneNumbers().size(), 0);
        EXPECT_EQ(person.getMoreAddresses().size(), 0);
        EXPECT_EQ(person.getMoreEmails().size(), 0);
        EXPECT_EQ(person.getOtherDocuments().size(), 0);
        EXPECT_EQ(person.getOtherFiles().size(), 0);
        EXPECT_EQ(person.getInteractionHistory().size(), 0);
        EXPECT_EQ(person.getNotes().size(), 0);
        EXPECT_EQ(person.getChangeLogs().size(), 0);
    }
    auto person = Person(BigUint("1000"), "Name", "Surname", std::nullopt);

    TEST(PersonTest, Name)
    {
        person._setName("New name", changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(person.getName(), "New name");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 1);

        auto log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto old_value = std::get<StringPtr>(log->getOldValue().value());
        EXPECT_EQ(*old_value, "Name");
        EXPECT_EQ(*log->getOldValueStr(), "Name");

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<StringPtr>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "New name");
        EXPECT_EQ(*log->getNewValueStr(), "New name");

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(PersonFields::Name);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(PersonTest, Surname)
    {
        person.setSurname("New surname", changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(person.getSurname(), "New surname");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 2);

        auto log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto old_value = std::get<StringPtr>(log->getOldValue().value());
        EXPECT_EQ(*old_value, "Surname");
        EXPECT_EQ(*log->getOldValueStr(), "Surname");

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<StringPtr>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "New surname");
        EXPECT_EQ(*log->getNewValueStr(), "New surname");

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(PersonFields::Surname);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(PersonTest, Patronymic)
    {
        // add value
        person.setPatronymic(std::string("Patronymic"), changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(person.getPatronymic().has_value());
        EXPECT_EQ(person.getPatronymic().value(), "Patronymic");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 3);

        auto log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<StringPtr>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "Patronymic");
        EXPECT_EQ(*log->getNewValueStr(), "Patronymic");

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(PersonFields::Patronymic);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);

        // del value
        person.setPatronymic(std::nullopt, changer);

        SCOPED_TRACE("Value check");
        EXPECT_FALSE(person.getPatronymic().has_value());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 4);

        log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto old_value = std::get<StringPtr>(log->getOldValue().value());
        EXPECT_EQ(*old_value, "Patronymic");
        EXPECT_EQ(*log->getOldValueStr(), "Patronymic");

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(PersonTest, PreferredLanguage)
    {
        // add value
        person.setPreferredLanguage("English", changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(person.getPreferredLanguage().has_value());
        EXPECT_EQ(person.getPreferredLanguage().value(), "English");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 5);

        auto log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<StringPtr>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "English");
        EXPECT_EQ(*log->getNewValueStr(), "English");

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(PersonFields::PreferredLanguage);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);

        // del value
        person.setPreferredLanguage(std::nullopt, changer);

        SCOPED_TRACE("Value check");
        EXPECT_FALSE(person.getPreferredLanguage().has_value());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 6);

        log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto old_value = std::get<StringPtr>(log->getOldValue().value());
        EXPECT_EQ(*old_value, "English");
        EXPECT_EQ(*log->getOldValueStr(), "English");

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(PersonTest, SetBirthday)
    {
        // add value
        DatePtr new_birthday = std::make_shared<Date>(2000, 1, 1, 0, 0);

        person.setBirthday(new_birthday, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(person.getBirthday(), new_birthday);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 7);

        auto log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Date);
        auto new_value = std::get<DatePtr>(log->getNewValue().value());
        EXPECT_EQ(new_value, new_birthday);
        EXPECT_EQ(*log->getNewValueStr(), "1 Jan 2000 0:00");

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(PersonFields::Birthday);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);

        // del value
        person.setBirthday(nullptr, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(
            person.getBirthday(), nullptr
        );  // Исправлено: getBirthday вместо getPreferredLanguage

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 8);

        log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Date);
        auto old_value = std::get<DatePtr>(log->getOldValue().value());
        EXPECT_EQ(old_value, new_birthday);
        EXPECT_EQ(*log->getOldValueStr(), "1 Jan 2000 0:00");

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(PersonTest, SetPhoneNumber)
    {
        // Add value
        PhoneNumberPtr new_phone = std::make_shared<PhoneNumber>("88005553535");

        person._setPhoneNumber(new_phone, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(person.getPhoneNumber(), new_phone);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 9);

        auto log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::PhoneNumber);
        auto new_value = std::get<PhoneNumberPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value, new_phone);
        EXPECT_EQ(*log->getNewValueStr(), "88005553535");

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(PersonFields::PhoneNumber);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);

        // Del value
        person._setPhoneNumber(nullptr, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(person.getPhoneNumber(), nullptr);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 10);

        log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::PhoneNumber);
        auto old_value = std::get<PhoneNumberPtr>(log->getOldValue().value());
        EXPECT_EQ(old_value, new_phone);
        EXPECT_EQ(*log->getOldValueStr(), "88005553535");

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(PersonTest, SetAddress)
    {
        // add value
        AddressPtr new_address =
            std::make_shared<Address>("New Country", "New City", "New Street", "", "", "");

        person.setAddress(new_address, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(person.getAddress(), new_address);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 11);

        auto log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Address);
        auto new_value = std::get<AddressPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value, new_address);
        EXPECT_EQ(*log->getNewValueStr(), "New Country New City New Street ");

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(PersonFields::Address);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);

        // del value
        person.setAddress(nullptr, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(person.getAddress(), nullptr);  // Исправлено: getAddress вместо getPhoneNumber

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 12);

        log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Address);
        auto old_value = std::get<AddressPtr>(log->getOldValue().value());
        EXPECT_EQ(old_value, new_address);
        EXPECT_EQ(*log->getOldValueStr(), "New Country New City New Street ");

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(PersonTest, SetEmail)
    {
        // add value
        person._setEmail("test@example.com", changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(person.getEmail(), "test@example.com");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 13);

        auto log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<StringPtr>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "test@example.com");
        EXPECT_EQ(*log->getNewValueStr(), "test@example.com");

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(PersonFields::Email);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);

        // del value
        person._setEmail(std::nullopt, changer);

        SCOPED_TRACE("Value check");
        EXPECT_FALSE(person.getEmail().has_value());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 14);

        log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto old_value = std::get<StringPtr>(log->getOldValue().value());
        EXPECT_EQ(*old_value, "test@example.com");
        EXPECT_EQ(*log->getOldValueStr(), "test@example.com");

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(PersonTest, SetGender)
    {
        EXPECT_EQ(person.getGender(), Gender::unknown);

        person.setGender(Gender::male, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(person.getGender(), Gender::male);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 15);

        auto log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Gender);
        auto old_value = std::get<Gender>(log->getOldValue().value());
        EXPECT_EQ(old_value, Gender::unknown);
        EXPECT_EQ(*log->getOldValueStr(), "Unknown");

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Gender);
        auto new_value = std::get<Gender>(log->getNewValue().value());
        EXPECT_EQ(new_value, Gender::male);
        EXPECT_EQ(*log->getNewValueStr(), "Male");

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(PersonFields::Gender);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(PersonTest, AddDelRelatedDeals)
    {
        auto deal_ptr = std::make_shared<Deal>(BigUint("1"));
        deal_ptr->changeTitle("Сделка #100500", nullptr);

        person.addRelatedDeals(deal_ptr, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(person.getRelatedDeals().back()->getId(), BigUint("1"));

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 16);

        auto log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Deal);
        auto new_value = std::get<DealPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value, deal_ptr);
        EXPECT_EQ(*log->getNewValueStr(), "Сделка #100500");

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(PersonFields::RelatedDeals);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);

        person.delRelatedDeals(deal_ptr, changer);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 17);

        log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Deal);
        auto old_value = std::get<DealPtr>(log->getOldValue().value());
        EXPECT_EQ(old_value, deal_ptr);
        EXPECT_EQ(*log->getOldValueStr(), "Сделка #100500");

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Remove);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(PersonTest, AddDelMorePhoneNumber)
    {
        auto phone = PhoneNumber("88005553535");
        person._addMorePhoneNumber(phone, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(person.getMorePhoneNumbers().back().getNumber(), "88005553535");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 18);

        auto log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::PhoneNumber);
        auto new_value = std::get<PhoneNumberPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value->getNumber(), "88005553535");
        EXPECT_EQ(*log->getNewValueStr(), std::string("88005553535"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(PersonFields::MorePhoneNumber);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);

        person._delMorePhoneNumber(0, changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(person.getMorePhoneNumbers().empty());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 19);

        log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::PhoneNumber);
        auto old_value = std::get<PhoneNumberPtr>(log->getOldValue().value());
        EXPECT_EQ(old_value->getNumber(), "88005553535");
        EXPECT_EQ(*log->getOldValueStr(), std::string("88005553535"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Remove);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(PersonTest, AddDelMoreAddress)
    {
        auto address = Address("USA", "Wasilla", "900 Lanark Dr", "", "", "");
        person.addMoreAddress(address, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(person.getMoreAddresses().back().getCountry(), "USA");
        EXPECT_EQ(person.getMoreAddresses().back().getCity(), "Wasilla");
        EXPECT_EQ(person.getMoreAddresses().back().getStreet(), "900 Lanark Dr");
        EXPECT_EQ(person.getMoreAddresses().back().getHouse(), "");
        EXPECT_EQ(person.getMoreAddresses().back().getApartment(), "");
        EXPECT_EQ(person.getMoreAddresses().back().getPostalCode(), "");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 20);

        auto log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Address);
        auto new_value = std::get<AddressPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value->getCountry(), "USA");
        EXPECT_EQ(new_value->getCity(), "Wasilla");
        EXPECT_EQ(new_value->getStreet(), "900 Lanark Dr");
        EXPECT_EQ(*log->getNewValueStr(), std::string("USA Wasilla 900 Lanark Dr "));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(PersonFields::MoreAddress);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);

        person.delMoreAddress(0, changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(person.getMoreAddresses().empty());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 21);

        log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Address);
        auto old_value = std::get<AddressPtr>(log->getOldValue().value());
        EXPECT_EQ(old_value->getCountry(), "USA");
        EXPECT_EQ(old_value->getCity(), "Wasilla");
        EXPECT_EQ(old_value->getStreet(), "900 Lanark Dr");
        EXPECT_EQ(*log->getOldValueStr(), std::string("USA Wasilla 900 Lanark Dr "));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Remove);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(PersonTest, AddDelMoreEmails)
    {
        person._addMoreEmails("test_email@mail.com", changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(person.getMoreEmails().back(), "test_email@mail.com");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 22);

        auto log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<StringPtr>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "test_email@mail.com");
        EXPECT_EQ(*log->getNewValueStr(), std::string("test_email@mail.com"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(PersonFields::MoreEmail);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);

        person._delMoreEmails(0, changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(person.getMoreEmails().empty());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 23);

        log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto old_value = std::get<StringPtr>(log->getOldValue().value());
        EXPECT_EQ(*old_value, "test_email@mail.com");
        EXPECT_EQ(*log->getOldValueStr(), std::string("test_email@mail.com"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Remove);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(PersonTest, AddDelMoreDocument)
    {
        auto document_ptr = std::make_shared<Document>(BigUint("1"));
        document_ptr->setDocumentTitle("Title", nullptr);

        person.addOtherDocument(document_ptr, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(person.getOtherDocuments().back()->getId(), BigUint("1"));

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 24);

        auto log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Document);
        auto new_value = std::get<DocumentPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value, document_ptr);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Title"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(PersonFields::OtherDocuments);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);

        person.delOtherDocument(0, changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(person.getOtherDocuments().empty());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 25);

        log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Document);
        auto old_value = std::get<DocumentPtr>(log->getOldValue().value());
        EXPECT_EQ(old_value, document_ptr);
        EXPECT_EQ(*log->getOldValueStr(), std::string("Title"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Remove);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(PersonTest, AddDelOtherFile)
    {
        auto file_ptr = std::make_shared<FileMetadata>(BigUint("1"));
        file_ptr->setFileName("File name", nullptr);

        person.addOtherFile(file_ptr, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(person.getOtherFiles().back()->getId(), BigUint("1"));

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 26);

        auto log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::FileMetadata);
        auto new_value = std::get<FileMetadataPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value, file_ptr);
        EXPECT_EQ(*log->getNewValueStr(), std::string("File name"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(PersonFields::OtherFiles);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);

        person.delOtherFile(0, changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(person.getOtherFiles().empty());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 27);

        log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::FileMetadata);
        auto old_value = std::get<FileMetadataPtr>(log->getOldValue().value());
        EXPECT_EQ(old_value, file_ptr);
        EXPECT_EQ(*log->getOldValueStr(), std::string("File name"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Remove);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(PersonTest, AddDelInteraction)
    {
        std::shared_ptr<BaseInteraction> interaction_ptr = std::make_shared<Meeting>(BigUint("1"));
        interaction_ptr->setTitle("Title", nullptr);

        person.addInteraction(interaction_ptr, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(person.getInteractionHistory().back()->getId(), BigUint("1"));

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 28);

        auto log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::BaseInteraction);
        auto new_value = std::get<InteractionPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value, interaction_ptr);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Title"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(PersonFields::InteractionHistory);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);

        person.delInteraction(0, changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(person.getInteractionHistory().empty());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 29);

        log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::BaseInteraction);
        auto old_value = std::get<InteractionPtr>(log->getOldValue().value());
        EXPECT_EQ(old_value, interaction_ptr);
        EXPECT_EQ(*log->getOldValueStr(), std::string("Title"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Remove);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(PersonTest, AddDelTag)
    {
        person.addTag("Tag", changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(person.getTags().back(), "Tag");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 30);

        auto log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<StringPtr>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "Tag");
        EXPECT_EQ(*log->getNewValueStr(), std::string("Tag"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(PersonFields::Tags);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);

        person.delTag(0, changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(person.getTags().empty());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 31);

        log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto old_value = std::get<StringPtr>(log->getOldValue().value());
        EXPECT_EQ(*old_value, "Tag");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Tag"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Remove);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(PersonTest, AddDelNote)
    {
        Note note(changer, nullptr, "Title", "Test");
        person.addNote(note, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(person.getNotes().back().getTitle(), "Title");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 32);

        auto log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Note);
        auto new_value = std::get<std::shared_ptr<Note>>(log->getNewValue().value());
        EXPECT_EQ(new_value->getTitle(), "Title");
        EXPECT_EQ(new_value->getText(), "Test");
        EXPECT_EQ(*log->getNewValueStr(), std::string("Title"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(PersonFields::Notes);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);

        person.delNote(0, changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(person.getNotes().empty());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(person.getChangeLogs().size(), 33);

        log = person.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Note);
        auto old_value = std::get<std::shared_ptr<Note>>(log->getOldValue().value());
        EXPECT_EQ(old_value->getTitle(), "Title");
        EXPECT_EQ(old_value->getText(), "Test");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Title"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Remove);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }
}  // namespace unit