//
// Created by Rainy Li on 24-10-17.
//

#ifndef LRCSPEC_H
#define LRCSPEC_H
#include <vector>

#include "LrcTag.h"
#include "Lyrics.h"

namespace kmp::lrc {
    class LrcSpec {
    public:
        LrcSpec(std::vector<LrcTag> tags, std::vector<Lyrics> lyrics) : mTags(std::move(tags)), mLyrics(std::move(lyrics)) {
        }

        LrcSpec(const LrcSpec &other) = default;

        LrcSpec(LrcSpec &&other) noexcept = default;

        LrcSpec &operator=(const LrcSpec &other) = default;

        LrcSpec &operator=(LrcSpec &&other) = default;

    private:
        std::vector<LrcTag> mTags;
        std::vector<Lyrics> mLyrics;
    };
} // kmp::lrc

#endif //LRCSPEC_H
