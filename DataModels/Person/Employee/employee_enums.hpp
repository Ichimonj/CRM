#pragma once
enum class AccessRole {
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
    other,
    COUNT
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
    other,
    COUNT
};