//
// Created by Rainy Li on 24-10-17.
//

#ifndef LRCSPEC_H
#define LRCSPEC_H
#include <vector>

#include "LrcTag.h"
#include "Lyrics.h"

namespace kmp {
    class LrcSpec {
    public:
        std::vector<LrcTag> tags;
        std::vector<Lyrics> lyrics;
    };
} // kmp

#endif //LRCSPEC_H
