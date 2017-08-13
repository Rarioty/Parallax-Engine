#ifndef PARALLAX_GL_VERTEX_ARRAY_HPP_GUARD
#define PARALLAX_GL_VERTEX_ARRAY_HPP_GUARD

#include <Parallax/Renderers/Objects/VertexArray.hpp>
#include <Parallax/Platform.hpp>

#if PARALLAX_GRAPHICS_OPENGL_ALLOWED

#include <Parallax/Renderers/RendererGL.hpp>

namespace Parallax
{
    namespace Renderer
    {
        struct GLVertexArray : public VertexArray
        {
            GLuint  m_uid;

            GLVertexArray();
            ~GLVertexArray();

            void create();
            void destroy();
            void bind();
            void unbind();
        };
    }
}

#endif

#endif
