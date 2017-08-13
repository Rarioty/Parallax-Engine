#include <Parallax/Renderers/Objects/VertexArray.hpp>

#include <Parallax/Renderers/Objects/GL/GLVertexArray.hpp>

namespace Parallax
{
    namespace Renderer
    {
        VertexArray* CreateVertexArray()
        {
            #if PARALLAX_GRAPHICS_OPENGL_ALLOWED
                    if (Renderer::GetRendererType() == Renderer::RendererType::OpenGL)
                        return new GLVertexArray();
            #endif

            return nullptr;
        }
    }
}
