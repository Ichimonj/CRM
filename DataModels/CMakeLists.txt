project(DataModels
    VERSION 0.1.2
    DESCRIPTION "Data models library for CRM"
    LANGUAGES CXX
)

file(GLOB INTERACTION_SOURCES CONFIGURE_DEPENDS
    "Interaction/*.cpp"
)
add_library(DataModels STATIC
    Address/address.cpp
    BigNum/big_uint.cpp
    BigNum/money.cpp
    Campaign/campaign.cpp
    Campaign/campaign_lead.cpp
    Case/case.cpp
    ChangeLog/change_log.cpp
    Company/company.cpp
    Company/ExternalCompany/external_company.cpp
    DateTime/date.cpp
    DateTime/time_duration.cpp
    Deal/deal.cpp
    Document/document.cpp
    FileMetadata/file_metadata.cpp
    Note/note.cpp
    Offering/offer_deal.cpp
    Offering/offering.cpp
    Payment/payment.cpp
    Person/person.cpp
    Person/Client/client.cpp
    Person/Employee/internal_employee.cpp
    Person/Employee/external_employee.cpp
    PhoneNumber/phone_number.cpp
    Report/report.cpp
    SocialNetwork/social_network.cpp
    Task/task.cpp
    UserSession/user_session.cpp
    UserSession/session_manager.cpp
    ${INTERACTION_SOURCES}
)

target_include_directories(DataModels
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
