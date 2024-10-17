//
// Created by Rainy Li on 24-10-17.
//

#ifndef LRCTAG_H
#define LRCTAG_H
#include <sstream>
#include <string>
#include <array>
#include <utility>
#include <vector>

namespace kmp::lrc {

    constexpr char TAG_TI[] = "ti";
    constexpr char TAG_AR[] = "ar";
    constexpr char TAG_AL[] = "al";
    constexpr char TAG_AU[] = "au";
    constexpr char TAG_LENGTH[] = "length";
    constexpr char TAG_BY[] = "by";
    constexpr char TAG_OFFSET[] = "offset";
    constexpr char TAG_RE[] = "re";
    constexpr char TAG_TOOL[] = "tool";
    constexpr char TAG_VE[] = "ve";
    constexpr char TAG_COMMENTS[] = "#";


    class LrcTag {
    public:
        LrcTag(std::string_view tagName, std::string value): mTagName(tagName), mValue(std::move(value)) {
        }

        LrcTag(const LrcTag &other) = default;

        LrcTag(LrcTag &&other) noexcept;

        LrcTag &operator=(const LrcTag &other) = default;
        LrcTag &operator=(LrcTag &&other) noexcept;

        [[nodiscard]] std::string_view getTagName() const {
            return mTagName;
        }

        [[nodiscard]] const std::string &getValue() const {
            return mValue;
        }


    private:
        std::string_view mTagName;
        std::string mValue;

    public:
        static LrcTag ti(std::string value) {
            return {TAG_TI, std::move(value)};
        }

        static LrcTag ar(std::string value) {
            return {TAG_AR, std::move(value)};
        }

        static LrcTag al(std::string value) {
            return {TAG_AL, std::move(value)};
        }

        static LrcTag au(std::string value) {
            return {TAG_AU, std::move(value)};
        }

        static LrcTag length(std::string value) {
            return {TAG_LENGTH, std::move(value)};
        }

        static LrcTag by(std::string value) {
            return {TAG_BY, std::move(value)};
        }

        static LrcTag offset(std::string value) {
            return {TAG_OFFSET, std::move(value)};
        }

        static LrcTag re(std::string value) {
            return {TAG_RE, std::move(value)};
        }

        static LrcTag tool(std::string value) {
            return {TAG_TOOL, std::move(value)};
        }

        static LrcTag ve(std::string value) {
            return {TAG_VE, std::move(value)};
        }

        static LrcTag comments(std::string value) {
            return {TAG_COMMENTS, std::move(value)};
        }

        static bool isTi(const LrcTag &tag) {
            return tag.getTagName() == TAG_TI;
        }

        static bool isAr(const LrcTag &tag) {
            return tag.getTagName() == TAG_AR;
        }

        static bool isAl(const LrcTag &tag) {
            return tag.getTagName() == TAG_AL;
        }

        static bool isAu(const LrcTag &tag) {
            return tag.getTagName() == TAG_AU;
        }

        static bool isLength(const LrcTag &tag) {
            return tag.getTagName() == TAG_LENGTH;
        }

        static bool isBy(const LrcTag &tag) {
            return tag.getTagName() == TAG_BY;
        }

        static bool isOffset(const LrcTag &tag) {
            return tag.getTagName() == TAG_OFFSET;
        }

        static bool isRe(const LrcTag &tag) {
            return tag.getTagName() == TAG_RE;
        }

        static bool isTool(const LrcTag &tag) {
            return tag.getTagName() == TAG_TOOL;
        }

        static bool isVe(const LrcTag &tag) {
            return tag.getTagName() == TAG_VE;
        }

        static bool isComments(const LrcTag &tag) {
            return tag.getTagName() == TAG_COMMENTS;
        }
    };

} // kmp::lrc

#endif //LRCTAG_H
