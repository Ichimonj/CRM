#include "session_manager.hpp"

SessionManager& SessionManager::getInstance() {
    static SessionManager instance;
    return instance;
}

void SessionManager::setCurrentSession(const UserSessionPtr& session) {
    this->current_session = session;
}

UserSessionPtr SessionManager::getCurrentSession() const {
    return this->current_session;
}

void SessionManager::addChangeToSession(ChangeLog* log) {
    auto session = getCurrentSession();
    if (session) {  
        session->addChangeLog(log);  
    }
 
}