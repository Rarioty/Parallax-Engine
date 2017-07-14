#ifndef PARALLAX_STRINGS_HPP_GUARD
#define PARALLAX_STRINGS_HPP_GUARD

namespace Parallax
{
    bool isSpace(char ch);
    bool isUpper(char ch);
    bool isLower(char ch);
    bool isAlpha(char ch);
    bool isNumeric(char ch);
    bool isAlphaNum(char ch);
    bool isPrint(char ch);
    char toLower(char ch);
    char toUpper(char ch);
    bool toBool(const char* ch);
}

#endif
