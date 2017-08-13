#include <Parallax/Renderers/Objects/GL/GLProgram.hpp>

#if PARALLAX_GRAPHICS_OPENGL_ALLOWED

#include <Parallax/Debug/Debug.hpp>

namespace Parallax::Renderer
{
    GLProgram::GLProgram()
    {
        m_uid       = 0;
        m_complete  = GL_FALSE;
    }

    void GLProgram::create()
    {
        m_uid = glCreateProgram();
    }

    void GLProgram::destroy()
    {
        glDeleteProgram(m_uid);
        m_uid = 0;
    }

    void GLProgram::addSource(ProgramShaderType type, const std::string& src)
    {
        m_shaderSources[type] += src;
    }

    void GLProgram::compile()
    {
        for (auto& shader : m_shaderSources)
        {
            GLuint suid = glCreateShader(shader.first.glType);

            const char* ptr = shader.second.c_str();
            glShaderSource(suid, 1, &ptr, nullptr);

            glCompileShader(suid);

            GLint param;
            glGetShaderiv(suid, GL_COMPILE_STATUS, &param);

            if (param == GL_TRUE)
            {
                glAttachShader(m_uid, suid);
            }
            else
            {
                glGetShaderiv(suid, GL_INFO_LOG_LENGTH, &param);

                char log[param];
                glGetShaderInfoLog(suid, param, &param, log);
                PARALLAX_TRACE("%s shader compile error: %s", GL::GetGLShaderTypename(shader.first.glType), log);

                glDeleteShader(suid);
            }
        }
    }

    void GLProgram::link(const std::string& fragName, ProgramLocationID fragLocation)
    {
        link({{fragName, fragLocation}}, {});
    }

    void GLProgram::link(LocationMap fragLocations, LocationMap attribLocations)
    {
        for (auto& loc : fragLocations)
            glBindFragDataLocation(m_uid, loc.second.glLoc, loc.first.c_str());
        for (auto& loc : attribLocations)
            glBindAttribLocation(m_uid, loc.second.glLoc, loc.first.c_str());

        glLinkProgram(m_uid);

        glGetProgramiv(m_uid, GL_LINK_STATUS, &m_complete);

        if (m_complete != GL_TRUE)
        {
            GLint param;
            glGetProgramiv(m_uid, GL_INFO_LOG_LENGTH, &param);

            char log[param];
            glGetProgramInfoLog(m_uid, param, &param, log);
            PARALLAX_TRACE("Program link error: %s", log);
        }
    }

    void GLProgram::bind()
    {
        glUseProgram(m_uid);
    }

    void GLProgram::unbind()
    {
        glUseProgram(0);
    }

    ProgramLocationID GLProgram::getUniformLocation(const std::string& name)
    {
        if (m_uniformLocations.count(name))
            return m_uniformLocations[name];

        GLint glloc = glGetUniformLocation(m_uid, name.c_str());
        ProgramLocationID loc;
        loc.glLoc = glloc;
        m_uniformLocations[name] = std::move(loc);
        return m_uniformLocations[name];
    }

    ProgramLocationID GLProgram::getAttributeLocation(const std::string& name)
    {
        if (m_attributesLocations.count(name))
            return m_attributesLocations[name];

        GLint glloc = glGetAttribLocation(m_uid, name.c_str());
        ProgramLocationID loc;
        loc.glLoc = glloc;
        m_uniformLocations[name] = std::move(loc);
        return m_uniformLocations[name];
    }

    void GLProgram::setUniform(ProgramLocationID loc, I32 val)
    {
        glUniform1f(loc.glLoc, val);
    }

    void GLProgram::setUniform(ProgramLocationID loc, float val)
    {
        glUniform1f(loc.glLoc, val);
    }

    void GLProgram::setUniform(ProgramLocationID loc, float* val, I32 count)
    {
        glUniform1fv(loc.glLoc, count, val);
    }

    void setUniform(ProgramLocationID loc, glm::vec2 val)
    {
        glUniform2fv(loc.glLoc, 1, &val.x);
    }

    void setUniform(ProgramLocationID loc, glm::vec3 val)
    {
        glUniform3fv(loc.glLoc, 1, &val.x);
    }

    void setUniform(ProgramLocationID loc, glm::vec4 val)
    {
        glUniform4fv(loc.glLoc, 1, &val.x);
    }

    void setUniform(ProgramLocationID loc, glm::mat4 val)
    {
        glUniformMatrix4fv(loc.glLoc, 1, GL_FALSE, &val[0][0]);
    }
}

#endif
