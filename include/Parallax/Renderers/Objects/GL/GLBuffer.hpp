#ifndef PARALLAX_GL_BUFFER_HPP_GUARD
#define PARALLAX_GL_BUFFER_HPP_GUARD

#include <Parallax/Renderers/Objects/Buffer.hpp>

#if PARALLAX_GRAPHICS_OPENGL_ALLOWED

#include <Parallax/Renderers/RendererGL.hpp>

namespace Parallax
{
    namespace Renderer
    {
        struct GLBuffer : Buffer
        {
            GLuint  m_uid;

            GLBuffer();
            void    create(BufferTarget target, BufferUsage usage);
            void    destroy();
            void    bind();
            void    unbind();

            void    upload(BufferSize size, const void* data);
            void    configure(const VertexLayout& layout);

            void*   map(BufferUsage usage);
            void    unmap();
        };
    }
}

#endif

#endif
