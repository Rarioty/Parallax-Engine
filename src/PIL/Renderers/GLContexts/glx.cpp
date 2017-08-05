#include <Parallax/Renderers/RendererGL.hpp>
#include <Parallax/Platform.hpp>

#if PARALLAX_PLATFORM_LINUX && PARALLAX_GRAPHICS_OPENGL_ALLOWED

#include <Parallax/Renderers/Defines.hpp>
#include <Parallax/Debug/Debug.hpp>
#include <iostream>

#if PARALLAX_USE_GLX
    #define GLX_GLXEXT_PROTOTYPES
    #include <glx/glxext.h>

namespace Parallax::Renderer
{
    typedef int     (*PFNGLXSWAPINTERVALMESAPROC)(U32 interval);

    PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB;
	PFNGLXSWAPINTERVALEXTPROC         glXSwapIntervalEXT;
	PFNGLXSWAPINTERVALMESAPROC        glXSwapIntervalMESA;
	PFNGLXSWAPINTERVALSGIPROC         glXSwapIntervalSGI;

    GLContext::GLContext()
        : m_context(0)
        , m_visualInfo(nullptr)
    {}

    void GLContext::create(U32 width, U32 height)
    {
        m_context = (GLXContext)g_platformData.context;

        PARALLAX_TRACE("Creating GL context...");

        if (NULL == g_platformData.context)
        {
            PARALLAX_FATAL(NULL != g_platformData.ndt, "No window has been created !");
            XLockDisplay((::Display*)g_platformData.ndt);

            int major, minor;
            bool version = glXQueryVersion((::Display*)g_platformData.ndt, &major, &minor);

            PARALLAX_FATAL(true == version, "Failed to query GLX version !");
            PARALLAX_FATAL(major > 1 || (major == 1 && minor >= 2), "GLX version it not >=1.2 (%d.%d)", major, minor);

            PARALLAX_TRACE("GLX version: %d.%d", major, minor);

            U32 screen = DefaultScreen((::Display*)g_platformData.ndt);

            const char* extensions = glXQueryExtensionsString((::Display*)g_platformData.ndt, screen);
            PARALLAX_TRACE("GLX extensions: %s", extensions);

            const int attrsGlx[] =
            {
                GLX_RENDER_TYPE,    GLX_RGBA_BIT,
                GLX_DRAWABLE_TYPE,  GLX_WINDOW_BIT,
                GLX_DOUBLEBUFFER,   true,
                GLX_RED_SIZE,       8,
                GLX_BLUE_SIZE,      8,
                GLX_GREEN_SIZE,     8,
                GLX_DEPTH_SIZE,     24,
                GLX_STENCIL_SIZE,   8,
                0
            };

            GLXFBConfig bestConfig = NULL;

            int numConfigs;
            GLXFBConfig* configs = glXChooseFBConfig((::Display*)g_platformData.ndt, screen, attrsGlx, &numConfigs);

            PARALLAX_TRACE("GLX number of configurations: %d", numConfigs);
            for (int i = 0; i < numConfigs; ++i)
            {
                m_visualInfo = glXGetVisualFromFBConfig((::Display*)g_platformData.ndt, configs[i]);
                if (NULL != m_visualInfo)
                {
                    PARALLAX_TRACE("---");
                    bool valid = true;
                    for (U32 attr = 6; attr < 16 && attrsGlx[attr] != None; attr += 2)
                    {
                        int value;
                        glXGetFBConfigAttrib((::Display*)g_platformData.ndt, configs[i], attrsGlx[attr], &value);
                        PARALLAX_TRACE("GLX %02d/%02d %02d: %02d, %02d (%02d)%s",
                            i, numConfigs, (attr/2), attrsGlx[attr],
                            value, attrsGlx[attr+1], (value < attrsGlx[attr+1] ? " *" : "")
                        );

                        if (value < attrsGlx[attr + 1])
                        {
                            valid = false;
                            break;
                        }
                    }

                    if (valid)
                    {
                        bestConfig = configs[i];
                        PARALLAX_TRACE("Best configuration: %02d", i);
                        break;
                    }
                }

                XFree(m_visualInfo);
                m_visualInfo = NULL;
            }

            XFree(configs);
            PARALLAX_FATAL(NULL != m_visualInfo, "Failed to find a suitable X11 display configuration !");

            PARALLAX_TRACE("Create GL 2.1 context...");
            m_context = glXCreateContext((::Display*)g_platformData.ndt, m_visualInfo, 0, GL_TRUE);

            PARALLAX_FATAL(NULL != m_context, "Failed to create GL 2.1 context !");

            XUnlockDisplay((::Display*)g_platformData.ndt);
        }

        glXMakeCurrent((::Display*)g_platformData.ndt, (::Window)g_platformData.nwh, m_context);

        glXSwapIntervalEXT = (PFNGLXSWAPINTERVALEXTPROC)glXGetProcAddress((const GLubyte*)"glXSwapIntervalEXT");
        if (NULL != glXSwapIntervalEXT)
        {
            PARALLAX_TRACE("Using glXSwapIntervalEXT");
            glXSwapIntervalEXT((::Display*)g_platformData.ndt, (::Window)g_platformData.nwh, 0);
        }
        else
        {
            glXSwapIntervalMESA = (PFNGLXSWAPINTERVALMESAPROC)glXGetProcAddress((const GLubyte*)"glXSwapIntervalMESA");
            if (NULL != glXSwapIntervalMESA)
            {
                PARALLAX_TRACE("Using glXSwapIntervalMESA");
                glXSwapIntervalMESA(0);
            }
            else
            {
                glXSwapIntervalSGI = (PFNGLXSWAPINTERVALSGIPROC)glXGetProcAddress((const GLubyte*)"glXSwapIntervalSGI");
                if (NULL != glXSwapIntervalSGI)
                {
                    PARALLAX_TRACE("Using glXSwapIntervalSGI");
                    glXSwapIntervalSGI(0);
                }
            }
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glXSwapBuffers((::Display*)g_platformData.ndt, (::Window)g_platformData.nwh);
    }

    void GLContext::resize(U32 width, U32 height, U32 flags)
    {
        bool vsync = !!(flags & PARALLAX_GRAPHICS_RESET_VSYNC);
        U32 interval = vsync ? 1 : 0;

        if (NULL != glXSwapIntervalEXT)
        {
            glXSwapIntervalEXT((::Display*)g_platformData.ndt, (::Window)g_platformData.nwh, interval);
        }
        else if (NULL != glXSwapIntervalMESA)
        {
            glXSwapIntervalMESA(interval);
        }
        else if (NULL != glXSwapIntervalSGI)
        {
            glXSwapIntervalSGI(interval);
        }
    }

    void GLContext::destroy()
    {
        glXMakeCurrent((::Display*)g_platformData.ndt, 0, 0);
        if (NULL == g_platformData.context)
        {
            glXDestroyContext((::Display*)g_platformData.ndt, m_context);
            XFree(m_visualInfo);
        }
        m_visualInfo = NULL;
    }

    U64 GLContext::getCaps() const
    {
        return 0;
    }

    bool GLContext::isValid() const
    {
        return 0 != m_context;
    }
}

#endif

#endif
