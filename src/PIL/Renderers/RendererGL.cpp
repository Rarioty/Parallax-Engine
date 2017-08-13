#include <Parallax/Renderers/RendererGL.hpp>

#include <Parallax/Platform.hpp>

#if PARALLAX_GRAPHICS_OPENGL_ALLOWED

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Parallax/Debug/Debug.hpp>
#include <iostream>
#include <map>

namespace Parallax::Renderer::GL
{
    static const char* s_vendor;
    static const char* s_renderer;
    static const char* s_version;
    static const char* s_glslVersion;

    static GLContext   s_glctx;

    static const std::map<GLenum,int> glTypeSizeLookup = {
		{GL_BYTE, sizeof(GLbyte)},
		{GL_UNSIGNED_BYTE, sizeof(GLubyte)},
		{GL_SHORT, sizeof(GLshort)},
		{GL_UNSIGNED_SHORT, sizeof(GLushort)},
		{GL_INT, sizeof(GLint)},
		{GL_UNSIGNED_INT, sizeof(GLuint)},
		{GL_HALF_FLOAT, sizeof(GLhalf)},
		{GL_FLOAT, sizeof(GLfloat)},
		{GL_DOUBLE, sizeof(GLdouble)}};

    static const std::map<GLenum,const char*> glShaderTypenameLookup = {
		{GL_VERTEX_SHADER, "Vertex"},
		{GL_GEOMETRY_SHADER, "Geometry"},
		{GL_FRAGMENT_SHADER, "Fragment"}
	};

    static const char* getGLString(GLenum _name)
    {
        const char* str = (const char*)glGetString(_name);
        glGetError();
        if (NULL != str)
        {
            return str;
        }

        return "<unknown>";
    }

    static void setRenderContextSize(U32 width, U32 height, U32 flags = 0)
    {
        if (width != 0 && height != 0)
        {
            if (!s_glctx.isValid())
            {
                s_glctx.create(width, height);
            }
            else
            {
                s_glctx.resize(width, height, flags);
            }
        }
    }

    bool Init(U32 width, U32 height)
    {
        I32 result;

        setRenderContextSize(width, height);

        s_vendor        = getGLString(GL_VENDOR);
        s_renderer      = getGLString(GL_RENDERER);
        s_version       = getGLString(GL_VERSION);
        s_glslVersion   = getGLString(GL_SHADING_LANGUAGE_VERSION);

        PARALLAX_TRACE("      Vendor: %s", s_vendor);
        PARALLAX_TRACE("    Renderer: %s", s_renderer);
        PARALLAX_TRACE("     Version: %s", s_version);
        PARALLAX_TRACE("GLSL version: %s", s_glslVersion);

        glewExperimental = GL_TRUE;
        result = glewInit();

        PARALLAX_CHECK(0 == result, "Checking result of glew init (%d)...", result);

        PARALLAX_TRACE("Renderer initialized");

        return true;
    }

	void Shutdown()
	{

	}

    RendererType GetRendererType()
    {
        return RendererType::OpenGL;
    }

    const char* GetRendererName()
    {
        return PARALLAX_GRAPHICS_OPENGL_NAME;
    }

    bool IsDeviceRemoved()
    {
        return false;
    }

    void WindowResized(U32 width, U32 height)
    {
        glViewport(0, 0, width, height);
    }

    void SwapBuffers()
    {
        if (s_glctx.isValid())
            s_glctx.swapBuffers();
    }

    size_t GetGLTypeSize(GLenum type)
    {
        return glTypeSizeLookup.at(type);
    }

    const char* GetGLShaderTypename(GLenum type)
    {
        return glShaderTypenameLookup.at(type);
    }
}

#endif
