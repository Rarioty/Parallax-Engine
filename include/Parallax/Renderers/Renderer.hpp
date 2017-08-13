#ifndef PARALLAX_IRENDERER_HPP_GUARD
#define PARALLAX_IRENDERER_HPP_GUARD

#include <Parallax/Platform.hpp>
#include <Parallax/Types.hpp>
#include <string>

extern "C"{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

namespace Parallax
{
    namespace Renderer
    {
        enum RendererType
        {
#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
            OpenGL,
#endif
#if PARALLAX_GRAPHICS_VULKAN_ALLOWED
            Vulkan,
#endif

            COUNT
        };

        bool            Init(std::string renderer_name, U32 width, U32 height);
        void            Shutdown();

        const char*     GetRendererName();
        RendererType    GetRendererType();
        bool            IsDeviceRemoved();

        void            WindowResized(U32 width, U32 height);
        void            SwapBuffers();
    }
}

#endif
