#ifndef PARALLAX_BUFFER_HPP_GUARD
#define PARALLAX_BUFFER_HPP_GUARD

#include <Parallax/Platform.hpp>

#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
    #include <Parallax/Renderers/RendererGL.hpp>
#endif

#include <vector>

namespace Parallax
{
    namespace Renderer
    {
        union BufferTarget
        {
#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
            GLenum  glTarget;
#endif
        };

        union BufferUsage
        {
#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
            GLenum  glUsage;
#endif
        };

        union BufferSize
        {
#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
            GLsizeiptr  glSize;
#endif
        };

        union VertexLayoutAttribute
        {
#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
            struct GLAttribute
            {
                GLint   location;
                GLint   size;
                GLint   type;
            } glAttribute;
#endif
        };

        union VertexLayoutStride
        {
#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
            GLsizei     glStride;
#endif
        };

        struct VertexLayout
        {
            VertexLayoutStride                  m_stride;
            std::vector<VertexLayoutAttribute>  m_attributes;

            VertexLayout();
            void addAttribute(VertexLayoutAttribute attribute);
            void fitStrideToAttributes();
        };

        struct Buffer
        {
            BufferTarget    m_target;
            BufferUsage     m_usage;
            BufferSize      m_size;

            virtual void    create(BufferTarget target, BufferUsage usage) = 0;
            virtual void    destroy() = 0;
            virtual void    bind() = 0;
            virtual void    unbind() = 0;

            virtual void    upload(BufferSize size, const void* data) = 0;
            virtual void    configure(const VertexLayout& layout) = 0;

            virtual void*   map(BufferUsage usage) = 0;
            virtual void    unmap() = 0;
        };

        Buffer*     CreateBuffer();
    }
}

#endif
