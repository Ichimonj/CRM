cmake_minimum_required(VERSION 3.20)

project(Crm LANGUAGES CXX VERSION 0.0.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TESTING "Build the testing tree" OFF)

add_subdirectory(DataModels)
add_subdirectory(DataBase)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE DataModels)

if(BUILD_TESTING)
    add_subdirectory(external/gtest EXCLUDE_FROM_ALL)
    enable_testing()

    add_executable(Tests Tests/tests_main.cpp)

    target_link_libraries(Tests PRIVATE DataModels gtest gtest_main)
    target_compile_definitions(Tests PRIVATE _TESTING)

    add_custom_command(TARGET Tests POST_BUILD
        COMMAND $<TARGET_FILE:Tests> --gtest_color=yes
        COMMENT "=== Running tests automatically ==="
        VERBATIM
        USES_TERMINAL
    )

    add_test(NAME unit_tests COMMAND Tests)
endif()