
#include "Tests/BigNum/big_uint_tests.hpp"
#include "Tests/BigNum/money_tests.hpp"
#include "Tests/ChangeLog/chagne_log_tests.hpp"
#include "Tests/ChangeLog/enums_to_str_tests.hpp"
#include "Tests/DateTime/date_tests.hpp"
#include "Tests/DateTime/time_duration_tests.hpp"
#include "Tests/PhoneNumber/phone_number_tests.hpp"
#include "Tests/Person/person_tests.hpp"
#include "Tests/Person/client_tests.hpp"
#include "Tests/Person/internal_employee_tests.hpp"
#include "Tests/Person/external_employee_tests.hpp"
int main(int argc, char**argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
