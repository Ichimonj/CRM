#include "social_network.hpp"

SocialNetwork::SocialNetwork(
    const std::string& name,
    const std::string& username,
    const std::string& full_url,
    bool               is_verified
)
    : name(name), username(username), full_url(full_url), is_verified(is_verified)
{
}

bool SocialNetwork::operator==(const SocialNetwork& other) const
{
    if (this->name != other.name) return false;
    if (this->username != other.username) return false;
    if (this->full_url != other.full_url) return false;
    if (this->is_verified != other.is_verified) return false;
    return true;
}
