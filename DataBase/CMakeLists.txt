project(DataBase
    VERSION 0.6.0
    DESCRIPTION "Data base library for CRM"
    LANGUAGES CXX
)

file(GLOB DATABASE_SOURCES CONFIGURE_DEPENDS
    "PersonDataBase/*.cpp"
)
add_library(DataBase STATIC
    ../Logger/events_log.cpp
    InteractionDataBase/interaction_data_base.cpp
    TaskDataBase/task_db.cpp
    DealDataBase/deal_db.cpp
    ${DATABASE_SOURCES}
)

target_include_directories(DataBase
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../DataModels
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
