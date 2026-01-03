#include "ChangeLog/change_log.hpp"
#include "Person/Employee/internal_employee.hpp"
#include "gtest/gtest.h"
#include "memory.h"
namespace unit {
    InternalEmployee ie(BigUint("1"), "Name", "Surname", std::nullopt);

    TEST(InternalEmployeeTest, SmallConstructor)
    {
        InternalEmployee ie(BigUint("1"), "Name", "Surname", std::nullopt);

        EXPECT_EQ(ie.getId(), BigUint("1"));
        EXPECT_EQ(ie.getName(), "Name");
        EXPECT_EQ(ie.getSurname(), "Surname");
        EXPECT_FALSE(ie.getPatronymic().has_value());

        EXPECT_FALSE(ie.getPosition().has_value());
        EXPECT_FALSE(ie.getDepartment().has_value());
        EXPECT_FALSE(ie.getOtherRole().has_value());
        EXPECT_FALSE(ie.getOtherStatus().has_value());
        EXPECT_FALSE(ie.getSalesTerritory().has_value());

        EXPECT_EQ(ie.getAccessRole(), AccessRole::other);
        EXPECT_EQ(ie.getStatus(), EmployeeStatus::other);

        EXPECT_EQ(ie.getLastLoginDate(), nullptr);
        EXPECT_EQ(ie.getLastActionDate(), nullptr);
        EXPECT_EQ(ie.getNextReviewDate(), nullptr);
        EXPECT_EQ(ie.getHireDate(), nullptr);
        EXPECT_EQ(ie.getDismissalDate(), nullptr);

        EXPECT_EQ(ie.getTimeZone(), 0);
        EXPECT_FALSE(ie.getIsActive());

        EXPECT_FALSE(ie.getCommissionRate().has_value());
        EXPECT_EQ(ie.getBaseSalary(), nullptr);
        EXPECT_FALSE(ie.getPerformanceScore().has_value());

        EXPECT_TRUE(ie.getManagedDeals().empty());
        EXPECT_TRUE(ie.getProposedOffers().empty());
        EXPECT_TRUE(ie.getLeads().empty());
        EXPECT_TRUE(ie.getMonthlyQuota().empty());
        EXPECT_TRUE(ie.getTasks().empty());
        EXPECT_TRUE(ie.getDocuments().empty());
        EXPECT_TRUE(ie.getSkills().empty());
        EXPECT_TRUE(ie.getDirectReports().empty());

        EXPECT_EQ(ie.getManager(), nullptr);
    }

    TEST(InternalEmployeeTest, SetManager)
    {
        InternalEmployee manager(BigUint("100"), "Ivan", "StaryBoss", std::nullopt);
        auto             manager_ptr = std::make_shared<InternalEmployee>(manager);

        ie._setManager(manager_ptr, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getManager(), manager_ptr);

        SCOPED_TRACE("ChangeLogs size");
        ASSERT_EQ(ie.getChangeLogs().size(), 1);

        auto& log = ie.getChangeLogs().back();

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        ASSERT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::InternalEmployee);
        auto new_value = std::get<std::shared_ptr<InternalEmployee>>(log->getNewValue().value());
        EXPECT_EQ(new_value, manager_ptr);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Ivan StaryBoss"));

        SCOPED_TRACE("Field");
        EXPECT_EQ(log->getField(), ChangeLog::FieldVariant(InternalEmployeeFields::Manager));

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
    }

    TEST(InternalEmployeeTest, SwapManager)
    {
        InternalEmployee manager2(BigUint("101"), "Dima", "White", std::nullopt);
        auto             manager2_ptr = std::make_shared<InternalEmployee>(manager2);

        ie._setManager(manager2_ptr, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getManager(), manager2_ptr);

        SCOPED_TRACE("ChangeLogs size");
        ASSERT_EQ(ie.getChangeLogs().size(), 2);

        auto& log = ie.getChangeLogs().back();

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::InternalEmployee);
        auto old_value = std::get<InternalEmployeePtr>(log->getOldValue().value());
        EXPECT_EQ(old_value->getId(), "100");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Ivan StaryBoss"));

        SCOPED_TRACE("New value");
        ASSERT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::InternalEmployee);
        auto new_value = std::get<std::shared_ptr<InternalEmployee>>(log->getNewValue().value());
        EXPECT_EQ(new_value, manager2_ptr);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Dima White"));

        SCOPED_TRACE("Field");
        EXPECT_EQ(log->getField(), ChangeLog::FieldVariant(InternalEmployeeFields::Manager));

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
    }

    TEST(InternalEmployeeTest, DelManager)
    {
        ie._setManager(nullptr, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getManager(), nullptr);

        SCOPED_TRACE("ChangeLogs size");
        ASSERT_EQ(ie.getChangeLogs().size(), 3);

        auto& log = ie.getChangeLogs().back();

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::InternalEmployee);
        auto old_value = std::get<std::shared_ptr<InternalEmployee>>(log->getOldValue().value());
        EXPECT_EQ(old_value->getId(), "101");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Dima White"));

        SCOPED_TRACE("New value");
        ASSERT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        EXPECT_EQ(log->getField(), ChangeLog::FieldVariant(InternalEmployeeFields::Manager));

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
    }

    TEST(InternalEmployeeTest, SetPosition)
    {
        ie._setPosition("Senior Developer", changer);

        SCOPED_TRACE("Value check");
        ASSERT_TRUE(ie.getPosition().has_value());
        EXPECT_EQ(ie.getPosition().value(), "Senior Developer");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 4);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<StringPtr>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "Senior Developer");
        EXPECT_EQ(*log->getNewValueStr(), std::string("Senior Developer"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::Position);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, SwapPosition)
    {
        ie._setPosition("Team Lead", changer);

        SCOPED_TRACE("Value check");
        ASSERT_TRUE(ie.getPosition().has_value());
        EXPECT_EQ(ie.getPosition().value(), "Team Lead");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 5);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto old_value = std::get<StringPtr>(log->getOldValue().value());
        EXPECT_EQ(*old_value, "Senior Developer");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Senior Developer"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<StringPtr>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "Team Lead");
        EXPECT_EQ(*log->getNewValueStr(), std::string("Team Lead"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::Position);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, DelPosition)
    {
        ie._setPosition(std::nullopt, changer);

        SCOPED_TRACE("Value check");
        EXPECT_FALSE(ie.getPosition().has_value());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 6);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto old_value = std::get<StringPtr>(log->getOldValue().value());
        EXPECT_EQ(*old_value, "Team Lead");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Team Lead"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::Position);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, SetDepartment)
    {
        ie._setDepartment("Engineering", changer);

        SCOPED_TRACE("Value check");
        ASSERT_TRUE(ie.getDepartment().has_value());
        EXPECT_EQ(ie.getDepartment().value(), "Engineering");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 7);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<StringPtr>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "Engineering");
        EXPECT_EQ(*log->getNewValueStr(), std::string("Engineering"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::Department);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, SwapDepartment)
    {
        ie._setDepartment("Product Management", changer);

        SCOPED_TRACE("Value check");
        ASSERT_TRUE(ie.getDepartment().has_value());
        EXPECT_EQ(ie.getDepartment().value(), "Product Management");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 8);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto old_value = std::get<StringPtr>(log->getOldValue().value());
        EXPECT_EQ(*old_value, "Engineering");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Engineering"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<StringPtr>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "Product Management");
        EXPECT_EQ(*log->getNewValueStr(), std::string("Product Management"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::Department);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, DelDepartment)
    {
        ie._setDepartment(std::nullopt, changer);

        SCOPED_TRACE("Value check");
        EXPECT_FALSE(ie.getDepartment().has_value());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 9);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto old_value = std::get<StringPtr>(log->getOldValue().value());
        EXPECT_EQ(*old_value, "Product Management");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Product Management"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::Department);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, SetRole)
    {
        ie._setAccessRole(AccessRole::Admin, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getAccessRole(), AccessRole::Admin);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 10);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::AccessLevel);
        auto old_value = std::get<AccessRole>(log->getOldValue().value());
        EXPECT_EQ(old_value, AccessRole::other);
        EXPECT_EQ(*log->getOldValueStr(), std::string("Other"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::AccessLevel);
        auto new_value = std::get<AccessRole>(log->getNewValue().value());
        EXPECT_EQ(new_value, AccessRole::Admin);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Administrator"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::Role);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, SetOtherRole)
    {
        ie._setOtherRole("Chief Happiness Officer", changer);

        SCOPED_TRACE("Value check");
        ASSERT_TRUE(ie.getOtherRole().has_value());
        EXPECT_EQ(ie.getOtherRole().value(), "Chief Happiness Officer");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 11);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::AccessLevel);
        auto old_value = std::get<AccessRole>(log->getOldValue().value());
        EXPECT_EQ(old_value, AccessRole::Admin);
        EXPECT_EQ(*log->getOldValueStr(), std::string("Administrator"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<StringPtr>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "Chief Happiness Officer");
        EXPECT_EQ(*log->getNewValueStr(), std::string("Chief Happiness Officer"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::Role);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, SetStatus)
    {
        ie._setStatus(EmployeeStatus::active, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getStatus(), EmployeeStatus::active);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 12);

        auto log = ie.getChangeLogs().back();

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
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::Status);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, SetOtherStatus)
    {
        ie._setOtherStatus("Maternity Leave", changer);

        SCOPED_TRACE("Value check");
        ASSERT_TRUE(ie.getOtherStatus().has_value());
        EXPECT_EQ(ie.getOtherStatus().value(), "Maternity Leave");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 13);

        auto log = ie.getChangeLogs().back();

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
        EXPECT_EQ(*new_value, "Maternity Leave");
        EXPECT_EQ(*log->getNewValueStr(), std::string("Maternity Leave"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::Status);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, SetSalesTerritory_FromNulloptToValue_LogsNewValue)
    {
        ie._setSalesTerritory("EMEA", changer);

        SCOPED_TRACE("Value check");
        ASSERT_TRUE(ie.getSalesTerritory().has_value());
        EXPECT_EQ(ie.getSalesTerritory().value(), "EMEA");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 14);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<StringPtr>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "EMEA");
        EXPECT_EQ(*log->getNewValueStr(), std::string("EMEA"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::SalesTerritory);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, SwapSalesTerritory)
    {
        ie._setSalesTerritory("North America - Enterprise", changer);

        SCOPED_TRACE("Value check");
        ASSERT_TRUE(ie.getSalesTerritory().has_value());
        EXPECT_EQ(ie.getSalesTerritory().value(), "North America - Enterprise");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 15);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto old_value = std::get<StringPtr>(log->getOldValue().value());
        EXPECT_EQ(*old_value, "EMEA");
        EXPECT_EQ(*log->getOldValueStr(), std::string("EMEA"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto new_value = std::get<StringPtr>(log->getNewValue().value());
        EXPECT_EQ(*new_value, "North America - Enterprise");
        EXPECT_EQ(*log->getNewValueStr(), std::string("North America - Enterprise"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::SalesTerritory);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, DelSalesTerritory)
    {
        ie._setSalesTerritory(std::nullopt, changer);

        SCOPED_TRACE("Value check");
        EXPECT_FALSE(ie.getSalesTerritory().has_value());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 16);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto old_value = std::get<StringPtr>(log->getOldValue().value());
        EXPECT_EQ(*old_value, "North America - Enterprise");
        EXPECT_EQ(*log->getOldValueStr(), std::string("North America - Enterprise"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::SalesTerritory);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);

        SCOPED_TRACE("Changer");
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, SetLastLoginDate)
    {
        auto date = std::make_shared<Date>(2025, 12, 4);

        ie.setLastLoginDate(date, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getLastLoginDate(), date);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 17);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Date);
        auto stored_date = std::get<DatePtr>(log->getNewValue().value());
        EXPECT_EQ(stored_date, date);
        EXPECT_EQ(*log->getNewValueStr(), std::string("4 Dec 2025 0:00"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::LastLoginDate);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(log->getChanger(), changer);
    }
    TEST(InternalEmployeeTest, SwapLastLoginDate)
    {
        auto new_date = std::make_shared<Date>(2025, 1, 1);

        ie.setLastLoginDate(new_date, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getLastLoginDate(), new_date);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 18);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value — full object check");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Date);
        auto stored_old = std::get<DatePtr>(log->getOldValue().value());
        EXPECT_EQ(stored_old->getDateStr(), "4 Dec 2025 0:00");
        EXPECT_EQ(*log->getOldValueStr(), std::string("4 Dec 2025 0:00"));

        SCOPED_TRACE("New value — full object check");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Date);
        auto stored_new = std::get<DatePtr>(log->getNewValue().value());
        EXPECT_EQ(stored_new, new_date);
        EXPECT_EQ(*log->getNewValueStr(), std::string("1 Jan 2025 0:00"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::LastLoginDate);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, DelLastLoginDate)
    {
        ie.setLastLoginDate(nullptr, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getLastLoginDate(), nullptr);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 19);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value — full object check");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Date);
        auto stored_old = std::get<DatePtr>(log->getOldValue().value());
        EXPECT_EQ(stored_old->getDateStr(), "1 Jan 2025 0:00");
        EXPECT_EQ(*log->getOldValueStr(), std::string("1 Jan 2025 0:00"));

        SCOPED_TRACE("New value — null");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::LastLoginDate);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(log->getChanger(), changer);
    }
    TEST(InternalEmployeeTest, SetLastActionDate)
    {
        auto date = std::make_shared<Date>(2025, 12, 4);

        ie.setLastActionDate(date, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getLastActionDate(), date);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 20);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Date);
        auto stored_date = std::get<DatePtr>(log->getNewValue().value());
        EXPECT_EQ(stored_date, date);
        EXPECT_EQ(stored_date->getDateStr(), "4 Dec 2025 0:00");
        EXPECT_EQ(*log->getNewValueStr(), std::string("4 Dec 2025 0:00"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::LastActionDate);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(log->getChanger(), changer);
    }
    TEST(InternalEmployeeTest, SwapLastActionDate)
    {
        auto new_date = std::make_shared<Date>(2025, 1, 1);

        ie.setLastActionDate(new_date, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getLastActionDate(), new_date);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 21);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Date);
        auto stored_old = std::get<DatePtr>(log->getOldValue().value());
        EXPECT_EQ(stored_old->getDateStr(), "4 Dec 2025 0:00");
        EXPECT_EQ(*log->getOldValueStr(), std::string("4 Dec 2025 0:00"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Date);
        auto stored_new = std::get<DatePtr>(log->getNewValue().value());
        EXPECT_EQ(stored_new, new_date);
        EXPECT_EQ(stored_new->getDateStr(), "1 Jan 2025 0:00");
        EXPECT_EQ(*log->getNewValueStr(), std::string("1 Jan 2025 0:00"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::LastActionDate);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(log->getChanger(), changer);
    }
    TEST(InternalEmployeeTest, DelLastActionDate)
    {
        ie.setLastActionDate(nullptr, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getLastActionDate(), nullptr);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 22);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Date);
        auto stored_old = std::get<DatePtr>(log->getOldValue().value());
        EXPECT_EQ(stored_old->getDateStr(), "1 Jan 2025 0:00");
        EXPECT_EQ(*log->getOldValueStr(), std::string("1 Jan 2025 0:00"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::LastActionDate);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, SetTimeZone)
    {
        ie._setTimeZone(3, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getTimeZone(), 3);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 23);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Int);
        auto old_value = std::get<int>(log->getOldValue().value());
        EXPECT_EQ(old_value, 0);
        EXPECT_EQ(*log->getOldValueStr(), std::string("0"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Int);
        auto stored_tz = std::get<int>(log->getNewValue().value());
        EXPECT_EQ(stored_tz, 3);
        EXPECT_EQ(*log->getNewValueStr(), std::string("3"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::TimeZone);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(log->getChanger(), changer);
    }
    TEST(InternalEmployeeTest, SwapTimeZone)
    {
        ie._setTimeZone(-8, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getTimeZone(), -8);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 24);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Int);
        auto old_tz = std::get<int>(log->getOldValue().value());
        EXPECT_EQ(old_tz, 3);
        EXPECT_EQ(*log->getOldValueStr(), std::string("3"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Int);
        auto new_tz = std::get<int>(log->getNewValue().value());
        EXPECT_EQ(new_tz, -8);
        EXPECT_EQ(*log->getNewValueStr(), std::string("-8"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::TimeZone);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, SetIsActive)
    {
        ie._setIsActive(true, changer);

        SCOPED_TRACE("Value check");
        EXPECT_TRUE(ie.getIsActive());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 25);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Bool);
        auto old_value = std::get<bool>(log->getOldValue().value());
        EXPECT_FALSE(old_value);
        EXPECT_EQ(*log->getOldValueStr(), std::string("False"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Bool);
        auto stored_value = std::get<bool>(log->getNewValue().value());
        EXPECT_TRUE(stored_value);
        EXPECT_EQ(*log->getNewValueStr(), std::string("True"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::IsActive);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, SetNextReviewDate)
    {
        auto date = std::make_shared<Date>(2025, 12, 4);

        ie.setNextReviewDate(date, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getNextReviewDate(), date);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 26);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Date);
        auto stored_date = std::get<DatePtr>(log->getNewValue().value());
        EXPECT_EQ(stored_date, date);
        EXPECT_EQ(stored_date->getDateStr(), "4 Dec 2025 0:00");
        EXPECT_EQ(*log->getNewValueStr(), std::string("4 Dec 2025 0:00"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::NextReviewDate);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, SwapNextReviewDate)
    {
        auto new_date = std::make_shared<Date>(2026, 6, 15);

        ie.setNextReviewDate(new_date, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getNextReviewDate(), new_date);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 27);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Date);
        auto stored_old = std::get<DatePtr>(log->getOldValue().value());
        EXPECT_EQ(stored_old->getDateStr(), "4 Dec 2025 0:00");
        EXPECT_EQ(*log->getOldValueStr(), std::string("4 Dec 2025 0:00"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Date);
        auto stored_new = std::get<DatePtr>(log->getNewValue().value());
        EXPECT_EQ(stored_new, new_date);
        EXPECT_EQ(stored_new->getDateStr(), "15 Jun 2026 0:00");
        EXPECT_EQ(*log->getNewValueStr(), std::string("15 Jun 2026 0:00"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::NextReviewDate);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, DelNextReviewDate)
    {
        ie.setNextReviewDate(nullptr, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getNextReviewDate(), nullptr);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 28);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Date);
        auto stored_old = std::get<DatePtr>(log->getOldValue().value());
        EXPECT_EQ(stored_old->getDateStr(), "15 Jun 2026 0:00");
        EXPECT_EQ(*log->getOldValueStr(), std::string("15 Jun 2026 0:00"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::NextReviewDate);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, SetHireDate)
    {
        auto date = std::make_shared<Date>(2023, 8, 15);

        ie.setHireDate(date, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getHireDate(), date);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 29);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Date);
        auto stored_date = std::get<DatePtr>(log->getNewValue().value());
        EXPECT_EQ(stored_date, date);
        EXPECT_EQ(stored_date->getDateStr(), "15 Aug 2023 0:00");
        EXPECT_EQ(*log->getNewValueStr(), std::string("15 Aug 2023 0:00"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::HireDate);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, SwapHireDate)
    {
        auto new_date = std::make_shared<Date>(2024, 1, 10);

        ie.setHireDate(new_date, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getHireDate(), new_date);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 30);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Date);
        auto stored_old = std::get<DatePtr>(log->getOldValue().value());
        EXPECT_EQ(stored_old->getDateStr(), "15 Aug 2023 0:00");
        EXPECT_EQ(*log->getOldValueStr(), std::string("15 Aug 2023 0:00"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Date);
        auto stored_new = std::get<DatePtr>(log->getNewValue().value());
        EXPECT_EQ(stored_new, new_date);
        EXPECT_EQ(stored_new->getDateStr(), "10 Jan 2024 0:00");
        EXPECT_EQ(*log->getNewValueStr(), std::string("10 Jan 2024 0:00"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::HireDate);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, DelHireDate)
    {
        ie.setHireDate(nullptr, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getHireDate(), nullptr);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 31);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Date);
        auto stored_old = std::get<DatePtr>(log->getOldValue().value());
        EXPECT_EQ(stored_old->getDateStr(), "10 Jan 2024 0:00");
        EXPECT_EQ(*log->getOldValueStr(), std::string("10 Jan 2024 0:00"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::HireDate);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(log->getChanger(), changer);
    }
    TEST(InternalEmployeeTest, SetDismissalDate)
    {
        auto date = std::make_shared<Date>(2025, 12, 31);

        ie.setDismissalDate(date, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getDismissalDate(), date);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 32);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Date);
        auto stored_date = std::get<DatePtr>(log->getNewValue().value());
        EXPECT_EQ(stored_date, date);
        EXPECT_EQ(stored_date->getDateStr(), "31 Dec 2025 0:00");
        EXPECT_EQ(*log->getNewValueStr(), std::string("31 Dec 2025 0:00"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::DismissalDate);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, SwapDismissalDate)
    {
        auto new_date = std::make_shared<Date>(2026, 3, 1);

        ie.setDismissalDate(new_date, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getDismissalDate(), new_date);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 33);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Date);
        auto stored_old = std::get<DatePtr>(log->getOldValue().value());
        EXPECT_EQ(stored_old->getDateStr(), "31 Dec 2025 0:00");
        EXPECT_EQ(*log->getOldValueStr(), std::string("31 Dec 2025 0:00"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Date);
        auto stored_new = std::get<DatePtr>(log->getNewValue().value());
        EXPECT_EQ(stored_new, new_date);
        EXPECT_EQ(stored_new->getDateStr(), "1 Mar 2026 0:00");
        EXPECT_EQ(*log->getNewValueStr(), std::string("1 Mar 2026 0:00"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::DismissalDate);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, DelDismissalDate)
    {
        ie.setDismissalDate(nullptr, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getDismissalDate(), nullptr);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 34);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Date);
        auto stored_old = std::get<DatePtr>(log->getOldValue().value());
        EXPECT_EQ(stored_old->getDateStr(), "1 Mar 2026 0:00");
        EXPECT_EQ(*log->getOldValueStr(), std::string("1 Mar 2026 0:00"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::DismissalDate);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, SetCommissionRate)
    {
        ie.setCommissionRate(15.5, changer);

        SCOPED_TRACE("Value check");
        ASSERT_TRUE(ie.getCommissionRate().has_value());
        EXPECT_DOUBLE_EQ(ie.getCommissionRate().value(), 15.5);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 35);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value — full check");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Double);
        auto stored_rate = std::get<double>(log->getNewValue().value());
        EXPECT_DOUBLE_EQ(stored_rate, 15.5);
        EXPECT_EQ(*log->getNewValueStr(), std::string("15.5"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::CommissionRate);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, SwapCommissionRate)
    {
        ie.setCommissionRate(7.75, changer);

        SCOPED_TRACE("Value check");
        ASSERT_TRUE(ie.getCommissionRate().has_value());
        EXPECT_DOUBLE_EQ(ie.getCommissionRate().value(), 7.75);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 36);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Double);
        auto old_rate = std::get<double>(log->getOldValue().value());
        EXPECT_DOUBLE_EQ(old_rate, 15.5);
        EXPECT_EQ(*log->getOldValueStr(), std::string("15.5"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Double);
        auto new_rate = std::get<double>(log->getNewValue().value());
        EXPECT_DOUBLE_EQ(new_rate, 7.75);
        EXPECT_EQ(*log->getNewValueStr(), std::string("7.75"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::CommissionRate);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, DelCommissionRate)
    {
        ie.setCommissionRate(std::nullopt, changer);

        SCOPED_TRACE("Value check");
        EXPECT_FALSE(ie.getCommissionRate().has_value());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 37);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Double);
        auto old_rate = std::get<double>(log->getOldValue().value());
        EXPECT_DOUBLE_EQ(old_rate, 7.75);
        EXPECT_EQ(*log->getOldValueStr(), std::string("7.75"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::CommissionRate);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, SetBaseSalary)
    {
        auto salary = std::make_shared<Money>("150000.0");

        ie.setBaseSalary(salary, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getBaseSalary(), salary);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 38);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Money);
        auto stored_money = std::get<MoneyPtr>(log->getNewValue().value());
        EXPECT_EQ(stored_money, salary);
        EXPECT_EQ(stored_money->num, "150000.00");
        EXPECT_EQ(*log->getNewValueStr(), std::string("150000.00 USD"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::BaseSalary);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, SetPerformanceScore)
    {
        ie.setPerformanceScore(92.7, changer);

        SCOPED_TRACE("Value check");
        ASSERT_TRUE(ie.getPerformanceScore().has_value());
        EXPECT_DOUBLE_EQ(ie.getPerformanceScore().value(), 92.7);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 39);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getOldValueStr(), nullptr);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Double);
        auto stored_score = std::get<double>(log->getNewValue().value());
        EXPECT_DOUBLE_EQ(stored_score, 92.7);
        EXPECT_EQ(*log->getNewValueStr(), std::string("92.7"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::PerformanceScore);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, SwapPerformanceScore)
    {
        ie.setPerformanceScore(88.3, changer);

        SCOPED_TRACE("Value check");
        ASSERT_TRUE(ie.getPerformanceScore().has_value());
        EXPECT_DOUBLE_EQ(ie.getPerformanceScore().value(), 88.3);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 40);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Double);
        auto old_score = std::get<double>(log->getOldValue().value());
        EXPECT_DOUBLE_EQ(old_score, 92.7);
        EXPECT_EQ(*log->getOldValueStr(), std::string("92.7"));

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Double);
        auto new_score = std::get<double>(log->getNewValue().value());
        EXPECT_DOUBLE_EQ(new_score, 88.3);
        EXPECT_EQ(*log->getNewValueStr(), std::string("88.3"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::PerformanceScore);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(log->getChanger(), changer);
    }
    TEST(InternalEmployeeTest, DelPerformanceScore)
    {
        ie.setPerformanceScore(std::nullopt, changer);

        SCOPED_TRACE("Value check");
        EXPECT_FALSE(ie.getPerformanceScore().has_value());

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 41);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Double);
        auto old_score = std::get<double>(log->getOldValue().value());
        EXPECT_DOUBLE_EQ(old_score, 88.3);
        EXPECT_EQ(*log->getOldValueStr(), std::string("88.3"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(log->getNewValueStr(), nullptr);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::PerformanceScore);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, AddManagerDeal)
    {
        auto deal = std::make_shared<Deal>(BigUint("14001"));
        deal->changeTitle("Strategic Deal — Bank of Tomorrow", nullptr);

        ie.addManagerDeal(deal, changer);

        SCOPED_TRACE("Value check");
        ASSERT_FALSE(ie.getManagedDeals().empty());
        EXPECT_EQ(ie.getManagedDeals().size(), 1);
        EXPECT_EQ(ie.getManagedDeals()[0], deal);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 43);

        auto log_person = ie.getChangeLogs().back();

        SCOPED_TRACE("Person log");
        EXPECT_FALSE(log_person->getOldValue().has_value());
        EXPECT_EQ(log_person->getOldValueFieldType(), ChangeLog::FieldType::null);

        EXPECT_TRUE(log_person->getNewValue().has_value());
        EXPECT_EQ(log_person->getNewValueFieldType(), ChangeLog::FieldType::Deal);
        auto stored_deal_person = std::get<DealPtr>(log_person->getNewValue().value());
        EXPECT_EQ(stored_deal_person, deal);
        EXPECT_EQ(*log_person->getNewValueStr(), std::string("Strategic Deal — Bank of Tomorrow"));

        EXPECT_EQ(log_person->getField(), ChangeLog::FieldVariant(PersonFields::RelatedDeals));
        EXPECT_EQ(log_person->getAction(), ChangeLog::Action::Add);
        EXPECT_EQ(log_person->getChanger(), changer);

        auto log_manager = ie.getChangeLogs()[ie.getChangeLogs().size() - 2];

        SCOPED_TRACE("Manager log");
        EXPECT_FALSE(log_manager->getOldValue().has_value());
        EXPECT_EQ(log_manager->getOldValueFieldType(), ChangeLog::FieldType::null);

        EXPECT_TRUE(log_manager->getNewValue().has_value());
        EXPECT_EQ(log_manager->getNewValueFieldType(), ChangeLog::FieldType::Deal);
        auto stored_deal_manager = std::get<DealPtr>(log_manager->getNewValue().value());
        EXPECT_EQ(stored_deal_manager, deal);
        EXPECT_EQ(*log_manager->getNewValueStr(), std::string("Strategic Deal — Bank of Tomorrow"));

        EXPECT_EQ(
            log_manager->getField(), ChangeLog::FieldVariant(InternalEmployeeFields::ManagerDeals)
        );
        EXPECT_EQ(log_manager->getAction(), ChangeLog::Action::Add);
        EXPECT_EQ(log_manager->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, SwapManagerDeal)
    {
        auto new_deal = std::make_shared<Deal>(BigUint("14002"));
        new_deal->changeTitle("Mega Deal — Government Contract", nullptr);

        ie.addManagerDeal(new_deal, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getManagedDeals().size(), 2);
        EXPECT_EQ(ie.getManagedDeals()[1], new_deal);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 45);

        auto log_person = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log_person->getOldValue().has_value());
        EXPECT_EQ(log_person->getOldValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log_person->getNewValue().has_value());
        EXPECT_EQ(log_person->getNewValueFieldType(), ChangeLog::FieldType::Deal);
        auto stored_person = std::get<DealPtr>(log_person->getNewValue().value());
        EXPECT_EQ(stored_person, new_deal);
        EXPECT_EQ(*log_person->getNewValueStr(), std::string("Mega Deal — Government Contract"));

        SCOPED_TRACE("Field & Action");
        EXPECT_EQ(log_person->getField(), ChangeLog::FieldVariant(PersonFields::RelatedDeals));
        EXPECT_EQ(log_person->getAction(), ChangeLog::Action::Add);
        EXPECT_EQ(log_person->getChanger(), changer);

        auto log_manager = ie.getChangeLogs()[ie.getChangeLogs().size() - 2];

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log_manager->getOldValue().has_value());
        EXPECT_EQ(log_manager->getOldValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log_manager->getNewValue().has_value());
        EXPECT_EQ(log_manager->getNewValueFieldType(), ChangeLog::FieldType::Deal);
        auto stored_manager = std::get<DealPtr>(log_manager->getNewValue().value());
        EXPECT_EQ(stored_manager, new_deal);
        EXPECT_EQ(*log_manager->getNewValueStr(), std::string("Mega Deal — Government Contract"));

        SCOPED_TRACE("Field & Action");
        EXPECT_EQ(
            log_manager->getField(), ChangeLog::FieldVariant(InternalEmployeeFields::ManagerDeals)
        );
        EXPECT_EQ(log_manager->getAction(), ChangeLog::Action::Add);
        EXPECT_EQ(log_manager->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, DelManagerDeal)
    {
        ie.delManagerDeal(0, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getManagedDeals().size(), 1);
        EXPECT_EQ(ie.getManagedDeals()[0]->getId(), BigUint("14002"));

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 47);

        auto log_person = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log_person->getOldValue().has_value());
        EXPECT_EQ(log_person->getOldValueFieldType(), ChangeLog::FieldType::Deal);
        auto old_deal_person = std::get<DealPtr>(log_person->getOldValue().value());
        EXPECT_EQ(old_deal_person->getId(), BigUint("14001"));
        EXPECT_EQ(*log_person->getOldValueStr(), std::string("Strategic Deal — Bank of Tomorrow"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log_person->getNewValue().has_value());
        EXPECT_EQ(log_person->getNewValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("Field & Action");
        EXPECT_EQ(log_person->getField(), ChangeLog::FieldVariant(PersonFields::RelatedDeals));
        EXPECT_EQ(log_person->getAction(), ChangeLog::Action::Remove);
        EXPECT_EQ(log_person->getChanger(), changer);

        auto log_manager = ie.getChangeLogs()[ie.getChangeLogs().size() - 2];

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log_manager->getOldValue().has_value());
        EXPECT_EQ(log_manager->getOldValueFieldType(), ChangeLog::FieldType::Deal);
        auto old_deal_manager = std::get<DealPtr>(log_manager->getOldValue().value());
        EXPECT_EQ(old_deal_manager->getId(), BigUint("14001"));
        EXPECT_EQ(*log_manager->getOldValueStr(), std::string("Strategic Deal — Bank of Tomorrow"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log_manager->getNewValue().has_value());
        EXPECT_EQ(log_manager->getNewValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("Field & Action");
        EXPECT_EQ(
            log_manager->getField(), ChangeLog::FieldVariant(InternalEmployeeFields::ManagerDeals)
        );
        EXPECT_EQ(log_manager->getAction(), ChangeLog::Action::Remove);
        EXPECT_EQ(log_manager->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, AddProposedOffer)
    {
        auto offer = std::make_shared<Offer>(
            BigUint("8001"), "Premium Support Package", std::nullopt, std::nullopt, 0, 0, 0
        );

        ie.addProposedOffer(offer, changer);

        SCOPED_TRACE("Value check");
        ASSERT_EQ(ie.getProposedOffers().size(), 1);
        EXPECT_EQ(ie.getProposedOffers()[0], offer);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 48);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Offer);
        auto stored_offer = std::get<OfferPtr>(log->getNewValue().value());
        EXPECT_EQ(stored_offer, offer);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Premium Support Package"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::ProposedOffers);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, SwapProposedOffer)
    {
        auto new_offer = std::make_shared<Offer>(
            BigUint("8002"), "Enterprise Bundle", std::nullopt, std::nullopt, 0, 0, 0
        );

        ie.addProposedOffer(new_offer, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getProposedOffers().size(), 2);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 49);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Offer);
        auto stored_offer = std::get<OfferPtr>(log->getNewValue().value());
        EXPECT_EQ(stored_offer, new_offer);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Enterprise Bundle"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::ProposedOffers);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, DelProposedOffer)
    {
        ie.delProposedOffer(0, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getProposedOffers().size(), 1);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 50);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Offer);
        auto stored_offer = std::get<OfferPtr>(log->getOldValue().value());
        EXPECT_EQ(stored_offer->getId(), BigUint("8001"));
        EXPECT_EQ(*log->getOldValueStr(), std::string("Premium Support Package"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::ProposedOffers);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Remove);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, AddLead)
    {
        auto lead = std::make_shared<Client>(BigUint("919"), "Alexander", "Petrov", std::nullopt);

        ie.addLead(lead, changer);

        SCOPED_TRACE("Value check");
        ASSERT_EQ(ie.getLeads().size(), 1);
        EXPECT_EQ(ie.getLeads()[0], lead);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 51);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Client);
        auto stored_lead = std::get<ClientPtr>(log->getNewValue().value());
        EXPECT_EQ(stored_lead, lead);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Alexander Petrov"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::Leads);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, SwapLead)
    {
        auto new_lead = std::make_shared<Client>(BigUint("12"), "Victoria", "Sidorova", "Ivanovna");

        ie.addLead(new_lead, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getLeads().size(), 2);
        EXPECT_EQ(ie.getLeads()[1], new_lead);

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 52);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Client);
        auto stored_lead = std::get<ClientPtr>(log->getNewValue().value());
        EXPECT_EQ(stored_lead, new_lead);
        EXPECT_EQ(*log->getNewValueStr(), std::string("Victoria Sidorova"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::Leads);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, DelLead)
    {
        ie.delLead(0, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getLeads().size(), 1);
        EXPECT_EQ(ie.getLeads()[0]->getName(), "Victoria");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 53);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Client);
        auto stored_lead = std::get<ClientPtr>(log->getOldValue().value());
        EXPECT_EQ(stored_lead->getName(), "Alexander");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Alexander Petrov"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::Leads);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Remove);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, AddMonthlyQuota)
    {
        Money quota("50000");

        ie.addMonthlyQuota(quota, changer);

        SCOPED_TRACE("Value check");
        ASSERT_EQ(ie.getMonthlyQuota().size(), 1);
        EXPECT_EQ(ie.getMonthlyQuota()[0].num, "50000.00");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 54);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Money);
        auto stored_money = std::get<std::shared_ptr<Money>>(log->getNewValue().value());
        EXPECT_EQ(stored_money->num, "50000.00");
        EXPECT_EQ(*log->getNewValueStr(), std::string("50000.00 USD"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::MonthlyQuota);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);
        EXPECT_EQ(log->getChanger(), changer);
    }
    TEST(InternalEmployeeTest, AddMonthlyQuota2)
    {
        Money new_quota("85000");

        ie.addMonthlyQuota(new_quota, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getMonthlyQuota().size(), 2);
        EXPECT_EQ(ie.getMonthlyQuota()[1].num, "85000.00");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 55);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Money);
        auto stored_money = std::get<std::shared_ptr<Money>>(log->getNewValue().value());
        EXPECT_EQ(stored_money->num, "85000.00");
        EXPECT_EQ(*log->getNewValueStr(), std::string("85000.00 USD"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::MonthlyQuota);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);
        EXPECT_EQ(log->getChanger(), changer);
    }
    TEST(InternalEmployeeTest, DelMonthlyQuota)
    {
        ie.delMonthlyQuota(0, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getMonthlyQuota().size(), 1);
        EXPECT_EQ(ie.getMonthlyQuota()[0].num, "85000.00");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 56);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Money);
        auto stored_money = std::get<std::shared_ptr<Money>>(log->getOldValue().value());
        EXPECT_EQ(stored_money->num, "50000.00");
        EXPECT_EQ(*log->getOldValueStr(), std::string("50000.00 USD"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::MonthlyQuota);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Remove);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, AddTask)
    {
        auto task = std::make_shared<Task>(
            BigUint("90001"),
            "Implement CRM API v2",
            "Develop REST API for new features",
            std::nullopt,
            Task::Status::InProgress,
            Priority::High,
            std::make_shared<Date>(2025, 12, 31),
            std::make_shared<Date>(2025, 11, 1),
            nullptr,
            nullptr,
            changer,
            nullptr,
            std::vector<Note>{},
            std::vector<StringPair>{},
            std::vector<PersonPtr>{}
        );

        ie.addTask(task, changer);

        SCOPED_TRACE("Value check");
        ASSERT_EQ(ie.getTasks().size(), 1);
        EXPECT_EQ(ie.getTasks()[0], task);
        EXPECT_EQ(ie.getTasks()[0]->getTitle(), "Implement CRM API v2");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 57);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Task);
        auto stored_task = std::get<std::shared_ptr<Task>>(log->getNewValue().value());
        EXPECT_EQ(stored_task, task);
        EXPECT_EQ(stored_task->getTitle(), "Implement CRM API v2");
        EXPECT_EQ(*log->getNewValueStr(), std::string("Implement CRM API v2"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::Tasks);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);
        EXPECT_EQ(log->getChanger(), changer);
    }
    TEST(InternalEmployeeTest, AddTask2)
    {
        auto new_task = std::make_shared<Task>(
            BigUint("90002"),
            "Write Unit Tests for ChangeLog",
            "Cover all edge cases",
            std::nullopt,
            Task::Status::Overdue,
            Priority::Critical,
            std::make_shared<Date>(2025, 12, 21),
            std::make_shared<Date>(2025, 10, 5),
            nullptr,
            nullptr,
            changer,
            nullptr,
            std::vector<Note>{},
            std::vector<StringPair>{},
            std::vector<PersonPtr>{}
        );

        ie.addTask(new_task, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getTasks().size(), 2);
        EXPECT_EQ(ie.getTasks()[1]->getTitle(), "Write Unit Tests for ChangeLog");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 58);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Task);
        auto stored_task = std::get<std::shared_ptr<Task>>(log->getNewValue().value());
        EXPECT_EQ(stored_task, new_task);
        EXPECT_EQ(stored_task->getTitle(), "Write Unit Tests for ChangeLog");
        EXPECT_EQ(*log->getNewValueStr(), std::string("Write Unit Tests for ChangeLog"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::Tasks);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, DelTask)
    {
        ie.delTask(0, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getTasks().size(), 1);
        EXPECT_EQ(ie.getTasks()[0]->getTitle(), "Write Unit Tests for ChangeLog");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 59);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Task);
        auto stored_task = std::get<std::shared_ptr<Task>>(log->getOldValue().value());
        EXPECT_EQ(stored_task->getTitle(), "Implement CRM API v2");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Implement CRM API v2"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::Tasks);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Remove);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, AddDocument)
    {
        auto doc = std::make_shared<Document>(BigUint("55"));
        doc->setDocumentTitle("Employment Contract 2025", nullptr);

        ie.addDocument(doc, changer);

        SCOPED_TRACE("Value check");
        ASSERT_EQ(ie.getDocuments().size(), 1);
        EXPECT_EQ(ie.getDocuments()[0], doc);
        EXPECT_EQ(ie.getDocuments()[0]->getTitle(), "Employment Contract 2025");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 60);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Document);
        auto stored_doc = std::get<std::shared_ptr<Document>>(log->getNewValue().value());
        EXPECT_EQ(stored_doc, doc);
        EXPECT_EQ(stored_doc->getTitle(), "Employment Contract 2025");
        EXPECT_EQ(*log->getNewValueStr(), std::string("Employment Contract 2025"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::Documents);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, AddDocument2)
    {
        auto new_doc = std::make_shared<Document>(BigUint("100"));
        new_doc->setDocumentTitle("Performance Review Q4 2025", nullptr);

        ie.addDocument(new_doc, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getDocuments().size(), 2);
        EXPECT_EQ(ie.getDocuments()[1]->getTitle(), "Performance Review Q4 2025");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 61);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::Document);
        auto stored_doc = std::get<std::shared_ptr<Document>>(log->getNewValue().value());
        EXPECT_EQ(stored_doc, new_doc);
        EXPECT_EQ(stored_doc->getTitle(), "Performance Review Q4 2025");
        EXPECT_EQ(*log->getNewValueStr(), std::string("Performance Review Q4 2025"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::Documents);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, DelDocument)
    {
        ie.delDocument(0, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getDocuments().size(), 1);
        EXPECT_EQ(ie.getDocuments()[0]->getTitle(), "Performance Review Q4 2025");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 62);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::Document);
        auto stored_doc = std::get<std::shared_ptr<Document>>(log->getOldValue().value());
        EXPECT_EQ(stored_doc->getTitle(), "Employment Contract 2025");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Employment Contract 2025"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::Documents);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Remove);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, AddSkill)
    {
        ie.addSkill("C++17/20", changer);

        SCOPED_TRACE("Value check");
        ASSERT_EQ(ie.getSkills().size(), 1);
        EXPECT_EQ(ie.getSkills()[0], "C++17/20");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 63);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto stored_skill = std::get<StringPtr>(log->getNewValue().value());
        EXPECT_EQ(*stored_skill, "C++17/20");
        EXPECT_EQ(*log->getNewValueStr(), std::string("C++17/20"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::Skills);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);
        EXPECT_EQ(log->getChanger(), changer);
    }
    TEST(InternalEmployeeTest, AddSkill2)
    {
        ie.addSkill("Unit Testing with GoogleTest", changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getSkills().size(), 2);
        EXPECT_EQ(ie.getSkills()[1], "Unit Testing with GoogleTest");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 64);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::String);
        auto stored_skill = std::get<StringPtr>(log->getNewValue().value());
        EXPECT_EQ(*stored_skill, "Unit Testing with GoogleTest");
        EXPECT_EQ(*log->getNewValueStr(), std::string("Unit Testing with GoogleTest"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::Skills);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);
        EXPECT_EQ(log->getChanger(), changer);
    }
    TEST(InternalEmployeeTest, DelSkill)
    {
        ie.delSkill(0, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getSkills().size(), 1);
        EXPECT_EQ(ie.getSkills()[0], "Unit Testing with GoogleTest");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 65);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::String);
        auto stored_skill = std::get<StringPtr>(log->getOldValue().value());
        EXPECT_EQ(*stored_skill, "C++17/20");
        EXPECT_EQ(*log->getOldValueStr(), std::string("C++17/20"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::Skills);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Remove);
        EXPECT_EQ(log->getChanger(), changer);
    }
    TEST(InternalEmployeeTest, AddDirectReport)
    {
        auto report =
            std::make_shared<InternalEmployee>(BigUint("501"), "Alexey", "Ivanov", std::nullopt);

        ie.addDirectReport(report, changer);

        SCOPED_TRACE("Value check");
        ASSERT_EQ(ie.getDirectReports().size(), 1);
        EXPECT_EQ(ie.getDirectReports()[0], report);
        EXPECT_EQ(ie.getDirectReports()[0]->getName(), "Alexey");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 66);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::InternalEmployee);
        auto stored_report = std::get<InternalEmployeePtr>(log->getNewValue().value());
        EXPECT_EQ(stored_report, report);
        EXPECT_EQ(stored_report->getName(), "Alexey");
        EXPECT_EQ(stored_report->getSurname(), "Ivanov");
        EXPECT_EQ(*log->getNewValueStr(), std::string("Alexey Ivanov"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::DirectReports);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);
        EXPECT_EQ(log->getChanger(), changer);
    }

    TEST(InternalEmployeeTest, AddDirectReport2)
    {
        auto new_report =
            std::make_shared<InternalEmployee>(BigUint("502"), "Daria", "Petrova", std::nullopt);

        ie.addDirectReport(new_report, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getDirectReports().size(), 2);
        EXPECT_EQ(ie.getDirectReports()[1]->getName(), "Daria");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 67);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_FALSE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("New value");
        EXPECT_TRUE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::InternalEmployee);
        auto stored_report = std::get<InternalEmployeePtr>(log->getNewValue().value());
        EXPECT_EQ(stored_report, new_report);
        EXPECT_EQ(stored_report->getName(), "Daria");
        EXPECT_EQ(stored_report->getSurname(), "Petrova");
        EXPECT_EQ(*log->getNewValueStr(), std::string("Daria Petrova"));

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::DirectReports);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Add);
        EXPECT_EQ(log->getChanger(), changer);
    }
    TEST(InternalEmployeeTest, DelDirectReport)
    {
        ie.delDirectReport(0, changer);

        SCOPED_TRACE("Value check");
        EXPECT_EQ(ie.getDirectReports().size(), 1);
        EXPECT_EQ(ie.getDirectReports()[0]->getName(), "Daria");

        SCOPED_TRACE("Change logs size");
        EXPECT_EQ(ie.getChangeLogs().size(), 68);

        auto log = ie.getChangeLogs().back();

        SCOPED_TRACE("Old value");
        EXPECT_TRUE(log->getOldValue().has_value());
        EXPECT_EQ(log->getOldValueFieldType(), ChangeLog::FieldType::InternalEmployee);
        auto stored_report = std::get<InternalEmployeePtr>(log->getOldValue().value());
        EXPECT_EQ(stored_report->getName(), "Alexey");
        EXPECT_EQ(stored_report->getSurname(), "Ivanov");
        EXPECT_EQ(*log->getOldValueStr(), std::string("Alexey Ivanov"));

        SCOPED_TRACE("New value");
        EXPECT_FALSE(log->getNewValue().has_value());
        EXPECT_EQ(log->getNewValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("Field");
        auto field = ChangeLog::FieldVariant(InternalEmployeeFields::DirectReports);
        EXPECT_EQ(log->getField(), field);

        SCOPED_TRACE("Action & Changer");
        EXPECT_EQ(log->getAction(), ChangeLog::Action::Remove);
        EXPECT_EQ(log->getChanger(), changer);
    }
}  // namespace unit