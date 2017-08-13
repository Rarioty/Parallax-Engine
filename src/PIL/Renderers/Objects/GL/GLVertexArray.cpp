#include <Parallax/Renderers/Objects/GL/GLVertexArray.hpp>

#if PARALLAX_GRAPHICS_OPENGL_ALLOWED

namespace Parallax::Renderer
{
    GLVertexArray::GLVertexArray()
    {
        m_uid = 0;
    }

    void GLVertexArray::create()
    {
        glGenVertexArrays(1, &m_uid);
        bind();
    }

    void GLVertexArray::destroy()
    {
        glDeleteVertexArrays(1, &m_uid);
        m_uid = 0;
    }

    void GLVertexArray::bind()
    {
        glBindVertexArray(m_uid);
    }

    void GLVertexArray::unbind()
    {
        glBindVertexArray(0);
    }
}

#endif
