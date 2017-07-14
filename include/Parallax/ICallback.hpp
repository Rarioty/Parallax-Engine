#ifndef PARALLAX_CALLBACK_HPP_GUARD
#define PARALLAX_CALLBACK_HPP_GUARD

#include <Parallax/Types.hpp>
#include <cstdarg>

namespace Parallax
{
    class ICallback
    {
    public:
        virtual ~ICallback() = 0;

        virtual void fatal(const char* message) = 0;
        virtual void traceVargs(const char* filepath, U16 line,
            const char* format, va_list argList);
    };

    inline ICallback::~ICallback(){}

    static ICallback*   g_callback = nullptr;
}

#endif
