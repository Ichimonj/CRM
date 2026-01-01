#include "change_log.hpp"
#include "gtest/gtest.h"

namespace unit {
    TEST(ChagneLogConstructorTest, Constructor)
    {
        auto changer =
            std::make_shared<InternalEmployee>(BigUint("1"), "Name", "Surname", std::nullopt);
        auto old_value = std::make_optional<ChangeLog::ValueVariant>(1);
        auto new_value = std::make_optional<ChangeLog::ValueVariant>(1.11);
        auto field = ChangeLog::FieldVariant(BaseInteractionFields::Id);
        Date      change_date;

        ChangeLog change(
            changer,
            old_value,
            new_value,
            field,
            ChangeLog::FieldType::Int,
            ChangeLog::FieldType::Double,
            ChangeLog::Action::Change,
            change_date
        );

        EXPECT_EQ(change.getChanger(), changer);
        EXPECT_EQ(change.getOldValue(), old_value);
        EXPECT_EQ(change.getNewValue(), new_value);
        EXPECT_EQ(change.getField(), field);
        EXPECT_EQ(change.getOldValueFieldType(), ChangeLog::FieldType::Int);
        EXPECT_EQ(change.getNewValueFieldType(), ChangeLog::FieldType::Double);
        EXPECT_EQ(change.getAction(), ChangeLog::Action::Change);
        EXPECT_EQ(change.getChangeDate(), change_date);
    }
}  // namespace unit