#include <Parallax/Renderers/RendererGL.hpp>

#include <Parallax/Platform.hpp>

#if PARALLAX_GRAPHICS_OPENGL_ALLOWED

#include <Parallax/Debug/Debug.hpp>
#include <iostream>

namespace Parallax::Renderer::GL
{
    static const char* s_vendor;
    static const char* s_renderer;
    static const char* s_version;
    static const char* s_glslVersion;

    static GLContext   s_glctx;

    static const char* getGLString(GLenum _name)
    {
        const char* str = (const char*)glGetString(_name);
        glGetError();
        if (NULL != str)
        {
            return str;
        }

        return "<unknown>";
    }

    static void setRenderContextSize(U32 width, U32 height, U32 flags = 0)
    {
        if (width != 0 && height != 0)
        {
            if (!s_glctx.isValid())
            {
                s_glctx.create(width, height);
            }
            else
            {
                s_glctx.resize(width, height, flags);
            }
        }
    }

    bool Init(U32 width, U32 height)
    {
        setRenderContextSize(width, height);

        s_vendor        = getGLString(GL_VENDOR);
        s_renderer      = getGLString(GL_RENDERER);
        s_version       = getGLString(GL_VERSION);
        s_glslVersion   = getGLString(GL_SHADING_LANGUAGE_VERSION);

        PARALLAX_TRACE("      Vendor: %s", s_vendor);
        PARALLAX_TRACE("    Renderer: %s", s_renderer);
        PARALLAX_TRACE("     Version: %s", s_version);
        PARALLAX_TRACE("GLSL version: %s", s_glslVersion);

        return true;
    }

	void Shutdown()
	{

	}

    RendererType GetRendererType()
    {
        return RendererType::OpenGL;
    }

    const char* GetRendererName()
    {
        return PARALLAX_GRAPHICS_OPENGL_NAME;
    }

    bool IsDeviceRemoved()
    {
        return false;
    }
}

#endif
