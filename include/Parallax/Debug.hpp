#ifndef PARALLAX_DEBUG_HPP_GUARD
#define PARALLAX_DEBUG_HPP_GUARD

#include <Parallax/Types.hpp>
#include <cstdarg>

namespace Parallax
{
    void Fatal(const char* format, ...);
    void Trace(const char* filePath, U16 line, const char* format, ...);

    #define PARALLAX_TRACE(format, ...) \
        Parallax::Trace(__FILE__, U16(__LINE__), "Parallax " format "\n", ##__VA_ARGS__);

    #define PARALLAX_WARN(condition, format, ...)   \
        if (!condition)                             \
            PARALLAX_TRACE("WARN " format, ##__VA_ARGS__);

    #define PARALLAX_CHECK(condition, format, ...)          \
        if (!condition)                                     \
        {                                                   \
            PARALLAX_TRACE("CHECK " format, ##__VA_ARGS__); \
            Parallax::Fatal(format, ##__VA_ARGS__);         \
        }

    #define PARALLAX_FATAL(condition, format, ...)     \
        if (!condition)                                     \
            Parallax::Fatal(format, ##__VA_ARGS__);

    void DebugBreak();
    void DebugOutput(const char* message);
    void DebugPrintfVargs(const char* format, va_list argList);
    void DebugPrintf(const char* format, ...);
    void DebugPrintfData(const void* data, U32 size, const char* format, ...);
}

#endif
