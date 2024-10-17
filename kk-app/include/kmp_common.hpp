#pragma once

#include "kmp_defines.hpp"

namespace kmp {

    class NonCopy {
    public:
        NonCopy() = default;
        NonCopy(const NonCopy &) = delete;
        NonCopy &operator=(const NonCopy &) = delete;
    };

} // namespace kmp
