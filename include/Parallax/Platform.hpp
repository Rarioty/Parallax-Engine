#ifndef PARALLAX_PLATFORM_HPP_GUARD
#define PARALLAX_PLATFORM_HPP_GUARD

/**
 * Include limits.h to include features.h when it exists and
 * so we have no error when it doesn't
 */
#include <limits.h>

/**
 * Architecture
 */
#define     PARALLAX_ARCH_32BIT     0
#define     PARALLAX_ARCH_64BIT     0

/**
 * Compiler
 */
#define     PARALLAX_COMPILER_CLANG     0
#define     PARALLAX_COMPILER_GCC       0
#define     PARALLAX_COMPILER_MSVC      0

/**
 * Endianness
 */
#define     PARALLAX_CPU_ENDIAN_BIG     0
#define     PARALLAX_CPU_ENDIAN_LITTLE  0

/**
 * CPU
 */
#define     PARALLAX_CPU_X86    0

/**
 * C runtime
 */
#define     PARALLAX_CRT_GLIBC  0
#define     PARALLAX_CRT_LIBCXX 0
#define     PARALLAX_CRT_MINGW  0
#define     PARALLAX_CRT_MSVC   0

/**
 * Platform
 */
#define     PARALLAX_PLATFORM_LINUX     0
#define     PARALLAX_PLATFORM_OSX       0
#define     PARALLAX_PLATFORM_PS4       0
#define     PARALLAX_PLATFORM_WINDOWS   0
#define     PARALLAX_PLATFORM_WINRT     0
#define     PARALLAX_PLATFORM_XBOXONE   0

/**
 * https://sourceforge.net/p/predef/wiki/Compilers/
 */
#if defined(__clang__)
    #undef  PARALLAX_COMPILER_CLANG
    #define PARALLAX_COMPILER_CLANG (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#elif defined(_MSC_VER)
    #undef  PARALLAX_COMPILER_MSVC
    #define PARALLAX_COMPILER_MSVC  _MSC_VER
#elif defined(__GNUC__)
    #undef  PARALLAX_COMPILER_GCC
    #define PARALLAX_COMPILER_GCC   (__GNUCC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
    #error "Compiler not supported !"
#endif

/**
 * https://sourceforge.net/p/predef/wiki/Architectures/
 */
#if defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__x86_64__)
    #undef  PARALLAX_CPU_X86
    #define PARALLAX_CPU_X86    1
    #define PARALLAX_CACHE_LINE_SIZE    64
#else
    #error  "CPU not supported"
#endif

#if defined(__x86_64__) || defined(_M_X64)
    #undef  PARALLAX_ARCH_64BIT
    #define PARALLAX_ARCH_64BIT     64
#else
    #undef  PARALLAX_ARCH_32BIT
    #define PARALLAX_ARCH_32BIT     32
#endif

#if defined(PARALLAX_CPU_X86)
    #undef  PARALLAX_CPU_ENDIAN_LITTLE
    #define PARALLAX_CPU_ENDIAN_LITTLE  1
#else
    #error "Endianness not recognized"
#endif

/**
 * https://sourceforge.net/p/predef/wiki/OperatingSystems/
 */
#if defined(_DURANGO) || defined(_XBOX_ONE)
    #undef  PARALLAX_PLATFORM_XBOXONE
    #define PARALLAX_PLATFORM_XBOXONE   1
#elif defined(__ORBIS__)
    #undef  PARALLAX_PLATFORM_PS4
    #define PARALLAX_PLATFORM_PS4   1
#elif defined(_WIN32) || defined(_WIN64)
    #if defined(_MSC_VER) && (_MSC_VER >= 1700) && (!_USING_V110_SDK71_)
        #include <winapifamily.h>
    #endif
    #if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
        #undef  PARALLAX_PLATFORM_WINDOWS
        #if !defined(WINVER) && !defined(_WIN32_WINNT)
            #if PARALLAX_ARCH_64BIT
                #define WINVER          0X0601
                #define _WIN32_WINNT    0X0601
            #else
                #define WINVER          0x0502
                #define _WIN32_WINNT    0X0502
            #endif
        #endif
        #define PARALLAX_PLATFORM_WINDOWS   _WIN32_WINNT
    #else
        #undef  PARALLAX_PLATFORM_WINRT
        #define PARALLAX_PLATFORM_WINRT 1
    #endif
#elif defined(__linux__)
    #undef  PARALLAX_PLATFORM_LINUX
    #define PARALLAX_PLATFORM_LINUX 1
#elif defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
    #undef  PARALLAX_PLATFORM_OSX
    #define PARALLAX_PLATFORM_OSX   __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__
#else
    #error "Operating system not supported"
#endif

/**
 * https://sourceforge.net/p/predef/wiki/Libraries/
 */
#if defined(_MSC_VER)
    #undef  PARALLAX_CRT_MSVC
    #define PARALLAX_CRT_MSVC   1
#elif defined(__GLIBC__)
    #undef  PARALLAX_CRT_GLIBC
    #define PARALLAX_CRT_GLIBC  (__GLIBC__ * 10000 + __GLIBC_MINOR__ * 100)
#elif defined(__MINGW32__) || defined(__MINGW64__)
    #undef  PARALLAX_CRT_MINGW
    #define PARALLAX_CRT_MINGW  1
#elif defined(__apple_build_version__) || defined(__ORBIS__) || defined(__llvm__)
    #undef  PARALLAX_CRT_LIBCXX
    #define PARALLAX_CRT_LIBCXX 1
#else
    #error "C Runtime not recognized !"
#endif

#define PARALLAX_PLATFORM_POSIX (0      \
    || PARALLAX_PLATFORM_LINUX          \
    || PARALLAX_PLATFORM_OSX            \
    || PARALLAX_PLATFORM_PS4            \
)

#if PARALLAX_COMPILER_GCC
    #define     PARALLAX_COMPILER_NAME  "GCC " \
        __GNUC__ "." \
        __GNUC_MINOR__ "." \
        __GNUC_PATCHLEVEL__
#elif PARALLAX_COMPILER_CLANG
    #define     PARALLAX_COMPILER_NAME  "Clang " \
        __clang_major__ "." \
        __clang_minor__ "." \
        __clang_patchlevel__
#elif PARALLAX_COMPILER_MSVC
    #if PARALLAX_COMPILER_MSVC >= 1910
        #define PARALLAX_COMPILER_NAME  "MSVC 15.0"
    #elif PARALLAX_COMPILER_MSVC >= 1900
        #define PARALLAX_COMPILER_NAME  "MSVC 14.0"
    #elif PARALLAX_COMPILER_MSVC >= 1800
        #define PARALLAX_COMPILER_NAME  "MSVC 12.0"
    #elif PARALLAX_COMPILER_MSVC >= 1700
        #define PARALLAX_COMPILER_NAME  "MSVC 11.0"
    #elif PARALLAX_COMPILER_MSVC >= 1600
        #define PARALLAX_COMPILER_NAME  "MSVC 10.0"
    #elif PARALLAX_COMPILER_MSVC >= 1500
        #define PARALLAX_COMPILER_NAME  "MSVC 9.0"
    #else
        #define PARALLAX_COMPILER_NAME  "MSVC"
    #endif
#else
    #error  "An error occured"
#endif

#if PARALLAX_PLATFORM_OSX
    #define     PARALLAX_PLATFORM_NAME  "OSX"
#elif PARALLAX_PLATFORM_PS4
    #define     PARALLAX_PLATFORM_NAME  "PlayStation 4"
#elif PARALLAX_PLATFORM_LINUX
    #define     PARALLAX_PLATFORM_NAME  "Linux"
#elif PARALLAX_PLATFORM_WINDOWS
    #define     PARALLAX_PLATFORM_NAME  "Windows"
#elif PARALLAX_PLATFORM_WINRT
    #define     PARALLAX_PLATFORM_NAME  "WinRT"
#elif PARALLAX_PLATFORM_XBOXONE
    #define     PARALLAX_PLATFORM_NAME  "Xbox One"
#else
    #error  "An error occured"
#endif

#if PARALLAX_CPU_X86
    #define     PARALLAX_CPU_NAME   "x86"
#else
    #error  "An error occured"
#endif

#if PARALLAX_CRT_MSVC
    #define     PARALLAX_CRT_NAME   "MSVC C Runtime"
#elif PARALLAX_CRT_GLIBC
    #define     PARALLAX_CRT_NAME   "GNU C Library"
#elif PARALLAX_CRT_MINGW
    #define     PARALLAX_CRT_NAME   "MinGW Runtime"
#elif PARALLAX_CRT_LIBCXX
    #define     PARALLAX_CRT_NAME   "Clang C Library"
#else
    #error  "An error occured"
#endif

#if PARALLAX_ARCH_32BIT
    #define     PARALLAX_ARCH_NAME  "32-bit"
#elif PARALLAX_ARCH_64BIT
    #define     PARALLAX_ARCH_NAME  "64-bit"
#else
    #error  "An error occured"
#endif

namespace Parallax
{
    struct PlatformData
    {
        void*   ndt;
        void*   nwh;
        void*   context;
        void*   backBuffer;
        void*   backBufferDS;
    };

    static PlatformData     g_platformData
    {
        .ndt            = nullptr,
        .nwh            = nullptr,
        .context        = nullptr,
        .backBuffer     = nullptr,
        .backBufferDS   = nullptr
    };
}

#endif
