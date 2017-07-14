#include <Parallax/Renderers/RendererGL.hpp>

#if PARALLAX_CONFIG_RENDERER_OPENGL

#include <Parallax/Renderers/Config.hpp>
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

    bool RendererGL::init()
    {
        setRenderContextSize(PARALLAX_DEFAULT_WIDTH, PARALLAX_DEFAULT_HEIGHT);

        m_vendor        = getGLString(GL_VENDOR);
        m_renderer      = getGLString(GL_RENDERER);
        m_version       = getGLString(GL_VERSION);
        m_glslVersion   = getGLString(GL_SHADING_LANGUAGE_VERSION);

        std::cout << "      Vendor: " << m_vendor << std::endl;
        std::cout << "    Renderer: " << m_renderer << std::endl;
        std::cout << "     Version: " << m_version << std::endl;
        std::cout << "GLSL version: " << m_glslVersion << std::endl;

        return true;
    }

    RendererType RendererGL::getRendererType() const
    {
        #if PARALLAX_CONFIG_RENDERER_OPENGL
            return RendererType::OpenGL;
        #else
            return RendererType::COUNT;
        #endif
    }

    const char* RendererGL::getRendererName() const
    {
        return PARALLAX_RENDERER_OPENGL_NAME;
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
