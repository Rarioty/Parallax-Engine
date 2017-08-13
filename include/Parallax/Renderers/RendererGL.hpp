#ifndef PARALLAX_RENDERER_GL_HPP_GUARD
#define PARALLAX_RENDERER_GL_HPP_GUARD

#include <Parallax/Renderers/Renderer.hpp>
#include <Parallax/Platform.hpp>
#include <Parallax/Types.hpp>

#define PARALLAX_USE_WGL    (PARALLAX_GRAPHICS_OPENGL_ALLOWED && PARALLAX_PLATFORM_WINDOWS)
#define PARALLAX_USE_GLX    (PARALLAX_GRAPHICS_OPENGL_ALLOWED && PARALLAX_PLATFORM_LINUX)

#if PARALLAX_PLATFORM_WINDOWS
	#include <Windows.h>
#elif PARALLAX_PLATFORM_LINUX
	#include <Parallax/Renderers/GLContexts/glx.hpp>
#endif

#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
    #if PARALLAX_PLATFORM_LINUX
		#include <GL/glew.h>
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
		#include <GL/glew.h>
        #include <GL/gl.h>
    #endif
#endif

#if PARALLAX_USE_WGL
	#include <Parallax/Renderers/GLContexts/wgl.hpp>
#endif

namespace Parallax
{
    namespace Renderer
    {
		namespace GL
		{
			bool 			Init(U32 width, U32 height);
			void 			Shutdown();

	        const char* 	GetRendererName();
	        RendererType 	GetRendererType();
	        bool            IsDeviceRemoved();

			void 			WindowResized(U32 width, U32 height);
			void 			SwapBuffers();

			size_t  		GetGLTypeSize(GLenum type);
			const char* 	GetGLShaderTypename(GLenum type);
		}
    }
}

#endif
