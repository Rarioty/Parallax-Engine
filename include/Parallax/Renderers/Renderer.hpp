#ifndef PARALLAX_IRENDERER_HPP_GUARD
#define PARALLAX_IRENDERER_HPP_GUARD

#include <Parallax/Platform.hpp>
#include <Parallax/Types.hpp>
#include <string>

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

        bool Init(std::string renderer_name, U32 width, U32 height);
        void Shutdown();

        const char*     GetRendererName();
        RendererType    GetRendererType();
        bool            IsDeviceRemoved();
    }
}

#endif
