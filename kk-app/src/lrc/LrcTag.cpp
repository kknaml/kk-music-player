//
// Created by Rainy Li on 24-10-17.
//

#include <lrc/LrcTag.h>

namespace kmp::lrc {
    LrcTag::LrcTag(LrcTag &&other) noexcept : mTagName(other.mTagName), mValue(std::move(other.mValue)) {
    }

    LrcTag & LrcTag::operator=(LrcTag &&other) noexcept {
        if (this == &other) {
            return *this;
        }
        this->mValue = other.mValue;
        this->mTagName = other.mTagName;
        return *this;
    }
} // namespace kmp::lrc
