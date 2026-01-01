#include "Employee/internal_employee.hpp"
#include "change_log.hpp"
#include "client.hpp"
#include "gtest/gtest.h"

namespace unit {
    Client client2(BigUint("1999"), "Name", "Surname", std::nullopt);

    TEST(ClientTest, SmallConstructor)
    {
        EXPECT_EQ(client2.getName(), "Name");
        EXPECT_EQ(client2.getSurname(), "Surname");
        EXPECT_EQ(client2.getPatronymic(), std::nullopt);
        EXPECT_EQ(client2.getOwner(), nullptr);

        EXPECT_EQ(client2.getType(), Client::ClientType::other);
        EXPECT_EQ(client2.getOtherType(), std::nullopt);
        EXPECT_EQ(client2.getLeadSource(), Client::LeadSource::other);
        EXPECT_EQ(client2.getOtherLeadSource(), std::nullopt);
        EXPECT_EQ(client2.getMarketingConsent(), false);
        EXPECT_EQ(client2.getCommunicationChannel(), std::nullopt);
        EXPECT_EQ(client2.getReferralCode(), std::nullopt);
        EXPECT_EQ(client2.getCustomerAcquisitionCost(), std::nullopt);
        EXPECT_EQ(client2.getLeadScore(), std::nullopt);
        EXPECT_EQ(client2.getAnnualRevenue(), std::nullopt);
        EXPECT_EQ(client2.getLifetimeValue(), std::nullopt);
        EXPECT_EQ(client2.getInterestedOffers().size(), 0);
    }

    TEST(ClientTest, SetOwner)
    {
        InternalEmployeePtr owner =
            std::make_shared<InternalEmployee>(BigUint("13"), "Owner", "Owner", std::nullopt);
        client2._setOwner(owner, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(client2.getOwner(), owner);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 1);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::InternalEmployee);
        auto new_value = std::get<std::shared_ptr<InternalEmployee>>(log->getNewValue().value());
        EXPECT_EQ(new_value, owner);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Owner Owner"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::Owner);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);

        client2._setOwner(nullptr, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(client2.getOwner(), nullptr);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 2);

        log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::InternalEmployee);
        auto old_value = std::get<std::shared_ptr<InternalEmployee>>(log->getOldValue().value());
        EXPECT_EQ(old_value, owner);
        EXPECT_EQ(*log->getOldValueStr(), std::string("Owner Owner"));

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

    TEST(ClientTest, SetType)
    {
        client2._setType(Client::ClientType::Lead, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(client2.getType(), Client::ClientType::Lead);
        EXPECT_EQ(client2.getOtherType(), std::nullopt);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 3);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::ClientType);
        auto old_value = std::get<Client::ClientType>(log->getOldValue().value());
        EXPECT_EQ(old_value, Client::ClientType::other);
        EXPECT_EQ(*log->getOldValueStr(), std::string("Other"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::ClientType);
        auto new_value = std::get<Client::ClientType>(log->getNewValue().value());
        EXPECT_EQ(new_value, Client::ClientType::Lead);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Lead"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::Type);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, SetOtherType_SwitchToCustom)
    {
        client2._setOtherType("Custom Client Type", changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(client2.getType(), Client::ClientType::other);
        EXPECT_EQ(client2.getOtherType().value(), "Custom Client Type");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 4);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::ClientType);
        auto old_value = std::get<Client::ClientType>(log->getOldValue().value());
        EXPECT_EQ(old_value, Client::ClientType::Lead);
        EXPECT_EQ(*log->getOldValueStr(), std::string("Lead"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<std::shared_ptr<std::string>>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "Custom Client Type");
        EXPECT_EQ(*log->getNewValueStr(), std::string("Custom Client Type"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::OtherType);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, SetType_AfterCustom)
    {
        client2._setType(Client::ClientType::Costomer, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(client2.getType(), Client::ClientType::Costomer);
        EXPECT_EQ(client2.getOtherType(), std::nullopt);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 5);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto old_value = std::get<std::shared_ptr<std::string>>(log->getOldValue().value());
        EXPECT_EQ(*old_value, "Custom Client Type");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Custom Client Type"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::ClientType);
        auto new_value = std::get<Client::ClientType>(log->getNewValue().value());
        EXPECT_EQ(new_value, Client::ClientType::Costomer);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Costomer"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::Type);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, SetLeadSource)
    {
        client2._setLeadSource(Client::LeadSource::Referral, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(client2.getLeadSource(), Client::LeadSource::Referral);
        EXPECT_EQ(client2.getOtherLeadSource(), std::nullopt);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 6);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::LeadSource);
        auto old_value = std::get<Client::LeadSource>(log->getOldValue().value());
        EXPECT_EQ(old_value, Client::LeadSource::other);
        EXPECT_EQ(*log->getOldValueStr(), "Other");

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::LeadSource);
        auto new_value = std::get<Client::LeadSource>(log->getNewValue().value());
        EXPECT_EQ(new_value, Client::LeadSource::Referral);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Referral"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::LeadSource);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, SetOtherLeadSource)
    {
        client2._setOtherLeadSource("Partner Event", changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(client2.getLeadSource(), Client::LeadSource::other);
        EXPECT_EQ(client2.getOtherLeadSource().value(), "Partner Event");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 7);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::LeadSource);
        auto old_value = std::get<Client::LeadSource>(log->getOldValue().value());
        EXPECT_EQ(old_value, Client::LeadSource::Referral);
        EXPECT_EQ(*log->getOldValueStr(), std::string("Referral"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<std::shared_ptr<std::string>>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "Partner Event");
        EXPECT_EQ(*log->getNewValueStr(), std::string("Partner Event"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::OtherLeadSource);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, SetLeadSourceAfter)
    {
        client2._setLeadSource(Client::LeadSource::SocialMedia, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(client2.getLeadSource(), Client::LeadSource::SocialMedia);
        EXPECT_EQ(client2.getOtherLeadSource(), std::nullopt);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 8);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto old_value = std::get<std::shared_ptr<std::string>>(log->getOldValue().value());
        EXPECT_EQ(*old_value, "Partner Event");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Partner Event"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::LeadSource);
        auto new_value = std::get<Client::LeadSource>(log->getNewValue().value());
        EXPECT_EQ(new_value, Client::LeadSource::SocialMedia);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Social media"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::LeadSource);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, SetMarketingConsent)
    {
        client2._setMarketingConsent(true, changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(client2.getMarketingConsent());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 9);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Bool);
        auto old_value = std::get<bool>(log->getOldValue().value());
        EXPECT_FALSE(old_value);
        EXPECT_EQ(*log->getOldValueStr(), std::string("False"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Bool);
        auto new_value = std::get<bool>(log->getNewValue().value());
        EXPECT_TRUE(new_value);
        EXPECT_EQ(*log->getNewValueStr(), std::string("True"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::MarketingConsent);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, SetCommunicationChannel_SetValue)
    {
        client2.setCommunicationChannel("Telegram", changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(client2.getCommunicationChannel().has_value());
        EXPECT_EQ(client2.getCommunicationChannel().value(), "Telegram");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 10);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<std::shared_ptr<std::string>>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "Telegram");
        EXPECT_EQ(*log->getNewValueStr(), std::string("Telegram"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::CommunicationChannel);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, SetCommunicationChannel_Null)
    {
        client2.setCommunicationChannel(std::nullopt, changer);

        SCOPED_TRACE("Value check");
        EXPECT_FALSE(client2.getCommunicationChannel().has_value());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 11);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto old_value = std::get<std::shared_ptr<std::string>>(log->getOldValue().value());
        EXPECT_EQ(*old_value, "Telegram");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Telegram"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::CommunicationChannel);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, SetReferralCode_SetValue)
    {
        client2.setReferralCode("SUMMER2025", changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(client2.getReferralCode().has_value());
        EXPECT_EQ(client2.getReferralCode().value(), "SUMMER2025");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 12);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<std::shared_ptr<std::string>>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "SUMMER2025");
        EXPECT_EQ(*log->getNewValueStr(), std::string("SUMMER2025"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::ReferralCode);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, SetReferralCode_Null)
    {
        client2.setReferralCode(std::nullopt, changer);

        SCOPED_TRACE("Value check");
        EXPECT_FALSE(client2.getReferralCode().has_value());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 13);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto old_value = std::get<std::shared_ptr<std::string>>(log->getOldValue().value());
        EXPECT_EQ(*old_value, "SUMMER2025");
        EXPECT_EQ(*log->getOldValueStr(), std::string("SUMMER2025"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::ReferralCode);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, SetCustomerAcquisitionCost_SetValue)
    {
        client2.setCustomerAcquisitionCost(Money("2499.99"), changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(client2.getCustomerAcquisitionCost().has_value());
        EXPECT_EQ(client2.getCustomerAcquisitionCost()->num, "2499.99");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 14);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Money);
        auto new_value = std::get<std::shared_ptr<Money>>(log->getNewValue().value());
        EXPECT_EQ(new_value->num, "2499.99");
        EXPECT_EQ(*log->getNewValueStr(), std::string("2499.99 USD"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::CustomerAcquisitionCost);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, SetCustomerAcquisitionCost_Null)
    {
        client2.setCustomerAcquisitionCost(std::nullopt, changer);

        SCOPED_TRACE("Value check");
        EXPECT_FALSE(client2.getCustomerAcquisitionCost().has_value());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 15);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Money);
        auto old_value = std::get<std::shared_ptr<Money>>(log->getOldValue().value());
        EXPECT_EQ(old_value->num, "2499.99");
        EXPECT_EQ(*log->getOldValueStr(), std::string("2499.99 USD"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::CustomerAcquisitionCost);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, SetLeadStatus_SetValue)
    {
        client2._setLeadStatus(Client::LeadStatus::Qualified, changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(client2.getLeadStatus().has_value());
        EXPECT_EQ(client2.getLeadStatus().value(), Client::LeadStatus::Qualified);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 16);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::LeadStatus);
        auto new_value = std::get<Client::LeadStatus>(log->getNewValue().value());
        EXPECT_EQ(new_value, Client::LeadStatus::Qualified);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Qualified"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::LeadStatus);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, SetLeadStatus_ChangeToLost)
    {
        client2._setLeadStatus(Client::LeadStatus::Lost, changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(client2.getLeadStatus().has_value());
        EXPECT_EQ(client2.getLeadStatus().value(), Client::LeadStatus::Lost);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 17);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::LeadStatus);
        auto old_value = std::get<Client::LeadStatus>(log->getOldValue().value());
        EXPECT_EQ(old_value, Client::LeadStatus::Qualified);
        EXPECT_EQ(*log->getOldValueStr(), std::string("Qualified"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::LeadStatus);
        auto new_value = std::get<Client::LeadStatus>(log->getNewValue().value());
        EXPECT_EQ(new_value, Client::LeadStatus::Lost);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Lost"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::LeadStatus);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, SetLeadStatus_ClearWithNullopt)
    {
        client2._setLeadStatus(std::nullopt, changer);

        SCOPED_TRACE("Value check");
        EXPECT_FALSE(client2.getLeadStatus().has_value());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 18);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::LeadStatus);
        auto old_value = std::get<Client::LeadStatus>(log->getOldValue().value());
        EXPECT_EQ(old_value, Client::LeadStatus::Lost);
        EXPECT_EQ(*log->getOldValueStr(), std::string("Lost"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::LeadStatus);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, SetLeadScore_SetValue)
    {
        client2.setLeadScore(87.5, changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(client2.getLeadScore().has_value());
        EXPECT_DOUBLE_EQ(client2.getLeadScore().value(), 87.5);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 19);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Double);
        auto new_value = std::get<double>(log->getNewValue().value());
        EXPECT_DOUBLE_EQ(new_value, 87.5);
        EXPECT_EQ(*log->getNewValueStr(), std::string("87.5"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::LeadScore);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, SetLeadScore_UpdateValue)
    {
        client2.setLeadScore(92.3, changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(client2.getLeadScore().has_value());
        EXPECT_DOUBLE_EQ(client2.getLeadScore().value(), 92.3);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 20);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Double);
        auto old_value = std::get<double>(log->getOldValue().value());
        EXPECT_DOUBLE_EQ(old_value, 87.5);
        EXPECT_EQ(*log->getOldValueStr(), std::string("87.5"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Double);
        auto new_value = std::get<double>(log->getNewValue().value());
        EXPECT_DOUBLE_EQ(new_value, 92.3);
        EXPECT_EQ(*log->getNewValueStr(), std::string("92.3"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::LeadScore);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, SetLeadScore_ClearWithNullopt)
    {
        client2.setLeadScore(std::nullopt, changer);

        SCOPED_TRACE("Value check");
        EXPECT_FALSE(client2.getLeadScore().has_value());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 21);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Double);
        auto old_value = std::get<double>(log->getOldValue().value());
        EXPECT_DOUBLE_EQ(old_value, 92.3);
        EXPECT_EQ(*log->getOldValueStr(), std::string("92.3"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::LeadScore);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, SetAnnualRevenue_SetValue)
    {
        client2.setAnnualRevenue(Money("12500000.00"), changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(client2.getAnnualRevenue().has_value());
        EXPECT_EQ(client2.getAnnualRevenue()->num, "12500000.00");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 22);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Money);
        auto new_value = std::get<std::shared_ptr<Money>>(log->getNewValue().value());
        EXPECT_EQ(new_value->num, "12500000.00");
        EXPECT_EQ(*log->getNewValueStr(), std::string("12500000.00 USD"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::AnnualRevenue);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, SetAnnualRevenue_UpdateValue)
    {
        client2.setAnnualRevenue(Money("18750000.50", ÑountriesCurrencies::EUR), changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(client2.getAnnualRevenue().has_value());
        EXPECT_EQ(client2.getAnnualRevenue()->num, "18750000.50");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 23);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Money);
        auto old_value = std::get<std::shared_ptr<Money>>(log->getOldValue().value());
        EXPECT_EQ(old_value->num, "12500000.00");
        EXPECT_EQ(*log->getOldValueStr(), std::string("12500000.00 USD"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Money);
        auto new_value = std::get<std::shared_ptr<Money>>(log->getNewValue().value());
        EXPECT_EQ(new_value->num, "18750000.50");
        EXPECT_EQ(*log->getNewValueStr(), std::string("18750000.50 EUR"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::AnnualRevenue);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, SetAnnualRevenue_ClearWithNullopt)
    {
        client2.setAnnualRevenue(std::nullopt, changer);

        SCOPED_TRACE("Value check");
        EXPECT_FALSE(client2.getAnnualRevenue().has_value());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 24);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Money);
        auto old_value = std::get<std::shared_ptr<Money>>(log->getOldValue().value());
        EXPECT_EQ(old_value->num, "18750000.50");
        EXPECT_EQ(*log->getOldValueStr(), std::string("18750000.50 EUR"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::AnnualRevenue);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, SetLifetimeValue_SetValue)
    {
        client2.setLifetimeValue(Money("450000.00"), changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(client2.getLifetimeValue().has_value());
        EXPECT_EQ(client2.getLifetimeValue()->num, "450000.00");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 25);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Money);
        auto new_value = std::get<std::shared_ptr<Money>>(log->getNewValue().value());
        EXPECT_EQ(new_value->num, "450000.00");
        EXPECT_EQ(*log->getNewValueStr(), std::string("450000.00 USD"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::LifetimeValue);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, SetLifetimeValue_UpdateValue)
    {
        client2.setLifetimeValue(Money("487920.75", CryptoCurrency::USDT), changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(client2.getLifetimeValue().has_value());
        EXPECT_EQ(client2.getLifetimeValue()->num, "487920.75");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 26);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Money);
        auto old_value = std::get<std::shared_ptr<Money>>(log->getOldValue().value());
        EXPECT_EQ(old_value->num, "450000.00");
        EXPECT_EQ(*log->getOldValueStr(), std::string("450000.00 USD"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Money);
        auto new_value = std::get<std::shared_ptr<Money>>(log->getNewValue().value());
        EXPECT_EQ(new_value->num, "487920.75");
        EXPECT_EQ(*log->getNewValueStr(), std::string("487920.75 USDT"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::LifetimeValue);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, SetLifetimeValue_ClearWithNullopt)
    {
        client2.setLifetimeValue(std::nullopt, changer);

        SCOPED_TRACE("Value check");
        EXPECT_FALSE(client2.getLifetimeValue().has_value());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 27);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Money);
        auto old_value = std::get<std::shared_ptr<Money>>(log->getOldValue().value());
        EXPECT_EQ(old_value->num, "487920.75");
        EXPECT_EQ(*log->getOldValueStr(), std::string("487920.75 USDT"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::LifetimeValue);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, AddOwnedDeal_FirstDeal)
    {
        DealPtr deal1 = std::make_shared<Deal>(BigUint("5001"));
        deal1->changeTitle("Deal1 title", nullptr);

        client2.addOwnedDeal(deal1, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(client2.getOwnedDeals().size(), 1);
        EXPECT_EQ(client2.getOwnedDeals()[0], deal1);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 29);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Deal);
        auto new_value = std::get<DealPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value, deal1);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Deal1 title"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(PersonFields::RelatedDeals);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);

        log = client2.getChangeLogs()[client2.getChangeLogs().size() - 2];

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Deal);
        auto new_value2 = std::get<DealPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value2, deal1);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Deal1 title"));

        SCOPED_TRACE("Field");
        field = ChangeLog::FieldVariant(ClientFields::OwnedDeals);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }
    TEST(ClientTest, AddOwnedDeal_SecondDeal)
    {
        DealPtr deal2 = std::make_shared<Deal>(BigUint("5002"));
        deal2->changeTitle("Deal2 title", nullptr);

        client2.addOwnedDeal(deal2, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(client2.getOwnedDeals().size(), 2);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 31);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Deal);
        auto new_value = std::get<DealPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value, deal2);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Deal2 title"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(PersonFields::RelatedDeals);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);

        log = client2.getChangeLogs()[client2.getChangeLogs().size() - 2];

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Deal);
        auto new_value2 = std::get<DealPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value2, deal2);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Deal2 title"));

        SCOPED_TRACE("Field");
        field = ChangeLog::FieldVariant(ClientFields::OwnedDeals);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, DelOwnedDeal_RemoveFirstDeal)
    {
        client2.delOwnedDeal(0, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(client2.getOwnedDeals().size(), 1);
        EXPECT_EQ(client2.getOwnedDeals().back()->getTitle(), std::string("Deal2 title"));

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 33);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Deal);
        EXPECT_EQ(*log->getOldValueStr(), std::string("Deal1 title"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(PersonFields::RelatedDeals);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Remove);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, AddInterestedOffer_FirstOffer)
    {
        OfferPtr offer1 = std::make_shared<Offer>(
            BigUint("9001"),
            "Premium Package 2025",
            "Annual subscription with full support",
            "Subscription",
            1,
            15.0,
            12999.00
        );

        client2.addInterestedOffer(offer1, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(client2.getInterestedOffers().size(), 1);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 34);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Offer);
        auto new_value = std::get<OfferPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value, offer1);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Premium Package 2025"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::InterestedOffers);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, AddInterestedOffer_SecondOffer)
    {
        OfferPtr offer2 = std::make_shared<Offer>(
            BigUint("9002"), "Enterprise License", std::nullopt, "License", 10, 25.0, 99999.99
        );

        client2.addInterestedOffer(offer2, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(client2.getInterestedOffers().size(), 2);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 35);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Offer);
        auto new_value = std::get<OfferPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value, offer2);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Enterprise License"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::InterestedOffers);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(ClientTest, DelInterestedOffer_RemoveFirstOffer)
    {
        client2.delInterestedOffer(0, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(client2.getInterestedOffers().size(), 1);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(client2.getChangeLogs().size(), 36);

        auto log = client2.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Offer);
        auto old_value = std::get<OfferPtr>(log->getOldValue().value());
        EXPECT_EQ(old_value->getName(), "Premium Package 2025");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Premium Package 2025"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ClientFields::InterestedOffers);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Remove);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }
}  // namespace unit