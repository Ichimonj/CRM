#pragma once
#include <vector>

#include "DateTime/date.hpp"
#include "DateTime/time_duration.hpp"
#include "Usings/type_usings.hpp"

class UserSession {
public:
    UserSession(
        const std::string& token,
        const OptionalStr& ip_address,
        const OptionalStr& device_info
    );

    /// @name Getters
    /// @{
    auto getToken() const -> const std::string&;
    auto getLoginTime() const -> const Date&;
    auto getLogoutTime() const -> const DatePtr&;
    auto getSessionDuration() const -> const TimeDuration&;
    auto getIsActive() const -> bool;
    auto getIpAddress() const -> const OptionalStr&;
    auto getDeviceInfo() const -> const OptionalStr&;
    auto getSessionChanges() const -> const std::vector<ChangeLog*>&;
    /// @}
    void addChangeLog(ChangeLog* change_log);
    void logout();
    
private:
    std::string  token;

    Date         login_time = Date();
    DatePtr      logout_time;
    TimeDuration session_duration;

    bool         is_active = true;

    OptionalStr  ip_address;
    OptionalStr  device_info;

    //
    std::vector<ChangeLog*> session_changes;
};