#pragma once
#include "user_session.hpp"
#include "Usings/type_usings.hpp"

class SessionManager {
public:
    static SessionManager& getInstance();
    void setCurrentSession(const UserSessionPtr& session);
    UserSessionPtr getCurrentSession() const;
    void addChangeToSession(ChangeLog* log);

private:
    SessionManager() : current_session(nullptr) {}  // Explicit init to nullptr
    UserSessionPtr current_session;
};