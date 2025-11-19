#pragma once
#include <string>

struct BigUint {
    BigUint() = default;
    BigUint(const std::string& num);
    BigUint(const BigUint& other);

    BigUint&    operator=(const BigUint& other);
    BigUint&    operator++();

    bool        operator<(const BigUint& other) const;

    bool        operator==(const BigUint& other) const;
    bool        operator==(const char* rhs) const;
    bool        operator!=(const BigUint& other) const;
    bool        operator!=(const char* rhs) const;

    std::string num = "0";
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