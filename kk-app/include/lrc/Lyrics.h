//
// Created by Rainy Li on 24-10-17.
//

#ifndef LYRICS_H
#define LYRICS_H
#include <string>

namespace kmp::lrc {
    class Lyrics {
    public:

        Lyrics(int start, int end, std::string text) : mStart(start), mEnd(end), mText(std::move(text)) {
        }

        Lyrics(Lyrics &&other) noexcept = default;

        Lyrics &operator=(const Lyrics &other) = default;

        Lyrics &operator=(Lyrics &&other) = default;

        [[nodiscard]]
        int getStart() const {
            return mStart;
        }

        [[nodiscard]]
        int getEnd() const {
            return mEnd;
        }

        [[nodiscard]]
        const std::string &getText() const {
            return mText;
        }

    private:
        int mStart;
        int mEnd;
        std::string mText;
    };
} // kmp::lrc

#endif //LYRICS_H
