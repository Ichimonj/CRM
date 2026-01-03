project(DataBase
    VERSION 0.0.4
    DESCRIPTION "Data base library for CRM"
    LANGUAGES CXX
)

file(GLOB DATABASE_SOURCES CONFIGURE_DEPENDS
    "PersonDataBase/*.cpp"
)
add_library(DataBase STATIC
    DealDataBase/deal_db.cpp
    ${DATABASE_SOURCES}
)

target_include_directories(DataBase
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../DataModels
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
