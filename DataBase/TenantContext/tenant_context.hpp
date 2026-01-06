#include "DataBase/PersonDataBase/client_db.hpp"
#include "DataBase/PersonDataBase/external_employee_db.hpp"
#include "DataBase/PersonDataBase/internal_employee_db.hpp"

struct TenantContext {
    ClientDataBase&           client_data_base;
    ExternalEmployeeDataBase& external_employee_data_base;
    InternalEmployeeDataBase& internal_employee_data_base;
};