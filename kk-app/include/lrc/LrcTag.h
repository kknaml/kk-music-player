//
// Created by Rainy Li on 24-10-17.
//

#ifndef LRCTAG_H
#define LRCTAG_H
#include <sstream>
#include <string>

namespace kmp {
    enum LrcTagEnum {
        TI,
        AR,
        AL,
        AU,
        LENGTH,
        BY,
        OFFSET,
        RE,
        TOOL,
        VE,
        COMMENTS,
        TAG_COUNT
    };
    const std::array<std::string, TAG_COUNT> lrcTagStrings = {
        "ti", "ar", "al", "au", "length",
        "by", "offset", "re", "tool", "ve", "#"
    };

    class LrcTag {
    public:
        LrcTagEnum tag;
        std::string_view tagName;
        std::string value;
        LrcTag(const LrcTagEnum tag, const std::string &value) {
            this->tag = tag;
            this->tagName = lrcTagStrings[tag];
            this->value = value;
        }
    };

    class Ti : public LrcTag {
    public:
        explicit Ti(const std::string &value): LrcTag(TI, value) {
        }
    };
    class Ar : public LrcTag {
    public:
        explicit Ar(const std::string &value): LrcTag(AR, value) {
        }
    };
    class Al : public LrcTag {
    public:
        explicit Al(const std::string &value): LrcTag(AL, value) {
        }
    };
    class Au : public LrcTag {
    public:
        explicit Au(const std::string &value): LrcTag(AU, value) {
        }
    };
    class Length : public LrcTag {
    public:
        int lenInMils = 0;
        explicit Length(const std::string &value): LrcTag(LENGTH, value) {
            std::stringstream ss(value);
            std::string item;
            std::vector<int> parts;
            while (std::getline(ss,item,':')) {
                parts.push_back(std::stoi(item));
            }
            lenInMils = parts[0]*60*1000+parts[1]*1000;
        }
    };
    class By : public LrcTag {
    public:
        explicit By(const std::string &value): LrcTag(BY, value) {
        }
    };
    class Offset : public LrcTag {
    public:
        explicit Offset(const std::string &value): LrcTag(OFFSET, value) {
        }
    };
    class Re : public LrcTag {
    public:
        explicit Re(const std::string &value): LrcTag(RE, value) {
        }
    };
    class Tool : public LrcTag {
    public:
        explicit Tool(const std::string &value): LrcTag(TOOL, value) {
        }
    };
    class Ve : public LrcTag {
    public:
        explicit Ve(const std::string &value): LrcTag(VE, value) {
        }
    };
    class Comments : public LrcTag {
    public:
        explicit Comments(const std::string &value): LrcTag(COMMENTS, value) {
        }
    };
} // kmp

#endif //LRCTAG_H
