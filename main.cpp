#include "Tests/big_uint_tests.hpp"
#include "Tests/money_tests.hpp"
#include "Tests/date_tests.hpp"
#include "Tests/phone_number_tests.hpp"
#include "Tests/time_duration_tests.hpp"
#include "Tests/chagne_log_tests.hpp"
#include "Tests/person_tests.hpp"
#include "Tests/client_tests.hpp"
#include "Tests/external_employee_tests.hpp"
#include "Tests/enums_to_str_tests.hpp"
using namespace std;

int main(int argc, char** argv)
{   
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
