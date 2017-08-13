#ifndef PARALLAX_VERTEX_ARRAY_HPP_GUARD
#define PARALLAX_VERTEX_ARRAY_HPP_GUARD

namespace Parallax
{
    namespace Renderer
    {
        struct VertexArray
        {
            virtual void create() = 0;
            virtual void destroy() = 0;
            virtual void bind() = 0;
            virtual void unbind() = 0;
        };

        VertexArray*    CreateVertexArray();
    }
}

#endif
