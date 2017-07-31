#include <Parallax/Renderers/RendererGL.hpp>

#if PARALLAX_GRAPHICS_OPENGL_ALLOWED

#include <Parallax/Debug/Debug.hpp>
#include <iostream>

namespace Parallax::Renderer
{
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

    RendererGL::RendererGL()
    {
    }

    RendererGL::~RendererGL()
    {

    }

    bool RendererGL::init(U32 width, U32 height)
    {
        setRenderContextSize(width, height);

        m_vendor        = getGLString(GL_VENDOR);
        m_renderer      = getGLString(GL_RENDERER);
        m_version       = getGLString(GL_VERSION);
        m_glslVersion   = getGLString(GL_SHADING_LANGUAGE_VERSION);

        PARALLAX_TRACE("      Vendor: %s", m_vendor);
        PARALLAX_TRACE("    Renderer: %s", m_renderer);
        PARALLAX_TRACE("     Version: %s", m_version);
        PARALLAX_TRACE("GLSL version: %s", m_glslVersion);

        return true;
    }

    RendererType RendererGL::getRendererType() const
    {
        return RendererType::OpenGL;
    }

    const char* RendererGL::getRendererName() const
    {
        return PARALLAX_GRAPHICS_OPENGL_NAME;
    }

    bool RendererGL::isDeviceRemoved()
    {
        return false;
    }

    void RendererGL::setRenderContextSize(U32 width, U32 height, U32 flags)
    {
        if (width != 0 && height != 0)
        {
            if (!m_glctx.isValid())
            {
                m_glctx.create(width, height);
            }
            else
            {
                m_glctx.resize(width, height, flags);
            }
        }
    }
}

#endif
