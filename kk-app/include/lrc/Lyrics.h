//
// Created by Rainy Li on 24-10-17.
//

#ifndef LYRICS_H
#define LYRICS_H
#include <string>

namespace kmp {
    class Lyrics {
    public:
        int ts = 0;
        int endts = 0;
        std::string_view text;
        Lyrics(int ts,int endts,std::string_view text) {
            this->ts = ts;
            this->endts = endts;
            this->text = text;
        }
    };
} // kmp

#endif //LYRICS_H
