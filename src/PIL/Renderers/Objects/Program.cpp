#include <Parallax/Renderers/Objects/Program.hpp>

#include <Parallax/Renderers/Objects/GL/GLProgram.hpp>

namespace Parallax::Renderer
{
    bool ProgramShaderSourcesComparator::operator()(const ProgramShaderType& a, const ProgramShaderType& b)
    {
#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
        if (GetRendererType() == RendererType::OpenGL)
        {
            return a.glType < b.glType;
        }
#endif

        return true;
    }

    Program* CreateProgram()
    {
        #if PARALLAX_GRAPHICS_OPENGL_ALLOWED
                if (Renderer::GetRendererType() == Renderer::RendererType::OpenGL)
                    return new GLProgram();
        #endif

        return nullptr;
    }
}
