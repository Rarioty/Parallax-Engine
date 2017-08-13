#include <Parallax/Renderers/Renderer.hpp>

#include <Parallax/Renderers/RendererVulkan.hpp>
#include <Parallax/Renderers/RendererGL.hpp>
#include <Parallax/Debug/Debug.hpp>

namespace Parallax::Renderer
{
    static std::string s_renderer = "";

    inline bool IsRendererAllowed(std::string renderer)
    {
        if (renderer == "vulkan")
        {
#if PARALLAX_GRAPHICS_VULKAN_ALLOWED
            return true;
#else
            return false;
#endif
        }
        else if (renderer == "opengl")
        {
#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
            return true;
#else
            return false;
#endif
        }

        return false;
    }

    bool Init(std::string renderer_name, U32 width, U32 height)
    {
        bool result = IsRendererAllowed(renderer_name);

        PARALLAX_FATAL(true == result, "Renderer %s not compiled in this version of Parallax Engine !", renderer_name.c_str());

        s_renderer = renderer_name;

        result = false;
#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
        if (renderer_name == "opengl")
        {
            result = GL::Init(width, height);
        }
#endif
#if PARALLAX_GRAPHICS_VULKAN_ALLOWED
        if (renderer_name == "vulkan")
        {
            result = Vulkan::Init(width, height);
        }
#endif

        return result;
    }

    void Shutdown()
    {
#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
        if (s_renderer == "opengl")
        {
            GL::Shutdown();
        }
#endif
#if PARALLAX_GRAPHICS_VULKAN_ALLOWED
        if (s_renderer == "vulkan")
        {
            Vulkan::Shutdown();
        }
#endif
    }

    const char* GetRendererName()
    {
        PARALLAX_FATAL("" != s_renderer, "Renderer not initialized !");

#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
        if (s_renderer == "opengl")
        {
            return GL::GetRendererName();
        }
#endif
#if PARALLAX_GRAPHICS_VULKAN_ALLOWED
        if (s_renderer == "vulkan")
        {
            return Vulkan::GetRendererName();
        }
#endif

        return nullptr;
    }

    RendererType GetRendererType()
    {
        PARALLAX_FATAL("" != s_renderer, "Renderer not initialized !");

#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
        if (s_renderer == "opengl")
        {
            return GL::GetRendererType();
        }
#endif
#if PARALLAX_GRAPHICS_VULKAN_ALLOWED
        if (s_renderer == "vulkan")
        {
            return Vulkan::GetRendererType();
        }
#endif

        return RendererType::COUNT;
    }

    bool IsDeviceRemoved()
    {
        PARALLAX_FATAL("" != s_renderer, "Renderer not initialized !");

#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
        if (s_renderer == "opengl")
        {
            return GL::IsDeviceRemoved();
        }
#endif
#if PARALLAX_GRAPHICS_VULKAN_ALLOWED
        if (s_renderer == "vulkan")
        {
            return Vulkan::IsDeviceRemoved();
        }
#endif

        return false;
    }

    void WindowResized(U32 width, U32 height)
    {
        PARALLAX_FATAL("" != s_renderer, "Renderer not initialized !");

#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
        if (s_renderer == "opengl")
        {
            return GL::WindowResized(width, height);
        }
#endif
#if PARALLAX_GRAPHICS_VULKAN_ALLOWED
        if (s_renderer == "vulkan")
        {
            return Vulkan::WindowResized(width, height);
        }
#endif
    }

    void SwapBuffers()
    {
        PARALLAX_FATAL("" != s_renderer, "Renderer not initialized !");

#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
        if (s_renderer == "opengl")
        {
            return GL::SwapBuffers();
        }
#endif
#if PARALLAX_GRAPHICS_VULKAN_ALLOWED
        if (s_renderer == "vulkan")
        {
            return Vulkan::SwapBuffers();
        }
#endif
    }
}
