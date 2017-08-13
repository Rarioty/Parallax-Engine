#ifndef PARALLAX_PROGRAM_HPP_GUARD
#define PARALLAX_PROGRAM_HPP_GUARD

#include <Parallax/Platform.hpp>
#include <glm/glm.hpp>
#include <string>
#include <map>

#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
    #include <Parallax/Renderers/RendererGL.hpp>
#endif

namespace Parallax
{
    namespace Renderer
    {
        union ProgramType
        {
#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
            GLenum  glType;
#endif
        };

        union ProgramLocationID
        {
#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
            GLuint  glLoc;
#endif
        };

        union ProgramShaderType
        {
#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
            GLenum  glType;
#endif
        };

        struct ProgramShaderSourcesComparator
        {
            bool operator()(const ProgramShaderType& a, const ProgramShaderType& b);
        };

        struct Program
        {
            typedef std::map<std::string, ProgramLocationID> LocationMap;
            LocationMap                                                                 m_uniformLocations;
            LocationMap                                                                 m_attributesLocations;
            std::map<ProgramShaderType, std::string, ProgramShaderSourcesComparator>    m_shaderSources;

            virtual                     ~Program(){};
            virtual void                addSource(ProgramShaderType type, const std::string& src) = 0;

            virtual void                create() = 0;
            virtual void                destroy() = 0;
            virtual void                compile() = 0;
            virtual void                link(const std::string& fragName, ProgramLocationID fragLocation) = 0;
            virtual void                link(LocationMap fragLocations, LocationMap attribLocations) = 0;

            virtual void                bind() = 0;
            virtual void                unbind() = 0;

            virtual ProgramLocationID   getUniformLocation(const std::string& name) = 0;
            virtual ProgramLocationID   getAttributeLocation(const std::string& name) = 0;

            virtual void                setUniform(ProgramLocationID loc, I32 val) = 0;
            virtual void                setUniform(ProgramLocationID loc, float val) = 0;
            virtual void                setUniform(ProgramLocationID loc, float* val, I32 count) = 0;
            virtual void                setUniform(ProgramLocationID loc, glm::vec2 val) = 0;
            virtual void                setUniform(ProgramLocationID loc, glm::vec3 val) = 0;
            virtual void                setUniform(ProgramLocationID loc, glm::vec4 val) = 0;
            virtual void                setUniform(ProgramLocationID loc, glm::mat4 val) = 0;
        };

        Program*    CreateProgram();
    }
}

#endif
