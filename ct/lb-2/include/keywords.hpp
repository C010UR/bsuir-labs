#pragma once

#include <string>
#include <unordered_set>

enum class KeywordType
{
    None,
    If,
    Return
};

const std::unordered_set<std::string> keywords = {
    "and",      "as",      "assert", "break", "class",  "continue", "def",    "del", "elif",  "else",   "except",
    "false",    "finally", "for",    "from",  "global", "if",       "import", "in",  "is",    "lambda", "none",
    "nonlocal", "not",     "or",     "pass",  "raise",  "return",   "true",   "try", "while", "with",   "yield",
};


KeywordType toKeyword(std::string keyword) {
    if (keyword == "if") {
        return KeywordType::If;
    }

    if (keyword == "return") {
        return KeywordType::Return;
    }

    return KeywordType::None;
}