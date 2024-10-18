#pragma once
#include <cstdint>
#include <kmp_common.hpp>
#include <vector>

namespace kmp {

    template<typename T>
    concept CMusicPlayer = requires(T player) {
        player.resume();
        player.pause();
    };

    class MusicPlayer : public NonCopy {
    public:
        void load(const char *path);

        [[nodiscard]] const uint8_t *data() const {
            return mData.data();
        }

        [[nodiscard]] size_t dataSize() const {
            return mData.size();
        }


    private:
        bool mIsLoaded{false};
        std::vector<uint8_t> mData{};
    };
}
