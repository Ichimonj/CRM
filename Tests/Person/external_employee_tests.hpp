#include "Person/Employee/external_employee.hpp"
#include "gtest/gtest.h"

namespace unit {
    ExternalEmployee ee(BigUint("90"), "Name", "Surname", std::nullopt);
    TEST(ExternalEmployeeTest, SmallConstructor)
    {
        SCOPED_TRACE("Basic info");
        EXPECT_EQ(ee.getName(), "Name");
        EXPECT_EQ(ee.getSurname(), "Surname");
        EXPECT_FALSE(ee.getPatronymic().has_value());

        SCOPED_TRACE("Company & Role");
        EXPECT_EQ(ee.getCompany(), nullptr);
        EXPECT_FALSE(ee.getJobTitle().has_value());
        EXPECT_FALSE(ee.getDepartment().has_value());
        EXPECT_FALSE(ee.getOtherRole().has_value());

        SCOPED_TRACE("Status & Access");
        EXPECT_EQ(ee.getStatus(), EmployeeStatus::other);
        EXPECT_EQ(ee.getAccessRole(), AccessRole::ReadOnly);

        SCOPED_TRACE("Interaction & Dates");
        EXPECT_EQ(ee.getCurrentInteraction(), nullptr);
        EXPECT_EQ(ee.getLastContactDate(), nullptr);

        SCOPED_TRACE("Time & Preferences");
        EXPECT_EQ(ee.getTimeZone(), 0);
        EXPECT_FALSE(ee.getPreferredContactTime().has_value());

        SCOPED_TRACE("Influence & Money");
        EXPECT_FALSE(ee.getDecisionInfluence().has_value());
        EXPECT_FALSE(ee.getInfluenceScore().has_value());
        EXPECT_EQ(ee.getBudgetAuthority(), nullptr);
        EXPECT_EQ(ee.getSalary(), nullptr);

        SCOPED_TRACE("Collections");
        EXPECT_TRUE(ee.getPainPoints().empty());
        EXPECT_TRUE(ee.getAssignedDeals().empty());
        EXPECT_TRUE(ee.getCompletedDeals().empty());
        EXPECT_TRUE(ee.getAssignedTasks().empty());
        EXPECT_TRUE(ee.getCompletedTasks().empty());

        SCOPED_TRACE("Change logs");
        EXPECT_TRUE(ee.getChangeLogs().empty());
    }

    TEST(ExternalEmployeeTest, SetCompany_SetNewCompany)
    {
        ExternalCompanyPtr company = std::make_shared<ExternalCompany>(BigUint("50001"));
        company->setCompanyName("GlobalTech Solutions", nullptr);

        ee._setCompany(company, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ee.getCompany(), company);
        EXPECT_EQ(ee.getCompany()->getId(), BigUint("50001"));
        EXPECT_EQ(ee.getCompany()->getCompanyName(), "GlobalTech Solutions");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 1);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Company);
        auto new_value = std::get<CompanyPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value, company);
        EXPECT_EQ(*log->getNewValueStr(), std::string("GlobalTech Solutions"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::Company);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetCompany_ChangeCompany)
    {
        ExternalCompanyPtr newCompany = std::make_shared<ExternalCompany>(BigUint("60002"));
        newCompany->setCompanyName("NeoSystems Inc", nullptr);

        ee._setCompany(newCompany, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ee.getCompany(), newCompany);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 2);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Company);
        auto old_value = std::get<CompanyPtr>(log->getOldValue().value());
        EXPECT_EQ(old_value->getCompanyName(), "GlobalTech Solutions");
        EXPECT_EQ(*log->getOldValueStr(), std::string("GlobalTech Solutions"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Company);
        auto new_value = std::get<CompanyPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value, newCompany);
        EXPECT_EQ(*log->getNewValueStr(), std::string("NeoSystems Inc"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::Company);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetCompany_ClearWithNullptr)
    {
        ee._setCompany(nullptr, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ee.getCompany(), nullptr);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 3);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Company);
        auto old_value = std::get<CompanyPtr>(log->getOldValue().value());
        EXPECT_EQ(old_value->getCompanyName(), "NeoSystems Inc");
        EXPECT_EQ(
            *log->getOldValueStr(), std::string("NeoSystems Inc")
        );  // Добавьте если есть строковое представление

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::Company);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, setJobTitle_SetFirstTitle)
    {
        ee._setJobTitle("Senior Account Manager", changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(ee.getJobTitle().has_value());
        EXPECT_EQ(ee.getJobTitle().value(), "Senior Account Manager");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 4);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<StringPtr>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "Senior Account Manager");
        EXPECT_EQ(*log->getNewValueStr(), std::string("Senior Account Manager"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::JobTitle);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, setJobTitle_ChangeTitle)
    {
        ee._setJobTitle("Head of Procurement", changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(ee.getJobTitle().has_value());
        EXPECT_EQ(ee.getJobTitle().value(), "Head of Procurement");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 5);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto old_value = std::get<StringPtr>(log->getOldValue().value());
        EXPECT_EQ(*old_value, "Senior Account Manager");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Senior Account Manager"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<StringPtr>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "Head of Procurement");
        EXPECT_EQ(*log->getNewValueStr(), std::string("Head of Procurement"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::JobTitle);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, setJobTitle_ClearWithNullopt)
    {
        ee._setJobTitle(std::nullopt, changer);

        SCOPED_TRACE("Value check");
        EXPECT_FALSE(ee.getJobTitle().has_value());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 6);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto old_value = std::get<StringPtr>(log->getOldValue().value());
        EXPECT_EQ(*old_value, "Head of Procurement");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Head of Procurement"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::JobTitle);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetDepartment_SetFirstDepartment)
    {
        ee._setDepartment("Sales Development", changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(ee.getDepartment().has_value());
        EXPECT_EQ(ee.getDepartment().value(), "Sales Development");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 7);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<StringPtr>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "Sales Development");
        EXPECT_EQ(*log->getNewValueStr(), std::string("Sales Development"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::Department);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetDepartment_ChangeDepartment)
    {
        ee._setDepartment("Procurement & Vendor Management", changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(ee.getDepartment().has_value());
        EXPECT_EQ(ee.getDepartment().value(), "Procurement & Vendor Management");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 8);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto old_value = std::get<StringPtr>(log->getOldValue().value());
        EXPECT_EQ(*old_value, "Sales Development");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Sales Development"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<StringPtr>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "Procurement & Vendor Management");
        EXPECT_EQ(*log->getNewValueStr(), std::string("Procurement & Vendor Management"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::Department);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetDepartment_ClearWithNullopt)
    {
        ee._setDepartment(std::nullopt, changer);

        SCOPED_TRACE("Value check");
        EXPECT_FALSE(ee.getDepartment().has_value());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 9);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto old_value = std::get<StringPtr>(log->getOldValue().value());
        EXPECT_EQ(*old_value, "Procurement & Vendor Management");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Procurement & Vendor Management"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::Department);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetStatus_SetStandardStatus)
    {
        ee._setStatus(EmployeeStatus::active, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ee.getStatus(), EmployeeStatus::active);
        EXPECT_FALSE(ee.getOtherStatus().has_value());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 10);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::EmployeeStatus);
        auto old_value = std::get<EmployeeStatus>(log->getOldValue().value());
        EXPECT_EQ(old_value, EmployeeStatus::other);
        EXPECT_EQ(*log->getOldValueStr(), std::string("Other"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::EmployeeStatus);
        auto new_value = std::get<EmployeeStatus>(log->getNewValue().value());
        EXPECT_EQ(new_value, EmployeeStatus::active);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Active"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::Status);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetOtherStatus_SwitchToCustom)
    {
        ee._setOtherStatus("Remote Work (Contract)", changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ee.getStatus(), EmployeeStatus::other);
        EXPECT_TRUE(ee.getOtherStatus().has_value());
        EXPECT_EQ(ee.getOtherStatus().value(), "Remote Work (Contract)");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 11);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::EmployeeStatus);
        auto old_value = std::get<EmployeeStatus>(log->getOldValue().value());
        EXPECT_EQ(old_value, EmployeeStatus::active);
        EXPECT_EQ(*log->getOldValueStr(), std::string("Active"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<StringPtr>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "Remote Work (Contract)");
        EXPECT_EQ(*log->getNewValueStr(), std::string("Remote Work (Contract)"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::Status);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetStatus_BackToStandardAfterCustom)
    {
        ee._setStatus(EmployeeStatus::probation, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ee.getStatus(), EmployeeStatus::probation);
        EXPECT_FALSE(ee.getOtherStatus().has_value());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 12);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto old_value = std::get<StringPtr>(log->getOldValue().value());
        EXPECT_EQ(*old_value, "Remote Work (Contract)");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Remote Work (Contract)"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::EmployeeStatus);
        auto new_value = std::get<EmployeeStatus>(log->getNewValue().value());
        EXPECT_EQ(new_value, EmployeeStatus::probation);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Probation"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::Status);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetCurrentInteraction_SetFirstInteraction)
    {
        InteractionPtr interaction = std::make_shared<EmailLetter>(BigUint("90001"));
        interaction->setTitle("Title", nullptr);

        ee.setCurrentInteraction(interaction, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ee.getCurrentInteraction(), interaction);
        EXPECT_EQ(ee.getCurrentInteraction()->getId(), BigUint("90001"));

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 13);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::BaseInteraction);
        auto new_value = std::get<InteractionPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value, interaction);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Title"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::CurrentInteraction);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetCurrentInteraction_ChangeInteraction)
    {
        InteractionPtr newInteraction = std::make_shared<EmailLetter>(BigUint("90002"));
        newInteraction->setTitle("New Title", nullptr);

        ee.setCurrentInteraction(newInteraction, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ee.getCurrentInteraction(), newInteraction);
        EXPECT_EQ(ee.getCurrentInteraction()->getId(), BigUint("90002"));

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 14);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::BaseInteraction);
        auto old_value = std::get<InteractionPtr>(log->getOldValue().value());
        EXPECT_EQ(old_value->getTitle(), "Title");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Title"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::BaseInteraction);
        auto new_value = std::get<InteractionPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value, newInteraction);
        EXPECT_EQ(*log->getNewValueStr(), std::string("New Title"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::CurrentInteraction);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetCurrentInteraction_ClearWithNullptr)
    {
        ee.setCurrentInteraction(nullptr, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ee.getCurrentInteraction(), nullptr);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 15);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::BaseInteraction);
        auto old_value = std::get<InteractionPtr>(log->getOldValue().value());
        EXPECT_EQ(old_value->getTitle(), "New Title");
        EXPECT_EQ(*log->getOldValueStr(), std::string("New Title"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::CurrentInteraction);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetLastContactDate_SetFirstDate)
    {
        DatePtr date = std::make_shared<Date>(2025, 3, 18);

        ee.setLastContactDate(date, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ee.getLastContactDate(), date);
        EXPECT_EQ(ee.getLastContactDate()->getYear(), 2025);
        EXPECT_EQ(ee.getLastContactDate()->getMonth(), 3);
        EXPECT_EQ(ee.getLastContactDate()->getDay(), 18);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 16);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Date);
        auto new_value = std::get<DatePtr>(log->getNewValue().value());
        EXPECT_EQ(new_value, date);
        EXPECT_EQ(*log->getNewValueStr(), std::string("18 Mar 2025 0:00"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::LastContactDate);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetLastContactDate_UpdateToNewerDate)
    {
        DatePtr newerDate = std::make_shared<Date>(2025, 11, 29);

        ee.setLastContactDate(newerDate, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ee.getLastContactDate(), newerDate);
        EXPECT_EQ(ee.getLastContactDate()->getDateStr(), std::string("29 Nov 2025 0:00"));

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 17);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Date);
        auto old_value = std::get<DatePtr>(log->getOldValue().value());
        EXPECT_EQ(old_value->getYear(), 2025);
        EXPECT_EQ(old_value->getMonth(), 3);
        EXPECT_EQ(old_value->getDay(), 18);
        EXPECT_EQ(*log->getOldValueStr(), std::string("18 Mar 2025 0:00"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Date);
        auto new_value = std::get<DatePtr>(log->getNewValue().value());
        EXPECT_EQ(new_value, newerDate);
        EXPECT_EQ(*log->getNewValueStr(), std::string("29 Nov 2025 0:00"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::LastContactDate);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetLastContactDate_ClearWithNullptr)
    {
        ee.setLastContactDate(nullptr, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ee.getLastContactDate(), nullptr);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 18);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Date);
        auto old_value = std::get<DatePtr>(log->getOldValue().value());
        EXPECT_EQ(old_value->getYear(), 2025);
        EXPECT_EQ(old_value->getMonth(), 11);
        EXPECT_EQ(old_value->getDay(), 29);
        EXPECT_EQ(*log->getOldValueStr(), std::string("29 Nov 2025 0:00"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::LastContactDate);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetTimeZone_SetFirstTimeZone)
    {
        ee._setTimeZone(3, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ee.getTimeZone(), 3);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 19);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Int);
        auto old_value = std::get<int>(log->getOldValue().value());
        EXPECT_EQ(old_value, 0);
        EXPECT_EQ(*log->getOldValueStr(), std::string("0"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Int);
        auto new_value = std::get<int>(log->getNewValue().value());
        EXPECT_EQ(new_value, 3);
        EXPECT_EQ(*log->getNewValueStr(), std::string("3"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::TimeZone);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetTimeZone_ChangeToNewYork)
    {
        ee._setTimeZone(-5, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ee.getTimeZone(), -5);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 20);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Int);
        auto old_value = std::get<int>(log->getOldValue().value());
        EXPECT_EQ(old_value, 3);
        EXPECT_EQ(*log->getOldValueStr(), std::string("3"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Int);
        auto new_value = std::get<int>(log->getNewValue().value());
        EXPECT_EQ(new_value, -5);
        EXPECT_EQ(*log->getNewValueStr(), std::string("-5"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::TimeZone);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetTimeZone_ChangeToTokyo)
    {
        ee._setTimeZone(9, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ee.getTimeZone(), 9);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 21);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Int);
        auto old_value = std::get<int>(log->getOldValue().value());
        EXPECT_EQ(old_value, -5);
        EXPECT_EQ(*log->getOldValueStr(), std::string("-5"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Int);
        auto new_value = std::get<int>(log->getNewValue().value());
        EXPECT_EQ(new_value, 9);
        EXPECT_EQ(*log->getNewValueStr(), std::string("9"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::TimeZone);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetPreferredContactTime_SetFirstTime)
    {
        ee.setPreferredContactTime("09:00-12:00 (UTC+3)", changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(ee.getPreferredContactTime().has_value());
        EXPECT_EQ(ee.getPreferredContactTime().value(), "09:00-12:00 (UTC+3)");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 22);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<StringPtr>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "09:00-12:00 (UTC+3)");
        EXPECT_EQ(*log->getNewValueStr(), std::string("09:00-12:00 (UTC+3)"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::PreferredContactTime);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetPreferredContactTime_ChangeToEvening)
    {
        ee.setPreferredContactTime("17:00-20:00 (EST)", changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(ee.getPreferredContactTime().has_value());
        EXPECT_EQ(ee.getPreferredContactTime().value(), "17:00-20:00 (EST)");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 23);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto old_value = std::get<StringPtr>(log->getOldValue().value());
        EXPECT_EQ(*old_value, "09:00-12:00 (UTC+3)");
        EXPECT_EQ(*log->getOldValueStr(), std::string("09:00-12:00 (UTC+3)"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<StringPtr>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "17:00-20:00 (EST)");
        EXPECT_EQ(*log->getNewValueStr(), std::string("17:00-20:00 (EST)"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::PreferredContactTime);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetPreferredContactTime_ClearWithNullopt)
    {
        ee.setPreferredContactTime(std::nullopt, changer);

        SCOPED_TRACE("Value check");
        EXPECT_FALSE(ee.getPreferredContactTime().has_value());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 24);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto old_value = std::get<StringPtr>(log->getOldValue().value());
        EXPECT_EQ(*old_value, "17:00-20:00 (EST)");
        EXPECT_EQ(*log->getOldValueStr(), std::string("17:00-20:00 (EST)"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::PreferredContactTime);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetDecisionInfluence_SetHighInfluence)
    {
        ee._setDecisionInfluence(ExternalEmployee::InfluenceLevel::High, changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(ee.getDecisionInfluence().has_value());
        EXPECT_EQ(ee.getDecisionInfluence().value(), ExternalEmployee::InfluenceLevel::High);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 25);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::InfluenceLevel);
        auto new_value = std::get<ExternalEmployee::InfluenceLevel>(log->getNewValue().value());
        EXPECT_EQ(new_value, ExternalEmployee::InfluenceLevel::High);
        EXPECT_EQ(*log->getNewValueStr(), std::string("High"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::DecisionInfluence);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetDecisionInfluence_ChangeToCritical)
    {
        ee._setDecisionInfluence(ExternalEmployee::InfluenceLevel::Critical, changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(ee.getDecisionInfluence().has_value());
        EXPECT_EQ(ee.getDecisionInfluence().value(), ExternalEmployee::InfluenceLevel::Critical);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 26);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::InfluenceLevel);
        auto old_value = std::get<ExternalEmployee::InfluenceLevel>(log->getOldValue().value());
        EXPECT_EQ(old_value, ExternalEmployee::InfluenceLevel::High);
        EXPECT_EQ(*log->getOldValueStr(), std::string("High"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::InfluenceLevel);
        auto new_value = std::get<ExternalEmployee::InfluenceLevel>(log->getNewValue().value());
        EXPECT_EQ(new_value, ExternalEmployee::InfluenceLevel::Critical);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Critical"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::DecisionInfluence);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetDecisionInfluence_DowngradeToLow)
    {
        ee._setDecisionInfluence(ExternalEmployee::InfluenceLevel::Low, changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(ee.getDecisionInfluence().has_value());
        EXPECT_EQ(ee.getDecisionInfluence().value(), ExternalEmployee::InfluenceLevel::Low);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 27);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::InfluenceLevel);
        auto old_value = std::get<ExternalEmployee::InfluenceLevel>(log->getOldValue().value());
        EXPECT_EQ(old_value, ExternalEmployee::InfluenceLevel::Critical);
        EXPECT_EQ(*log->getOldValueStr(), std::string("Critical"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::InfluenceLevel);
        auto new_value = std::get<ExternalEmployee::InfluenceLevel>(log->getNewValue().value());
        EXPECT_EQ(new_value, ExternalEmployee::InfluenceLevel::Low);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Low"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::DecisionInfluence);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetDecisionInfluence_ClearWithNullopt)
    {
        ee._setDecisionInfluence(std::nullopt, changer);

        SCOPED_TRACE("Value check");
        EXPECT_FALSE(ee.getDecisionInfluence().has_value());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 28);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::InfluenceLevel);
        auto old_value = std::get<ExternalEmployee::InfluenceLevel>(log->getOldValue().value());
        EXPECT_EQ(old_value, ExternalEmployee::InfluenceLevel::Low);
        EXPECT_EQ(*log->getOldValueStr(), std::string("Low"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::DecisionInfluence);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetInfluenceScore_SetFirstScore)
    {
        ee.setInfluenceScore(87.5, changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(ee.getInfluenceScore().has_value());
        EXPECT_DOUBLE_EQ(ee.getInfluenceScore().value(), 87.5);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 29);

        auto log = ee.getChangeLogs().back();

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
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::InfluenceScore);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetInfluenceScore_UpdateToHigher)
    {
        ee.setInfluenceScore(94.2, changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(ee.getInfluenceScore().has_value());
        EXPECT_DOUBLE_EQ(ee.getInfluenceScore().value(), 94.2);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 30);

        auto log = ee.getChangeLogs().back();

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
        EXPECT_DOUBLE_EQ(new_value, 94.2);
        EXPECT_EQ(*log->getNewValueStr(), std::string("94.2"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::InfluenceScore);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetInfluenceScore_ClearWithNullopt)
    {
        ee.setInfluenceScore(std::nullopt, changer);

        SCOPED_TRACE("Value check");
        EXPECT_FALSE(ee.getInfluenceScore().has_value());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 31);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Double);
        auto old_value = std::get<double>(log->getOldValue().value());
        EXPECT_DOUBLE_EQ(old_value, 94.2);
        EXPECT_EQ(*log->getOldValueStr(), std::string("94.2"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::InfluenceScore);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetBudgetAuthority_SetFirstAuthority)
    {
        MoneyPtr budget = std::make_shared<Money>("750000.00");

        ee.setBudgetAuthority(budget, changer);

        SCOPED_TRACE("Value check");
        EXPECT_NE(ee.getBudgetAuthority(), nullptr);
        EXPECT_EQ(ee.getBudgetAuthority()->num, "750000.00");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 32);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Money);
        auto new_value = std::get<MoneyPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value, budget);
        EXPECT_EQ(*log->getNewValueStr(), std::string("750000.00 USD"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::BudgetAuthority);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetBudgetAuthority_IncreaseAuthority)
    {
        MoneyPtr higherBudget = std::make_shared<Money>("2000000.00");

        ee.setBudgetAuthority(higherBudget, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ee.getBudgetAuthority(), higherBudget);
        EXPECT_EQ(ee.getBudgetAuthority()->num, "2000000.00");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 33);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Money);
        auto old_value = std::get<MoneyPtr>(log->getOldValue().value());
        EXPECT_EQ(old_value->num, "750000.00");
        EXPECT_EQ(*log->getOldValueStr(), std::string("750000.00 USD"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Money);
        auto new_value = std::get<MoneyPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value, higherBudget);
        EXPECT_EQ(*log->getNewValueStr(), std::string("2000000.00 USD"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::BudgetAuthority);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetBudgetAuthority_ClearWithNullptr)
    {
        ee.setBudgetAuthority(nullptr, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ee.getBudgetAuthority(), nullptr);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 34);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Money);
        auto old_value = std::get<MoneyPtr>(log->getOldValue().value());
        EXPECT_EQ(old_value->num, "2000000.00");
        EXPECT_EQ(*log->getOldValueStr(), std::string("2000000.00 USD"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::BudgetAuthority);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetSalary_SetFirstSalary)
    {
        MoneyPtr salary = std::make_shared<Money>("180000.00");

        ee.setSalary(salary, changer);

        SCOPED_TRACE("Value check");
        EXPECT_NE(ee.getSalary(), nullptr);
        EXPECT_EQ(ee.getSalary()->num, "180000.00");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 35);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Money);
        auto new_value = std::get<MoneyPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value, salary);
        EXPECT_EQ(*log->getNewValueStr(), std::string("180000.00 USD"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::Salary);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetSalary_RaiseSalary)
    {
        MoneyPtr newSalary = std::make_shared<Money>("225000.00");

        ee.setSalary(newSalary, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ee.getSalary(), newSalary);
        EXPECT_EQ(ee.getSalary()->num, "225000.00");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 36);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Money);
        auto old_value = std::get<MoneyPtr>(log->getOldValue().value());
        EXPECT_EQ(old_value->num, "180000.00");
        EXPECT_EQ(*log->getOldValueStr(), std::string("180000.00 USD"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Money);
        auto new_value = std::get<MoneyPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value, newSalary);
        EXPECT_EQ(*log->getNewValueStr(), std::string("225000.00 USD"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::Salary);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, SetSalary_ClearWithNullptr)
    {
        ee.setSalary(nullptr, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ee.getSalary(), nullptr);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 37);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Money);
        auto old_value = std::get<MoneyPtr>(log->getOldValue().value());
        EXPECT_EQ(old_value->num, "225000.00");
        EXPECT_EQ(*log->getOldValueStr(), std::string("225000.00 USD"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::Salary);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, AddPainPoint_FirstPain)
    {
        ee.addPainPoint("Long approval cycles (45+ days)", changer);

        SCOPED_TRACE("Value check");
        ASSERT_FALSE(ee.getPainPoints().empty());
        EXPECT_EQ(ee.getPainPoints().size(), 1);
        EXPECT_EQ(ee.getPainPoints()[0], "Long approval cycles (45+ days)");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 38);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<StringPtr>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "Long approval cycles (45+ days)");
        EXPECT_EQ(*log->getNewValueStr(), std::string("Long approval cycles (45+ days)"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::PainPoints);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, AddPainPoint_SecondPain)
    {
        ee.addPainPoint("Budget frozen until Q3", changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ee.getPainPoints().size(), 2);
        EXPECT_EQ(ee.getPainPoints()[1], "Budget frozen until Q3");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 39);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<StringPtr>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "Budget frozen until Q3");
        EXPECT_EQ(*log->getNewValueStr(), std::string("Budget frozen until Q3"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::PainPoints);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, DelPainPoint_RemoveFirstPain)
    {
        ee.delPainPoint(0, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ee.getPainPoints().size(), 1);
        EXPECT_EQ(ee.getPainPoints()[0], "Budget frozen until Q3");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 40);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto old_value = std::get<StringPtr>(log->getOldValue().value());
        EXPECT_EQ(*old_value, "Long approval cycles (45+ days)");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Long approval cycles (45+ days)"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::PainPoints);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Remove);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    DealPtr deal3 = std::make_shared<Deal>(BigUint("12001"));
    TEST(ExternalEmployeeTest, AddAssignedDeal_FirstDeal)
    {
        deal3->_changeTitle("Title1", nullptr);

        ee.addAssignedDeal(deal3, changer);

        SCOPED_TRACE("Value check");
        ASSERT_FALSE(ee.getAssignedDeals().empty());
        EXPECT_EQ(ee.getAssignedDeals().size(), 1);
        EXPECT_EQ(ee.getAssignedDeals()[0].lock(), deal3);
        EXPECT_EQ(ee.getAssignedDeals()[0].lock()->getId(), BigUint("12001"));

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 42);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::WeakDeal);
        auto new_value = std::get<WeakDealPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value.lock(), deal3);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Title1"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(PersonFields::RelatedDeals);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);

        log = ee.getChangeLogs()[ee.getChangeLogs().size() - 2];

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::WeakDeal);
        auto new_value2 = std::get<WeakDealPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value2.lock(), deal3);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Title1"));

        SCOPED_TRACE("Field");
        field = ChangeLog::FieldVariant(ExternalEmployeeFields::AssignedDeals);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    DealPtr deal4 = std::make_shared<Deal>(BigUint("12005"));
    TEST(ExternalEmployeeTest, AddAssignedDeal_SecondDeal)
    {
        deal4->_changeTitle("Title2", nullptr);

        ee.addAssignedDeal(deal4, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ee.getAssignedDeals().size(), 2);
        EXPECT_EQ(ee.getAssignedDeals()[1].lock()->getId(), BigUint("12005"));

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 44);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::WeakDeal);
        auto new_value = std::get<WeakDealPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value.lock(), deal4);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Title2"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(PersonFields::RelatedDeals);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);

        log = ee.getChangeLogs()[ee.getChangeLogs().size() - 2];

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::WeakDeal);
        auto new_value2 = std::get<WeakDealPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value2.lock(), deal4);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Title2"));

        SCOPED_TRACE("Field");
        field = ChangeLog::FieldVariant(ExternalEmployeeFields::AssignedDeals);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, DelAssignedDeal_RemoveFirstDeal)
    {
        ee.delAssignedDeal(0, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ee.getAssignedDeals().size(), 1);
        EXPECT_EQ(ee.getAssignedDeals()[0].lock()->getId(), BigUint("12005"));

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 46);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::WeakDeal);
        auto old_value = std::get<WeakDealPtr>(log->getOldValue().value());
        EXPECT_EQ(old_value.lock()->getTitle(), "Title1");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Title1"));

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
        EXPECT_EQ(log->getChanger().lock(), changer);

        log = ee.getChangeLogs()[ee.getChangeLogs().size() - 2];

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::WeakDeal);
        auto old_value2 = std::get<WeakDealPtr>(log->getOldValue().value());
        EXPECT_EQ(old_value2.lock()->getTitle(), "Title1");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Title1"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        field = ChangeLog::FieldVariant(ExternalEmployeeFields::AssignedDeals);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Remove);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    DealPtr deal5 = std::make_shared<Deal>(BigUint("13001"));
    TEST(ExternalEmployeeTest, AddCompletedDeal_FirstDeal)
    {
        deal5->_changeTitle("Closed-Won: Enterprise License 2025", nullptr);

        ee.addCompletedDeal(deal5, changer);

        SCOPED_TRACE("Value check");
        ASSERT_FALSE(ee.getCompletedDeals().empty());
        EXPECT_EQ(ee.getCompletedDeals().size(), 1);
        EXPECT_EQ(ee.getCompletedDeals()[0].lock(), deal5);
        EXPECT_EQ(ee.getCompletedDeals()[0].lock()->getId(), BigUint("13001"));

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 48);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("RelatedDeals log - Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("RelatedDeals log - New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::WeakDeal);
        auto new_value = std::get<WeakDealPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value.lock(), deal5);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Closed-Won: Enterprise License 2025"));

        SCOPED_TRACE("RelatedDeals log - Field");
        auto field = ChangeLog::FieldVariant(PersonFields::RelatedDeals);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("RelatedDeals log - Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);

        SCOPED_TRACE("RelatedDeals log - Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);

        log = ee.getChangeLogs()[ee.getChangeLogs().size() - 2];

        SCOPED_TRACE("CompletedDeals log - Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("CompletedDeals log - New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::WeakDeal);
        auto new_value2 = std::get<WeakDealPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value2.lock(), deal5);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Closed-Won: Enterprise License 2025"));

        SCOPED_TRACE("CompletedDeals log - Field");
        field = ChangeLog::FieldVariant(ExternalEmployeeFields::CompletedDeals);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("CompletedDeals log - Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);

        SCOPED_TRACE("CompletedDeals log - Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, DelCompletedDeal_RemoveOnlyDeal)
    {
        ee.delCompletedDeal(0, changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(ee.getCompletedDeals().empty());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 50);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("RelatedDeals remove log - Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::WeakDeal);
        auto old_value = std::get<WeakDealPtr>(log->getOldValue().value());
        EXPECT_EQ(old_value.lock()->getTitle(), "Closed-Won: Enterprise License 2025");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Closed-Won: Enterprise License 2025"));

        SCOPED_TRACE("RelatedDeals remove log - New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("RelatedDeals remove log - Field");
        auto field = ChangeLog::FieldVariant(PersonFields::RelatedDeals);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("RelatedDeals remove log - Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Remove);

        SCOPED_TRACE("RelatedDeals remove log - Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);

        log = ee.getChangeLogs()[ee.getChangeLogs().size() - 2];

        SCOPED_TRACE("CompletedDeals remove log - Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::WeakDeal);
        auto old_value2 = std::get<WeakDealPtr>(log->getOldValue().value());
        EXPECT_EQ(old_value2.lock()->getTitle(), "Closed-Won: Enterprise License 2025");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Closed-Won: Enterprise License 2025"));

        SCOPED_TRACE("CompletedDeals remove log - New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("CompletedDeals remove log - Field");
        field = ChangeLog::FieldVariant(ExternalEmployeeFields::CompletedDeals);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("CompletedDeals remove log - Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Remove);

        SCOPED_TRACE("CompletedDeals remove log - Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, AddCompletedTask_FirstTask)
    {
        TaskPtr task1 = std::make_shared<Task>(BigUint("50001"));
        task1->setTitle("Onboarding completed: NDA signed", nullptr);

        ee.addCompletedTask(task1, changer);

        SCOPED_TRACE("Value check");
        ASSERT_FALSE(ee.getCompletedTasks().empty());
        EXPECT_EQ(ee.getCompletedTasks().size(), 1);
        EXPECT_EQ(ee.getCompletedTasks()[0], task1);
        EXPECT_EQ(ee.getCompletedTasks()[0]->getId(), BigUint("50001"));

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 51);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Task);
        auto new_value = std::get<TaskPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value, task1);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Onboarding completed: NDA signed"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::CompletedTasks);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, AddCompletedTask_SecondTask)
    {
        TaskPtr task2 = std::make_shared<Task>(BigUint("50005"));
        task2->setTitle("Demo session held (Q4 goals)", nullptr);

        ee.addCompletedTask(task2, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ee.getCompletedTasks().size(), 2);
        EXPECT_EQ(ee.getCompletedTasks()[1]->getId(), BigUint("50005"));

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 52);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Task);
        auto new_value = std::get<TaskPtr>(log->getNewValue().value());
        EXPECT_EQ(new_value, task2);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Demo session held (Q4 goals)"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::CompletedTasks);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }

    TEST(ExternalEmployeeTest, DelCompletedTask_RemoveFirstTask)
    {
        ee.delCompletedTask(0, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ee.getCompletedTasks().size(), 1);
        EXPECT_EQ(ee.getCompletedTasks()[0]->getId(), BigUint("50005"));

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ee.getChangeLogs().size(), 53);

        auto log = ee.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Task);
        auto old_value = std::get<TaskPtr>(log->getOldValue().value());
        EXPECT_EQ(old_value->getTitle(), "Onboarding completed: NDA signed");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Onboarding completed: NDA signed"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(ExternalEmployeeFields::CompletedTasks);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Remove);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger().lock(), changer);
    }
}  // namespace unit