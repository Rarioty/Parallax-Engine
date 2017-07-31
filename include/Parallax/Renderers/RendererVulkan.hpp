#ifndef PARALLAX_RENDERER_VULKAN_HPP_GUARD
#define PARALLAX_RENDERER_VULKAN_HPP_GUARD

#include <Parallax/Renderers/Renderer.hpp>
#include <Parallax/Platform.hpp>

namespace Parallax
{
    namespace Renderer
    {
        namespace Vulkan
        {
            bool Init(U32 width, U32 height);
            void Shutdown();

            const char*     GetRendererName();
            RendererType    GetRendererType();
            bool            IsDeviceRemoved();
        }
    }
}

#endif
