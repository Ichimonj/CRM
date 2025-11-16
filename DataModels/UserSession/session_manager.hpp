#pragma once
#include <memory>
#include "user_session.hpp"

using UserSessionPtr = std::shared_ptr<UserSession>;
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