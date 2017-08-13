#include <Parallax/Renderers/Objects/GL/GLBuffer.hpp>

#if PARALLAX_GRAPHICS_OPENGL_ALLOWED

namespace Parallax::Renderer
{
    #define BUFFER_OFFSET(i) (char*)NULL + i

    GLBuffer::GLBuffer()
    {
        m_uid = 0;
    }

    GLBuffer::~GLBuffer()
    {}

    void GLBuffer::create(BufferTarget target, BufferUsage usage)
    {
        m_target = target;
        m_usage  = usage;

        glGenBuffers(1, &m_uid);
        bind();
    }

    void GLBuffer::destroy()
    {
        glDeleteBuffers(1, &m_uid);
        m_uid = 0;
    }

    void GLBuffer::bind()
    {
        glBindBuffer(m_target.glTarget, m_uid);
    }

    void GLBuffer::unbind()
    {
        glBindBuffer(m_target.glTarget, 0);
    }

    void GLBuffer::upload(BufferSize size, const void* data)
    {
        m_size = size;
        glBufferData(m_target.glTarget, m_size.glSize, data, m_usage.glUsage);
    }

    void GLBuffer::configure(const VertexLayout& layout)
    {
        I32 offset = 0;
        for (const VertexLayoutAttribute& at : layout.m_attributes)
        {
            VertexLayoutAttribute::GLAttribute attrib = at.glAttribute;

            glEnableVertexAttribArray(attrib.location);
            glVertexAttribPointer(attrib.location, attrib.size,
                attrib.type, GL_FALSE, layout.m_stride.glStride, BUFFER_OFFSET(offset));
            offset += attrib.size * GL::GetGLTypeSize(attrib.type);
        }
    }

    void* GLBuffer::map(BufferUsage usage)
    {
        return glMapBuffer(m_target.glTarget, m_usage.glUsage);
    }

    void GLBuffer::unmap()
    {
        glUnmapBuffer(m_target.glTarget);
    }
}

#endif
