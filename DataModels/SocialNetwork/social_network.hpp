#pragma once
#include <string>
struct SocialNetwork {
    SocialNetwork(
        const std::string& name,
        const std::string& username,
        const std::string& full_url,
        bool               is_verified
    );
    bool operator==(const SocialNetwork& other) const;

    //
    std::string name;
    std::string username;
    std::string full_url;
    bool        is_verified;
};