#include <Parallax/Renderers/IRenderer.hpp>

#include <Parallax/Renderers/RendererVulkan.hpp>
#include <Parallax/Renderers/RendererGL.hpp>
#include <Parallax/Debug/Debug.hpp>

namespace Parallax::Renderer
{
    IRenderer* GetRenderer(std::string renderer_name)
    {
        IRenderer* renderer = nullptr;
        bool result;

        result = IsRendererAllowed(renderer_name);

        PARALLAX_FATAL(true == result, "Renderer %s not compiled with this version of Parallax Engine !", renderer_name.c_str());

#if PARALLAX_GRAPHICS_VULKAN_ALLOWED
        if (renderer_name == "vulkan")
        {
            renderer = new RendererVulkan();
        }
#endif
#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
        if (renderer_name == "opengl")
        {
            renderer = new RendererGL();
        }
#endif

        return renderer;
    }
}
