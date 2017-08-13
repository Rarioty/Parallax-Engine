#include <Parallax/Renderers/Objects/Buffer.hpp>

#include <Parallax/Renderers/Renderer.hpp>

#include <map>

#include <Parallax/Renderers/Objects/GL/GLBuffer.hpp>

namespace Parallax::Renderer
{
    static void initStride(VertexLayoutStride& stride)
    {
#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
        if (Renderer::GetRendererType() == Renderer::RendererType::OpenGL)
        {
            stride.glStride = 0;
        }
#endif
    }

    VertexLayout::VertexLayout()
    {
        initStride(m_stride);
    }

    void VertexLayout::addAttribute(VertexLayoutAttribute attribute)
    {
        m_attributes.push_back(attribute);
    }

    void VertexLayout::fitStrideToAttributes()
    {
        initStride(m_stride);

#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
        if (Renderer::GetRendererType() == Renderer::RendererType::OpenGL)
            for (VertexLayoutAttribute& attrib : m_attributes)
                m_stride.glStride += attrib.glAttribute.size * GL::GetGLTypeSize(attrib.glAttribute.type);
#endif
    }

    Buffer* CreateBuffer()
    {
        #if PARALLAX_GRAPHICS_OPENGL_ALLOWED
                if (Renderer::GetRendererType() == Renderer::RendererType::OpenGL)
                    return new GLBuffer();
        #endif

        return nullptr;
    }
}
