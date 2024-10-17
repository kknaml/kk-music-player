#pragma once

namespace kmp {

    class NonCopy {
    public:
        NonCopy() = default;
        NonCopy(const NonCopy &) = delete;
        NonCopy &operator=(const NonCopy &) = delete;
    };

} // namespace kmp
