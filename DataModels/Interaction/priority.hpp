#pragma once
#include <stdint.h>

#include "location.hpp"

enum class Priority : uint8_t { Low, Medium, High, Critical, null, COUNT };

inline std::string priorityToStr(const Priority priority)
{
    switch (priority) {
        case Priority::Low:
            return priority_str::low;
        case Priority::Medium:
            return priority_str::medium;
        case Priority::High:
            return priority_str::high;
        case Priority::Critical:
            return priority_str::critical;
        case Priority::null:
            return priority_str::null;
    }
    return std::string();
}