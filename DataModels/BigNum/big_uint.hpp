#pragma once
#include <string>

struct BigUint {
    BigUint() = default;
    BigUint(const std::string& num);
    BigUint(const BigUint& other);
    BigUint&    operator=(const BigUint& other);
    BigUint&    operator++();

    friend bool operator<(const BigUint& uuidL, const BigUint& uuidR);
    friend bool operator==(const BigUint& uuidL, const BigUint& uuidR);

    std::string num;
};
namespace std {
    template <>
    struct hash<BigUint> {
        std::size_t operator()(const BigUint& bigUint) const noexcept
        {
            return std::hash<std::string>{}(bigUint.num);
        }
    };
}  // namespace std