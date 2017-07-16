#include <Parallax/Debug.hpp>

#include <Parallax/ICallback.hpp>
#include <Parallax/Platform.hpp>
#include <Parallax/Strings.hpp>
#include <Parallax/Macros.hpp>
#include <inttypes.h>
#include <cstdlib>
#include <stdio.h>

#if PARALLAX_PLATFORM_WINDOWS || PARALLAX_PLATFORM_WINRT || PARALLAX_PLATFORM_XBOXONE
    extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char* str);
	#include <intrin.h>
	#define alloca _alloca
#elif PARALLAX_PLATFORM_OSX
    #if defined(__OBJC__)
        #import <Foundation/NSObjCRuntime.h>
    #else
        #include <CoreFoundation/CFString.h>
        extern "C" void NSLog(CFStringRef _format, ...);
    #endif
	#include <alloca.h>
#else
    #include <cstdio>
	#include <alloca.h>
#endif

namespace Parallax
{
    void Fatal(const char* format, ...)
    {
        va_list argList;
        va_start(argList, format);

        if (NULL == g_callback)
        {
            Parallax::DebugPrintfVargs(format, argList);
            abort();
        }
        else
        {
            char temp[8192];
            char* message = temp;
            U32 len = vsnprintf(message, sizeof(temp), format, argList);
            if ((I32)sizeof(temp) < len)
            {
                message = (char*)alloca(len + 1);
                len = vsnprintf(message, len, format, argList);
            }
            message[len] = '\0';

            g_callback->fatal(message);
        }

        va_end(argList);
    }

    void Trace(const char* filepath, U16 line, const char* format, ...)
    {
        va_list argList;
        va_start(argList, format);

        if (NULL == g_callback)
        {
            Parallax::DebugPrintfVargs(format, argList);
        }
        else
        {
            g_callback->traceVargs(filepath, line, format, argList);
        }

        va_end(argList);
    }

    void DebugBreak()
    {
        #if PARALLAX_COMPILER_MSVC
			__debugbreak();
        #elif PARALLAX_CPU_X86 && (PARALLAX_COMPILER_CLANG || PARALLAX_COMPILER_GCC)
            __builtin_trap();
        #else
            int* int3 = (int*)0;
            *int3 = 3;
        #endif
    }

    void DebugOutput(const char* message)
    {
        #if PARALLAX_PLATFORM_WINDOWS || PARALLAX_PLATFORM_WINRT || PARALLAX_PLATFORM_XBOXONE
            OutputDebugStringA(message);
        #elif PARALLAX_PLATFORM_OSX
            #if defined(__OBJC__)
                NSLog(@"%s", message);
            #else
                NSLog(__CFStringMakeConstantString("%s"), message);
            #endif
        #else
            fputs(message, stdout);
            fflush(stdout);
        #endif
    }

    void DebugPrintfVargs(const char* format, va_list argList)
    {
        char temp[8192];
        char* message = temp;
        U32 len = vsnprintf(message, sizeof(temp), format, argList);
        if ((I32)sizeof(temp) < len)
        {
            message = (char*)alloca(len+1);
            len = vsnprintf(message, len, format, argList);
        }
        message[len] = '\0';

		fprintf(stderr, message);

        DebugOutput(message);
    }

    void DebugPrintf(const char* format, ...)
    {
        va_list argList;
        va_start(argList, format);
        DebugPrintfVargs(format, argList);
        va_end(argList);
    }

#define DBG_ADDRESS     "%" PRIxPTR

    void DebugPrintfData(const void* data, U32 size, const char* format, ...)
    {
        #define HEX_DUMP_WIDTH          16
        #define HEX_DUMP_SPACE_WIDTH    48
        #define HEX_DUMP_FORMAT         "%-" STRINGIZE(HEX_DUMP_SPACE_WIDTH) "." STRINGIZE(HEX_DUMP_WIDTH) "s"

        va_list argList;
        va_start(argList, format);
        DebugPrintfVargs(format, argList);
        va_end(argList);

        DebugPrintf("\ndata: " DBG_ADDRESS ", size: %d\n", data, size);

        if (NULL != data)
        {
            const U8* data = reinterpret_cast<const U8*>(data);
            char hex[HEX_DUMP_WIDTH*3+1];
            char ascii[HEX_DUMP_WIDTH+1];
            U32 hexPos = 0;
            U32 asciiPos = 0;

            for (U32 i = 0; i < size; ++i)
            {
                snprintf(&hex[hexPos], sizeof(hex) - hexPos, "%02x ", data[asciiPos]);
                hexPos += 3;

                ascii[asciiPos] = isPrint(data[asciiPos]) ? data[asciiPos] : '.';
                asciiPos++;

                if (HEX_DUMP_WIDTH == asciiPos)
                {
                    ascii[asciiPos] = '\0';
                    DebugPrintf("\t" DBG_ADDRESS "\t" HEX_DUMP_FORMAT "\t%s\n", data, hex, ascii);
                    data += asciiPos;
                    hexPos = 0;
                    asciiPos = 0;
                }
            }

            if (0 != asciiPos)
            {
                ascii[asciiPos] = '\0';
                DebugPrintf("\t" DBG_ADDRESS "\t" HEX_DUMP_FORMAT "\t%s\n", data, hex, ascii);
            }
        }

        #undef HEX_DUMP_WIDTH
        #undef HEX_DUMP_SPACE_WIDTH
        #undef HEX_DUMP_FORMAT
    }
}
