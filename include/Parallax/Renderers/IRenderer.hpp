#ifndef IRENDERER_HPP
#define IRENDERER_HPP

namespace Parallax
{
    namespace Renderer
    {
        enum RendererType
        {
            OpenGL,
            Vulkan,

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
