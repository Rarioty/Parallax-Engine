#ifndef RENDERER_CONFIG_HPP
#define RENDERER_CONFIG_HPP

#include <Parallax/Platform.hpp>

#define PARALLAX_DEFAULT_WIDTH      600
#define PARALLAX_DEFAULT_HEIGHT     480

#if !defined(PARALLAX_CONFIG_RENDERER_OPENGL)   \
  && !defined(PARALLAX_CONFIG_RENDERER_VULKAN)
    #ifndef PARALLAX_CONFIG_RENDERER_OPENGL
        #define PARALLAX_CONFIG_RENDERER_OPENGL (0  \
            || PARALLAX_PLATFORM_LINUX              \
            || PARALLAX_PLATFORM_OSX                \
            || PARALLAX_PLATFORM_WINDOWS            \
        ? 1 : 0)
    #endif

    #ifndef PARALLAX_CONFIG_RENDERER_VULKAN
        #define PARALLAX_CONFIG_RENDERER_VULKAN (0  \
            || PARALLAX_PLATFORM_LINUX              \
            || PARALLAX_PLATFORM_WINDOWS            \
        ? 1 : 0)
    #endif
#else
    #ifndef PARALLAX_CONFIG_RENDERER_OPENGL
        #define PARALLAX_CONFIG_RENDERER_OPENGL 0
    #endif

    #ifndef PARALLAX_CONFIG_RENDERER_VULKAN
        #define PARALLAX_CONFIG_RENDERER_VULKAN 0
    #endif
#endif

#if PARALLAX_CONFIG_RENDERER_OPENGL && PARALLAX_CONFIG_RENDERER_OPENGL < 21
    #undef  PARALLAX_CONFIG_RENDERER_OPENGL
    #define PARALLAX_CONFIG_RENDERER_OPENGL     21
#endif

#if PARALLAX_CONFIG_RENDERER_OPENGL && PARALLAX_CONFIG_RENDERER_OPENGL < 20
    #undef  PARALLAX_CONFIG_RENDERER_OPENGL
    #define PARALLAX_CONFIG_RENDERER_OPENGL     20
#endif

#define PARALLAX_RENDERER_VULKAN_NAME   "Vulkan"

#if PARALLAX_CONFIG_RENDERER_OPENGL
    #if PARALLAX_CONFIG_RENDERER_OPENGL >= 31 && PARALLAX_CONFIG_RENDERER_OPENGL <= 33
        #if PARALLAX_CONFIG_RENDERER_OPENGL == 31
            #define PARALLAX_RENDERER_OPENGL_NAME   "OpenGL 3.1"
        #elif PARALLAX_CONFIG_RENDERER_OPENGL == 32
            #define PARALLAX_RENDERER_OPENGL_NAME   "OpenGL 3.2"
        #else
            #define PARALLAX_RENDERER_OPENGL_NAME   "OpenGL 3.3"
        #endif
    #elif PARALLAX_CONFIG_RENDERER_OPENGL >= 40 && PARALLAX_CONFIG_RENDERER_OPENGL <= 45
        #if PARALLAX_CONFIG_RENDERER_OPENGL == 40
            #define PARALLAX_RENDERER_OPENGL_NAME   "OpenGL 4.0"
        #elif PARALLAX_CONFIG_RENDERER_OPENGL == 41
            #define PARALLAX_RENDERER_OPENGL_NAME   "OpenGL 4.1"
        #elif PARALLAX_CONFIG_RENDERER_OPENGL == 42
            #define PARALLAX_RENDERER_OPENGL_NAME   "OpenGL 4.2"
        #elif PARALLAX_CONFIG_RENDERER_OPENGL == 43
            #define PARALLAX_RENDERER_OPENGL_NAME   "OpenGL 4.3"
        #elif PARALLAX_CONFIG_RENDERER_OPENGL == 44
            #define PARALLAX_RENDERER_OPENGL_NAME   "OpenGL 4.4"
        #else
            #define PARALLAX_RENDERER_OPENGL_NAME   "OpenGL 4.5"
        #endif
    #else
        #define PARALLAX_RENDERER_OPENGL_NAME       "OpenGL 2.1"
    #endif
#endif

#endif
