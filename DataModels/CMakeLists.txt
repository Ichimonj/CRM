cmake_minimum_required(VERSION 3.10)
project(DataModels)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(
    DataModels
    STATIC
    Address/address.cpp
    Address/address.hpp
    DateTime/date.cpp
    DateTime/date.hpp
    DateTime/time_duration.hpp
    DateTime/time_duration.hpp
    Deal/deal.cpp
    Deal/deal.hpp
    Document/document.cpp
    Document/document.hpp
    Interaction/interaction.cpp
    Interaction/interaction.hpp
    Offering/offering.cpp
    Offering/offering.hpp
    Person/person.cpp
    Person/person.hpp
    Person/Client/client.cpp
    Person/Client/client.hpp
    PhoneNumber/phone_number.cpp
    PhoneNumber/phone_number.hpp
    BigUint/big_uint.cpp
    BigUint/big_uint.hpp
)
target_include_directories(
    DataModels
    PUBLIC
    ${CMAKE_SOURCE_DIR}/DataModels/Address
    ${CMAKE_SOURCE_DIR}/DataModels/DateTime
    ${CMAKE_SOURCE_DIR}/DataModels/Deal
    ${CMAKE_SOURCE_DIR}/DataModels/Document
    ${CMAKE_SOURCE_DIR}/DataModels/Interaction
    ${CMAKE_SOURCE_DIR}/DataModels/Offering
    ${CMAKE_SOURCE_DIR}/DataModels/Person
    ${CMAKE_SOURCE_DIR}/DataModels/Person/Client
    ${CMAKE_SOURCE_DIR}/DataModels/PhoneNumber
    ${CMAKE_SOURCE_DIR}/DataModels/BigUint
    ${CMAKE_SOURCE_DIR}
)
