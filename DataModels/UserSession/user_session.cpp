#include "user_session.hpp"

UserSession::UserSession(
    const std::string& token, const OptionalStr& ip_address, const OptionalStr& device_info
)
    : token(token), ip_address(ip_address), device_info(device_info)
{
}

auto UserSession::getToken() const -> const std::string& { return this->token; }
auto UserSession::getLoginTime() const -> const Date& { return this->login_time; }
auto UserSession::getLogoutTime() const -> const DatePtr& { return this->logout_time; }
auto UserSession::getSessionDuration() const -> const TimeDuration&
{
    return this->session_duration;
}
auto UserSession::getIsActive() const -> bool { return this->is_active; }
auto UserSession::getIpAddress() const -> const OptionalStr& { return this->ip_address; }
auto UserSession::getDeviceInfo() const -> const OptionalStr& { return this->device_info; }
auto UserSession::getSessionChanges() const -> const std::vector<ChangeLog*>&
{
    return this->session_changes;
}

void UserSession::addChangeLog(ChangeLog* change_log)
{
    this->session_changes.push_back(change_log);
}

void UserSession::logout()
{
    this->logout_time      = std::make_shared<Date>();
    this->session_duration = *this->logout_time - this->login_time;
    this->is_active        = false;
}