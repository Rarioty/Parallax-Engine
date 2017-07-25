#ifndef PARALLAX_RENDERER_GL_HPP_GUARD
#define PARALLAX_RENDERER_GL_HPP_GUARD

#include <Parallax/Renderers/IRenderer.hpp>
#include <Parallax/Renderers/Config.hpp>
#include <Parallax/Platform.hpp>
#include <Parallax/Types.hpp>

#if PARALLAX_CONFIG_RENDERER_OPENGL

#define PARALLAX_USE_WGL    (PARALLAX_CONFIG_RENDERER_OPENGL && PARALLAX_PLATFORM_WINDOWS)
#define PARALLAX_USE_GLX    (PARALLAX_CONFIG_RENDERER_OPENGL && PARALLAX_PLATFORM_LINUX)

#if PARALLAX_PLATFORM_WINDOWS
	#include <Windows.h>
#elif PARALLAX_PLATFORM_LINUX
	#include <Parallax/Renderers/GLContexts/glx.hpp>
#endif

#if PARALLAX_CONFIG_RENDERER_OPENGL
    #if PARALLAX_CONFIG_RENDERER_OPENGL >= 31
        #include <GL/glcorearb.h>
        #if PARALLAX_PLATFORM_OSX
            #define GL_ARB_shader_objects
        #endif
    #else
        #if PARALLAX_PLATFORM_LINUX
            #define GL_PROTOTYPES
            #define GL_GLEXT_LEGACY
            #include <GL/gl.h>
            #undef  GL_PROTOTYPES
        #elif PARALLAX_PLATFORM_OSX
            #define GL_GLEXT_LEGACY
            #define long ptrdiff_t
            #include <OpenGL/gl.h>
            #undef long
            #undef GL_VERSION_1_2
            #undef GL_VERSION_1_3
            #undef GL_VERSION_1_4
            #undef GL_VERSION_1_4
            #undef GL_VERSION_1_5
            #undef GL_VERSION_2_0
        #else
            #include <GL/gl.h>
        #endif

        #include <gl/glext.h>
    #endif
#endif

#if PARALLAX_USE_WGL
	#include <Parallax/Renderers/GLContexts/wgl.hpp>
#endif

namespace Parallax
{
    namespace Renderer
    {
        class RendererGL : public IRenderer
        {
        public:
            RendererGL();
            ~RendererGL() override;

            bool            init() override;

            RendererType    getRendererType() const override;
            const char*     getRendererName() const override;

            bool            isDeviceRemoved() override;

        private:
            void            setRenderContextSize(U32 width, U32 height, U32 flags = 0);

        private:
            const char* m_vendor;
            const char* m_renderer;
            const char* m_version;
            const char* m_glslVersion;

            GLContext   m_glctx;
        };
    }
}

#endif

#endif
