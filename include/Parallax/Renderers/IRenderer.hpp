#ifndef PARALLAX_IRENDERER_HPP_GUARD
#define PARALLAX_IRENDERER_HPP_GUARD

namespace Parallax
{
    namespace Renderer
    {
        enum RendererType
        {
#if defined(PARALLAX_GRAPHICS_OPENGL_ALLOWED)
            OpenGL,
#endif
#if defined(PARALLAX_GRAPHICS_VULKAN_ALLOWED)
            Vulkan,
#endif

            COUNT
        };

        class IRenderer
        {
        public:
            virtual ~IRenderer() = 0;

            virtual bool            init() = 0;

            virtual RendererType    getRendererType() const = 0;
            virtual const char*     getRendererName() const = 0;

            virtual bool            isDeviceRemoved() = 0;
        };

        inline IRenderer::~IRenderer(){}
    }
}

#endif
