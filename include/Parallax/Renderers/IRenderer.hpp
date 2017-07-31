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

        class IRenderer
        {
        public:
            virtual ~IRenderer() = 0;

            virtual bool            init(U32 width, U32 height) = 0;

            virtual RendererType    getRendererType() const = 0;
            virtual const char*     getRendererName() const = 0;

            virtual bool            isDeviceRemoved() = 0;
        };

        inline IRenderer::~IRenderer(){}

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

        IRenderer* GetRenderer(std::string renderer_name);
    }
}

#endif
