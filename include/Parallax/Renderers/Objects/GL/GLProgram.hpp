#ifndef PARALLAX_GL_PROGRAM_HPP_GUARD
#define PARALLAX_GL_PROGRAM_HPP_GUARD

#include <Parallax/Renderers/Objects/Program.hpp>

#if PARALLAX_GRAPHICS_OPENGL_ALLOWED

namespace Parallax
{
    namespace Renderer
    {
        struct GLProgram : Program
        {
            GLuint  m_uid;
            GLint   m_complete;

            GLProgram();
            void                addSource(ProgramShaderType type, const std::string& src);

            void                create();
            void                destroy();
            void                compile();
            void                link(const std::string& fragName, ProgramLocationID fragLocation);
            void                link(LocationMap fragLocations, LocationMap attribLocations);

            void                bind();
            void                unbind();

            ProgramLocationID   getUniformLocation(const std::string& name);
            ProgramLocationID   getAttributeLocation(const std::string& name);

            void                setUniform(ProgramLocationID loc, I32 val);
            void                setUniform(ProgramLocationID loc, float val);
            void                setUniform(ProgramLocationID loc, float* val, I32 count);
            void                setUniform(ProgramLocationID loc, glm::vec2 val);
            void                setUniform(ProgramLocationID loc, glm::vec3 val);
            void                setUniform(ProgramLocationID loc, glm::vec4 val);
            void                setUniform(ProgramLocationID loc, glm::mat4 val);
        };
    }
}

#endif

#endif
