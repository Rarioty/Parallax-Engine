#include <Parallax/Strings.hpp>

#include <stdio.h>

namespace Parallax
{
    bool isSpace(char ch)
    {
        return ' '  == ch
            || '\t' == ch
            || '\n' == ch
            || '\v' == ch
            || '\f' == ch
            || '\r' == ch
            ;
    }

    inline bool isInRange(char ch, char from, char to)
    {
        return unsigned(ch - from) <= unsigned(to - from);
    }

    bool isUpper(char ch)
    {
        return isInRange(ch, 'A', 'Z');
    }

    bool isLower(char ch)
    {
        return isInRange(ch, 'a', 'z');
    }

    bool isAlpha(char ch)
    {
        return isLower(ch) || isUpper(ch);
    }

    bool isNumeric(char ch)
    {
        return isInRange(ch, '0', '9');
    }

    bool isAlphaNum(char ch)
    {
        return isAlpha(ch) || isNumeric(ch);
    }

    bool isPrint(char ch)
    {
        return isInRange(ch, ' ', '~');
    }

    char toLower(char ch)
    {
        return ch + (isUpper(ch) ? 0x20 : 0);
    }

    char toUpper(char ch)
    {
        return ch - (isLower(ch) ? 0x20 : 0);
    }

    bool toBool(const char* str)
    {
        char ch = toLower(str[0]);
        return ch == 't' || ch == '1';
    }
}
