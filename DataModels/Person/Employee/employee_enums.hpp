#pragma once
enum class AccessLevel {
    Admin,
    SalesRep,
    Executive,
    Manager,
    MarketingUser,
    ReadOnly,
    SalesManager,
    ServiceManager,
    Support,
    DecisionMaker,
    Influencer,
    User,
    Gatekeeper,
    other
};
enum class EmployeeStatus {
    active,
    vacation,
    fired,
    education,
    internship,
    probation,
    suspended,
    sick_leave,
    retired,
    other
};