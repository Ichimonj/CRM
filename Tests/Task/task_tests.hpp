#include "Task/task.hpp"
#include "gtest/gtest.h"
#include "Person/Client/client.hpp"

namespace unit {
    TEST(TaskTest, ConstructorWithIdOnly)
    {
        Task task(BigUint("1"));

        SCOPED_TRACE("Constructor with only ID");

        EXPECT_EQ(task.getId().num, "1");

        EXPECT_TRUE(task.getTitle().empty());
        EXPECT_FALSE(task.getDescription().has_value());
        EXPECT_FALSE(task.getSubject().has_value());

        EXPECT_EQ(task.getStatus(), Task::Status::NotStarted);
        EXPECT_EQ(task.getPriority(), Priority::Medium);

        const Date& created = task.getCreatedDate();
        EXPECT_GT(created.getYear(), 2000);

        EXPECT_FALSE(task.getDeadline() ? true : false);
        EXPECT_FALSE(task.getStartDate() ? true : false);

        EXPECT_FALSE(task.getETC() ? true : false);
        EXPECT_FALSE(task.getATS() ? true : false);

        EXPECT_FALSE(task.getCreatedBy() ? true : false);
        EXPECT_FALSE(task.getManager() ? true : false);

        EXPECT_TRUE(task.getFiles().empty());
        EXPECT_TRUE(task.getTasks().empty());
        EXPECT_TRUE(task.getNotes().empty());
        EXPECT_TRUE(task.getMoreData().empty());
        EXPECT_TRUE(task.getTeem().empty());
        EXPECT_TRUE(task.getChangeLogs().empty());
    }

    /*
    StringPtr getOldValueStr();
    StringPtr getNewValueStr();

    auto getChanger() const -> const std::shared_ptr<InternalEmployee>;
    auto getChangeDate() const -> const Date&;
    auto getOldValue() const -> const std::optional<ValueVariant>&;
    auto getNewValue() const -> const std::optional<ValueVariant>&;
    auto getField() const -> const FieldVariant;
    auto getOldValueFieldType() const -> FieldType;
    auto getNewValueFieldType() const -> FieldType;
    auto getAction() const -> Action;
    */
    Task task(BigUint("1"));
    TEST(TaskTest, setTitle)
    {
        EXPECT_TRUE(task.setTitle("Title", changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getTitle(), "Title");
        EXPECT_EQ(task.getChangeLogs().size(), 1);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_TRUE(change->getOldValue().has_value());
        auto old_title = std::get<StringPtr>(change->getOldValue().value());
        EXPECT_EQ(*old_title, "");
        EXPECT_EQ(*change->getOldValueStr(), "");
        EXPECT_TRUE(change->getNewValue().has_value());
        auto new_title = std::get<StringPtr>(change->getNewValue().value());
        EXPECT_EQ(*new_title, "Title");
        EXPECT_EQ(*change->getNewValueStr(), "Title");

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::Title);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::String);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::String);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Change);
        EXPECT_FALSE(task.setTitle("Title", changer));
    }

    TEST(TaskTest, setDescription)
    {
        EXPECT_TRUE(task.setDescription("Description", changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getDescription(), "Description");
        EXPECT_EQ(task.getChangeLogs().size(), 2);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_FALSE(change->getOldValue().has_value());
        EXPECT_EQ(change->getOldValueStr(), nullptr);
        EXPECT_TRUE(change->getNewValue().has_value());
        auto new_desc = std::get<StringPtr>(change->getNewValue().value());
        EXPECT_EQ(*new_desc, "Description");
        EXPECT_EQ(*change->getNewValueStr(), "Description");

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::Description);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::String);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Change);
        EXPECT_FALSE(task.setDescription("Description", changer));
    }

    TEST(TaskTest, clearDescription)
    {
        EXPECT_TRUE(task.setDescription(std::nullopt, changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getDescription(), std::nullopt);
        EXPECT_EQ(task.getChangeLogs().size(), 3);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_TRUE(change->getOldValue().has_value());
        auto old_desc = std::get<StringPtr>(change->getOldValue().value());
        EXPECT_EQ(*old_desc, "Description");
        EXPECT_EQ(*change->getOldValueStr(), "Description");
        EXPECT_FALSE(change->getNewValue().has_value());
        EXPECT_EQ(change->getNewValueStr(), nullptr);

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::Description);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::String);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Change);
        EXPECT_FALSE(task.setDescription(std::nullopt, changer));
    }

    TEST(TaskTest, setSubject)
    {
        EXPECT_TRUE(task.setSubject("Subject", changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getSubject(), "Subject");
        EXPECT_EQ(task.getChangeLogs().size(), 4);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_FALSE(change->getOldValue().has_value());
        EXPECT_EQ(change->getOldValueStr(), nullptr);
        EXPECT_TRUE(change->getNewValue().has_value());
        auto new_subject = std::get<StringPtr>(change->getNewValue().value());
        EXPECT_EQ(*new_subject, "Subject");
        EXPECT_EQ(*change->getNewValueStr(), "Subject");

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::Subject);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::String);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Change);
        EXPECT_FALSE(task.setSubject("Subject", changer));
    }

    TEST(TaskTest, clearSubject)
    {
        EXPECT_TRUE(task.setSubject(std::nullopt, changer));
        SCOPED_TRACE("Check value");

        EXPECT_EQ(task.getSubject(), std::nullopt);
        EXPECT_EQ(task.getChangeLogs().size(), 5);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_TRUE(change->getOldValue().has_value());
        auto old_subject = std::get<StringPtr>(change->getOldValue().value());
        EXPECT_EQ(*old_subject, "Subject");
        EXPECT_EQ(*change->getOldValueStr(), "Subject");
        EXPECT_FALSE(change->getNewValue().has_value());
        EXPECT_EQ(change->getNewValueStr(), nullptr);

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::Subject);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::String);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Change);
        EXPECT_FALSE(task.setSubject(std::nullopt, changer));
    }

    TEST(TaskTest, setStatus)
    {
        EXPECT_TRUE(task.setStatus(Task::Status::InProgress, changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getStatus(), Task::Status::InProgress);
        EXPECT_EQ(task.getChangeLogs().size(), 6);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_TRUE(change->getOldValue().has_value());
        auto old_status = std::get<Task::Status>(change->getOldValue().value());
        EXPECT_EQ(old_status, Task::Status::NotStarted);
        EXPECT_EQ(*change->getOldValueStr(), "Not started");
        EXPECT_TRUE(change->getNewValue().has_value());
        auto new_status = std::get<Task::Status>(change->getNewValue().value());
        EXPECT_EQ(new_status, Task::Status::InProgress);
        EXPECT_EQ(*change->getNewValueStr(), "In progress");

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::Status);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::TaskStatus);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::TaskStatus);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Change);
        EXPECT_FALSE(task.setStatus(Task::Status::InProgress, changer));
    }

    TEST(TaskTest, setPriority)
    {
        EXPECT_TRUE(task.setPriority(Priority::High, changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getPriority(), Priority::High);
        EXPECT_EQ(task.getChangeLogs().size(), 7);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_TRUE(change->getOldValue().has_value());
        auto old_priority = std::get<Priority>(change->getOldValue().value());
        EXPECT_EQ(old_priority, Priority::Medium);
        EXPECT_EQ(*change->getOldValueStr(), "Medium");
        EXPECT_TRUE(change->getNewValue().has_value());
        auto new_priority = std::get<Priority>(change->getNewValue().value());
        EXPECT_EQ(new_priority, Priority::High);
        EXPECT_EQ(*change->getNewValueStr(), "High");

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::Priority);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::Priority);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::Priority);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Change);
        EXPECT_FALSE(task.setPriority(Priority::High, changer));
    }

    TEST(TaskTest, setDeadline)
    {
        auto date_ptr = std::make_shared<Date>(2030, 11, 11);
        EXPECT_TRUE(task.setDeadline(date_ptr, changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getDeadline(), date_ptr);
        EXPECT_EQ(task.getChangeLogs().size(), 8);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_FALSE(change->getOldValue().has_value());
        EXPECT_EQ(change->getOldValueStr(), nullptr);
        EXPECT_TRUE(change->getNewValue().has_value());
        auto new_date = std::get<DatePtr>(change->getNewValue().value());
        EXPECT_EQ(*new_date, *date_ptr);
        EXPECT_EQ(*change->getNewValueStr(), "11 Nov 2030 0:00");

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::Deadline);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::Date);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Change);
        EXPECT_FALSE(task.setDeadline(date_ptr, changer));
    }

    TEST(TaskTest, changeDeadline)
    {
        auto old_date_ptr = std::make_shared<Date>(2030, 11, 11);

        auto new_date_ptr = std::make_shared<Date>(2032, 5, 15);
        EXPECT_TRUE(task.setDeadline(new_date_ptr, changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getDeadline(), new_date_ptr);
        EXPECT_EQ(task.getChangeLogs().size(), 9);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_TRUE(change->getOldValue().has_value());
        auto old_date = std::get<DatePtr>(change->getOldValue().value());
        EXPECT_EQ(*old_date, *old_date_ptr);
        EXPECT_EQ(*change->getOldValueStr(), "11 Nov 2030 0:00");
        EXPECT_TRUE(change->getNewValue().has_value());
        auto new_date = std::get<DatePtr>(change->getNewValue().value());
        EXPECT_EQ(*new_date, *new_date_ptr);
        EXPECT_EQ(*change->getNewValueStr(), "15 May 2032 0:00");

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::Deadline);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::Date);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::Date);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Change);
        EXPECT_FALSE(task.setDeadline(new_date_ptr, changer));
    }

    TEST(TaskTest, clearDeadline)
    {
        auto date_ptr = std::make_shared<Date>(2032, 5, 15);
        EXPECT_TRUE(task.setDeadline(nullptr, changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getDeadline(), nullptr);
        EXPECT_EQ(task.getChangeLogs().size(), 10);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_TRUE(change->getOldValue().has_value());
        auto old_date = std::get<DatePtr>(change->getOldValue().value());
        EXPECT_EQ(*old_date, *date_ptr);
        EXPECT_EQ(*change->getOldValueStr(), "15 May 2032 0:00");
        EXPECT_FALSE(change->getNewValue().has_value());
        EXPECT_EQ(change->getNewValueStr(), nullptr);

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::Deadline);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::Date);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Change);
        EXPECT_FALSE(task.setDeadline(nullptr, changer));
    }
    TEST(TaskTest, setStartDate)
    {
        auto date_ptr = std::make_shared<Date>(2020, 11, 11);
        EXPECT_TRUE(task.setStartDate(date_ptr, changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getStartDate(), date_ptr);
        EXPECT_EQ(task.getChangeLogs().size(), 11);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_FALSE(change->getOldValue().has_value());
        EXPECT_EQ(change->getOldValueStr(), nullptr);
        EXPECT_TRUE(change->getNewValue().has_value());
        auto new_date = std::get<DatePtr>(change->getNewValue().value());
        EXPECT_EQ(*new_date, *date_ptr);
        EXPECT_EQ(*change->getNewValueStr(), "11 Nov 2020 0:00");

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::StartDate);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::Date);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Change);
        EXPECT_FALSE(task.setStartDate(date_ptr, changer));
    }
    TEST(TaskTest, changeStartDate)
    {
        auto old_date_ptr = std::make_shared<Date>(2020, 11, 11);

        auto new_date_ptr = std::make_shared<Date>(2021, 12, 25);
        EXPECT_TRUE(task.setStartDate(new_date_ptr, changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getStartDate(), new_date_ptr);
        EXPECT_EQ(task.getChangeLogs().size(), 12);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_TRUE(change->getOldValue().has_value());
        auto old_date = std::get<DatePtr>(change->getOldValue().value());
        EXPECT_EQ(*old_date, *old_date_ptr);
        EXPECT_EQ(*change->getOldValueStr(), "11 Nov 2020 0:00");
        EXPECT_TRUE(change->getNewValue().has_value());
        auto new_date = std::get<DatePtr>(change->getNewValue().value());
        EXPECT_EQ(*new_date, *new_date_ptr);
        EXPECT_EQ(*change->getNewValueStr(), "25 Dec 2021 0:00");

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::StartDate);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::Date);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::Date);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Change);
        EXPECT_FALSE(task.setStartDate(new_date_ptr, changer));
    }

    TEST(TaskTest, clearStartDate)
    {
        auto date_ptr = std::make_shared<Date>(2021, 12, 25);
        EXPECT_TRUE(task.setStartDate(nullptr, changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getStartDate(), nullptr);
        EXPECT_EQ(task.getChangeLogs().size(), 13);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_TRUE(change->getOldValue().has_value());
        auto old_date = std::get<DatePtr>(change->getOldValue().value());
        EXPECT_EQ(*old_date, *date_ptr);
        EXPECT_EQ(*change->getOldValueStr(), "25 Dec 2021 0:00");
        EXPECT_FALSE(change->getNewValue().has_value());
        EXPECT_EQ(change->getNewValueStr(), nullptr);

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::StartDate);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::Date);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Change);
        EXPECT_FALSE(task.setStartDate(nullptr, changer));
    }

    TEST(TaskTest, setETC)
    {
        auto duration_ptr = std::make_shared<TimeDuration>(1, 5, 11, 0, 0);
        EXPECT_TRUE(task.setETC(duration_ptr, changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getETC(), duration_ptr);
        EXPECT_EQ(task.getChangeLogs().size(), 14);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_FALSE(change->getOldValue().has_value());
        EXPECT_EQ(change->getOldValueStr(), nullptr);
        EXPECT_TRUE(change->getNewValue().has_value());
        auto new_duration = std::get<DurationPtr>(change->getNewValue().value());
        EXPECT_EQ(*new_duration, *duration_ptr);
        EXPECT_EQ(*change->getNewValueStr(), "1 wk, 5 d, 11 hr, 0 min, 0 sec");

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::ETC);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::TimeDuration);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Change);
        EXPECT_FALSE(task.setETC(duration_ptr, changer));
    }
    TEST(TaskTest, changeETC)
    {
        auto old_duration_ptr = std::make_shared<TimeDuration>(1, 5, 11, 0, 0);

        auto new_duration_ptr = std::make_shared<TimeDuration>(2, 0, 8, 30, 45);
        EXPECT_TRUE(task.setETC(new_duration_ptr, changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getETC(), new_duration_ptr);
        EXPECT_EQ(task.getChangeLogs().size(), 15);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_TRUE(change->getOldValue().has_value());
        auto old_duration = std::get<DurationPtr>(change->getOldValue().value());
        EXPECT_EQ(*old_duration, *old_duration_ptr);
        EXPECT_EQ(*change->getOldValueStr(), "1 wk, 5 d, 11 hr, 0 min, 0 sec");
        EXPECT_TRUE(change->getNewValue().has_value());
        auto new_duration = std::get<DurationPtr>(change->getNewValue().value());
        EXPECT_EQ(*new_duration, *new_duration_ptr);
        EXPECT_EQ(*change->getNewValueStr(), "2 wks, 0 d, 8 hr, 30 min, 45 sec");

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::ETC);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::TimeDuration);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::TimeDuration);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Change);
        EXPECT_FALSE(task.setETC(new_duration_ptr, changer));
    }

    TEST(TaskTest, clearETC)
    {
        auto last_duration_ptr = std::make_shared<TimeDuration>(2, 0, 8, 30, 45);
        EXPECT_TRUE(task.setETC(nullptr, changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getETC(), nullptr);
        EXPECT_EQ(task.getChangeLogs().size(), 16);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_TRUE(change->getOldValue().has_value());
        auto old_duration = std::get<DurationPtr>(change->getOldValue().value());
        EXPECT_EQ(*old_duration, *last_duration_ptr);
        EXPECT_EQ(*change->getOldValueStr(), "2 wks, 0 d, 8 hr, 30 min, 45 sec");
        EXPECT_FALSE(change->getNewValue().has_value());
        EXPECT_EQ(change->getNewValueStr(), nullptr);

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::ETC);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::TimeDuration);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Change);
        EXPECT_FALSE(task.setETC(nullptr, changer));
    }

    TEST(TaskTest, setATS)
    {
        auto duration_ptr = std::make_shared<TimeDuration>(0, 3, 6, 15, 30);
        EXPECT_TRUE(task.setATS(duration_ptr, changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getATS(), duration_ptr);
        EXPECT_EQ(task.getChangeLogs().size(), 17);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_FALSE(change->getOldValue().has_value());
        EXPECT_EQ(change->getOldValueStr(), nullptr);
        EXPECT_TRUE(change->getNewValue().has_value());
        auto new_duration = std::get<DurationPtr>(change->getNewValue().value());
        EXPECT_EQ(*new_duration, *duration_ptr);
        EXPECT_EQ(*change->getNewValueStr(), "0 wk, 3 d, 6 hr, 15 min, 30 sec");

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::ATS);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::TimeDuration);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Change);
        EXPECT_FALSE(task.setATS(duration_ptr, changer));
    }

    TEST(TaskTest, changeATS)
    {
        auto old_duration_ptr = std::make_shared<TimeDuration>(0, 3, 6, 15, 30);

        auto new_duration_ptr = std::make_shared<TimeDuration>(1, 0, 4, 45, 20);
        EXPECT_TRUE(task.setATS(new_duration_ptr, changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getATS(), new_duration_ptr);
        EXPECT_EQ(task.getChangeLogs().size(), 18);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_TRUE(change->getOldValue().has_value());
        auto old_duration = std::get<DurationPtr>(change->getOldValue().value());
        EXPECT_EQ(*old_duration, *old_duration_ptr);
        EXPECT_EQ(*change->getOldValueStr(), "0 wk, 3 d, 6 hr, 15 min, 30 sec");
        EXPECT_TRUE(change->getNewValue().has_value());
        auto new_duration = std::get<DurationPtr>(change->getNewValue().value());
        EXPECT_EQ(*new_duration, *new_duration_ptr);
        EXPECT_EQ(*change->getNewValueStr(), "1 wk, 0 d, 4 hr, 45 min, 20 sec");

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::ATS);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::TimeDuration);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::TimeDuration);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Change);
        EXPECT_FALSE(task.setATS(new_duration_ptr, changer));
    }

    TEST(TaskTest, clearATS)
    {
        auto last_duration_ptr = std::make_shared<TimeDuration>(1, 0, 4, 45, 20);
        EXPECT_TRUE(task.setATS(nullptr, changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getATS(), nullptr);
        EXPECT_EQ(task.getChangeLogs().size(), 19);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_TRUE(change->getOldValue().has_value());
        auto old_duration = std::get<DurationPtr>(change->getOldValue().value());
        EXPECT_EQ(*old_duration, *last_duration_ptr);
        EXPECT_EQ(*change->getOldValueStr(), "1 wk, 0 d, 4 hr, 45 min, 20 sec");
        EXPECT_FALSE(change->getNewValue().has_value());
        EXPECT_EQ(change->getNewValueStr(), nullptr);

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::ATS);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::TimeDuration);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Change);
        EXPECT_FALSE(task.setATS(nullptr, changer));
    }

    TEST(TaskTest, setManager)
    {
        auto manager =
            std::make_shared<InternalEmployee>(BigUint("1"), "Name", "Surname", std::nullopt);
        EXPECT_TRUE(task.setManager(manager, changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getManager(), manager);
        EXPECT_EQ(task.getChangeLogs().size(), 20);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_FALSE(change->getOldValue().has_value());
        EXPECT_EQ(change->getOldValueStr(), nullptr);
        EXPECT_TRUE(change->getNewValue().has_value());
        auto new_manager = std::get<InternalEmployeePtr>(change->getNewValue().value());
        EXPECT_EQ(new_manager->getId(), manager->getId());
        EXPECT_EQ(*change->getNewValueStr(), "Name Surname");

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::Manager);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::InternalEmployee);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Change);
        EXPECT_FALSE(task.setManager(manager, changer));
    }
    TEST(TaskTest, changeManager)
    {
        auto old_manager =
            std::make_shared<InternalEmployee>(BigUint("1"), "Name", "Surname", std::nullopt);

        auto new_manager =
            std::make_shared<InternalEmployee>(BigUint("2"), "NewName", "NewSurname", "Patronymic");
        EXPECT_TRUE(task.setManager(new_manager, changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getManager(), new_manager);
        EXPECT_EQ(task.getChangeLogs().size(), 21);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_TRUE(change->getOldValue().has_value());
        auto old_manager_val = std::get<InternalEmployeePtr>(change->getOldValue().value());
        EXPECT_EQ(old_manager_val->getId(), old_manager->getId());
        EXPECT_EQ(*change->getOldValueStr(), "Name Surname");
        EXPECT_TRUE(change->getNewValue().has_value());
        auto new_manager_val = std::get<InternalEmployeePtr>(change->getNewValue().value());
        EXPECT_EQ(new_manager_val->getId(), new_manager->getId());
        EXPECT_EQ(*change->getNewValueStr(), "NewName NewSurname");

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::Manager);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::InternalEmployee);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::InternalEmployee);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Change);
        EXPECT_FALSE(task.setManager(new_manager, changer));
    }

    TEST(TaskTest, clearManager)
    {
        auto last_manager =
            std::make_shared<InternalEmployee>(BigUint("2"), "NewName", "NewSurname", "Patronymic");
        EXPECT_TRUE(task.setManager(nullptr, changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getManager(), nullptr);
        EXPECT_EQ(task.getChangeLogs().size(), 22);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_TRUE(change->getOldValue().has_value());
        auto old_manager = std::get<InternalEmployeePtr>(change->getOldValue().value());
        EXPECT_EQ(old_manager->getId(), last_manager->getId());
        EXPECT_EQ(*change->getOldValueStr(), "NewName NewSurname");
        EXPECT_FALSE(change->getNewValue().has_value());
        EXPECT_EQ(change->getNewValueStr(), nullptr);

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::Manager);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::InternalEmployee);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Change);
        EXPECT_FALSE(task.setManager(nullptr, changer));
    }

    TEST(TaskTest, addTask)
    {
        auto task_ptr = std::make_shared<Task>(BigUint("1"));
        task_ptr->setTitle("Title", nullptr);

        EXPECT_TRUE(task.addTask(task_ptr, changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getTasks().back(), task_ptr);
        EXPECT_EQ(task.getChangeLogs().size(), 23);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_FALSE(change->getOldValue().has_value());
        EXPECT_EQ(change->getOldValueStr(), nullptr);
        EXPECT_TRUE(change->getNewValue().has_value());
        auto old_task = std::get<TaskPtr>(change->getNewValue().value());
        EXPECT_EQ(old_task->getId(), task_ptr->getId());
        EXPECT_EQ(*change->getNewValueStr(), "Title");

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::Task);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::Task);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Add);

        EXPECT_FALSE(task.addTask(task_ptr, changer));
    }

    TEST(TaskTest, delTask)
    {
        EXPECT_TRUE(task.delTask(0, changer));

        SCOPED_TRACE("Check value");
        EXPECT_TRUE(task.getTasks().empty());
        EXPECT_EQ(task.getChangeLogs().size(), 24);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_TRUE(change->getOldValue().has_value());
        EXPECT_EQ(*change->getOldValueStr(), "Title");
        auto old_task = std::get<TaskPtr>(change->getOldValue().value());
        EXPECT_EQ(old_task->getId().num, "1");
        EXPECT_FALSE(change->getNewValue().has_value());
        EXPECT_EQ(change->getNewValueStr(), nullptr);

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::Task);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::Task);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Remove);

        EXPECT_FALSE(task.setManager(nullptr, changer));
    }

    TEST(TaskTest, addFile)
    {
        auto file_ptr = std::make_shared<FileMetadata>(BigUint("1"));
        file_ptr->setFileName("Name", nullptr);

        EXPECT_TRUE(task.addFile(file_ptr, changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getFiles().back(), file_ptr);
        EXPECT_EQ(task.getChangeLogs().size(), 25);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_FALSE(change->getOldValue().has_value());
        EXPECT_EQ(change->getOldValueStr(), nullptr);
        EXPECT_TRUE(change->getNewValue().has_value());
        auto old_file = std::get<FilePtr>(change->getNewValue().value());
        EXPECT_EQ(old_file->getId(), file_ptr->getId());
        EXPECT_EQ(*change->getNewValueStr(), "Name");

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::File);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::FileMetadata);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Add);

        EXPECT_FALSE(task.addFile(file_ptr, changer));
    }

    TEST(TaskTest, delFile)
    {
        EXPECT_TRUE(task.delFile(0, changer));

        SCOPED_TRACE("Check value");
        EXPECT_TRUE(task.getTasks().empty());
        EXPECT_EQ(task.getChangeLogs().size(), 26);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_TRUE(change->getOldValue().has_value());
        EXPECT_EQ(*change->getOldValueStr(), "Name");
        auto old_task = std::get<FilePtr>(change->getOldValue().value());
        EXPECT_EQ(old_task->getId().num, "1");
        EXPECT_FALSE(change->getNewValue().has_value());
        EXPECT_EQ(change->getNewValueStr(), nullptr);

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::File);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::FileMetadata);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Remove);

        EXPECT_FALSE(task.delFile(0, changer));
    }

    TEST(TaskTest, addNote)
    {
        EXPECT_TRUE(task.addNote("Note", changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getNotes().back(), "Note");
        EXPECT_EQ(task.getChangeLogs().size(), 27);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_FALSE(change->getOldValue().has_value());
        EXPECT_EQ(change->getOldValueStr(), nullptr);
        EXPECT_TRUE(change->getNewValue().has_value());
        auto old_note = std::get<StringPtr>(change->getNewValue().value());
        EXPECT_EQ(*old_note, "Note");
        EXPECT_EQ(*change->getNewValueStr(), "Note");

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::Notes);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::String);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Add);

        EXPECT_FALSE(task.addNote("Note", changer));
    }

    TEST(TaskTest, delNote)
    {
        EXPECT_TRUE(task.delNote(0, changer));

        SCOPED_TRACE("Check value");
        EXPECT_TRUE(task.getTasks().empty());
        EXPECT_EQ(task.getChangeLogs().size(), 28);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_TRUE(change->getOldValue().has_value());
        EXPECT_EQ(*change->getOldValueStr(), "Note");
        auto old_note = std::get<StringPtr>(change->getOldValue().value());
        EXPECT_EQ(*old_note, "Note");
        EXPECT_FALSE(change->getNewValue().has_value());
        EXPECT_EQ(change->getNewValueStr(), nullptr);

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::Notes);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::String);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Remove);

        EXPECT_FALSE(task.delNote(0, changer));
    }

    TEST(TaskTest, addMoreData)
    {
        EXPECT_TRUE(task.addMoreData("Title", "Data", changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getMoreData().back().first, "Title");
        EXPECT_EQ(task.getMoreData().back().second, "Data");
        EXPECT_EQ(task.getChangeLogs().size(), 29);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_FALSE(change->getOldValue().has_value());
        EXPECT_EQ(change->getOldValueStr(), nullptr);
        EXPECT_TRUE(change->getNewValue().has_value());
        auto old_more_data =
            std::get<std::shared_ptr<std::pair<const std::string, const std::string>>>(
                change->getNewValue().value()
            );
        EXPECT_EQ(old_more_data->first, "Title");
        EXPECT_EQ(old_more_data->second, "Data");
        EXPECT_EQ(*change->getNewValueStr(), "Title Data");

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::MoreData);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::StringPair);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Add);

        EXPECT_FALSE(task.addMoreData("Title", "Data", changer));
    }

    TEST(TaskTest, delMoreData)
    {
        EXPECT_TRUE(task.delMoreData(0, changer));

        SCOPED_TRACE("Check value");
        EXPECT_TRUE(task.getTasks().empty());
        EXPECT_EQ(task.getChangeLogs().size(), 30);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_TRUE(change->getOldValue().has_value());
        EXPECT_EQ(*change->getOldValueStr(), "Title Data");
        auto old_more_data =
            std::get<std::shared_ptr<std::pair<const std::string, const std::string>>>(
                change->getOldValue().value()
            );
        EXPECT_EQ(old_more_data->first, "Title");
        EXPECT_EQ(old_more_data->second, "Data");
        EXPECT_FALSE(change->getNewValue().has_value());
        EXPECT_EQ(change->getNewValueStr(), nullptr);

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::MoreData);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::StringPair);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Remove);

        EXPECT_FALSE(task.delMoreData(0, changer));
    }

    TEST(TaskTest, addTeemMember)
    {
        auto person = std::make_shared<Client>(BigUint("1"), "Name", "Surname", std::nullopt);
        EXPECT_TRUE(task.addTeemMember(person, changer));

        SCOPED_TRACE("Check value");
        EXPECT_EQ(task.getTeem().back(), person);
        EXPECT_EQ(task.getChangeLogs().size(), 31);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_FALSE(change->getOldValue().has_value());
        EXPECT_EQ(change->getOldValueStr(), nullptr);
        EXPECT_TRUE(change->getNewValue().has_value());
        auto old_person = std::get<PersonPtr>(change->getNewValue().value());
        EXPECT_EQ(old_person->getId().num, "1");
        EXPECT_EQ(*change->getNewValueStr(), "Name Surname");

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::Teem);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::null);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::Person);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Add);

        EXPECT_FALSE(task.addTeemMember(person, changer));
    }

    TEST(TaskTest, delTeemMember)
    {
        EXPECT_TRUE(task.delTeemMember(0, changer));

        SCOPED_TRACE("Check value");
        EXPECT_TRUE(task.getTasks().empty());
        EXPECT_EQ(task.getChangeLogs().size(), 32);
        auto change = task.getChangeLogs().back();

        SCOPED_TRACE("Check change log value");
        EXPECT_EQ(change->getChanger(), changer);
        EXPECT_TRUE(change->getOldValue().has_value());
        EXPECT_EQ(*change->getOldValueStr(), "Name Surname");
        auto old_teem = std::get<PersonPtr>(change->getOldValue().value());
        EXPECT_EQ(old_teem->getId().num, "1");
        EXPECT_FALSE(change->getNewValue().has_value());
        EXPECT_EQ(change->getNewValueStr(), nullptr);

        SCOPED_TRACE("Check field");
        auto field = ChangeLog::FieldVariant(TaskFields::Teem);
        EXPECT_EQ(change->getField(), field);
        EXPECT_EQ(change->getOldValueFieldType(), ChangeLog::FieldType::Person);
        EXPECT_EQ(change->getNewValueFieldType(), ChangeLog::FieldType::null);

        SCOPED_TRACE("Check action");
        EXPECT_EQ(change->getAction(), ChangeLog::Action::Remove);

        EXPECT_FALSE(task.delTeemMember(0, changer));
    }
   

}  // namespace unit