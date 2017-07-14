#include <Parallax/Renderers/RendererGL.hpp>
#include <Parallax/Platform.hpp>

#if PARALLAX_PLATFORM_LINUX && PARALLAX_CONFIG_RENDERER_OPENGL

#include <Parallax/Renderers/Defines.hpp>
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
    {

    }

    void GLContext::create(U32 width, U32 height)
    {
        m_context = (GLXContext)g_platformData.context;

        if (NULL == g_platformData.context)
        {
            XLockDisplay((::Display*)g_platformData.ndt);

            int major, minor;
            bool version = glXQueryVersion((::Display*)g_platformData.ndt, &major, &minor);

            if (!version)
            {
                std::cerr << "Failed to query GLX version" << std::endl;
                exit(1);
            }

            if (!((major == 1 && minor >= 2) || major > 1))
            {
                std::cerr << "GLX version is not >=1.2 (" << major << "." << minor << ")" << std::endl;
                exit(1);
            }

            U32 screen = DefaultScreen((::Display*)g_platformData.ndt);

            const char* extensions = glXQueryExtensionsString((::Display*)g_platformData.ndt, screen);
            std::cout << "GLX extensions: " << extensions << std::endl;

            const int attrsGlx[] =
            {
                GLX_RENDER_TYPE, GLX_RGBA_BIT,
                GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
                GLX_DOUBLEBUFFER, true,
                GLX_RED_SIZE, 8,
                GLX_BLUE_SIZE, 8,
                GLX_GREEN_SIZE, 8,
                GLX_DEPTH_SIZE, 24,
                GLX_STENCIL_SIZE, 8,
                0
            };

            GLXFBConfig bestConfig = NULL;

            int numConfigs;
            GLXFBConfig* configs = glXChooseFBConfig((::Display*)g_platformData.ndt, screen, attrsGlx, &numConfigs);

            std::cout << "glX num configs " << numConfigs << std::endl;
            for (int i = 0; i < numConfigs; ++i)
            {
                m_visualInfo = glXGetVisualFromFBConfig((::Display*)g_platformData.ndt, configs[i]);
                if (NULL != m_visualInfo)
                {
                    std::cout << "---" << std::endl;
                    bool valid = true;
                    for (U32 attr = 6; attr < 16 && attrsGlx[attr] != None; attr += 2)
                    {
                        int value;
                        glXGetFBConfigAttrib((::Display*)g_platformData.ndt, configs[i], attrsGlx[attr], &value);
                        std::cout << "glX " << i << "/" << numConfigs << " " << attr/2 << ": "
                            << attrsGlx[attr] << ", " << value << " (" << attrsGlx[attr+1]
                            << (value < attrsGlx[attr+1] ? " *" : "") << ")" <<  std::endl;

                        if (value < attrsGlx[attr + 1])
                        {
                            valid = false;
                            break;
                        }
                    }

                    if (valid)
                    {
                        bestConfig = configs[i];
                        std::cout << "Best config " << i << std::endl;
                        break;
                    }
                }

                XFree(m_visualInfo);
                m_visualInfo = NULL;
            }

            XFree(configs);
            if (!m_visualInfo)
            {
                std::cerr << "Failed to find a suitable X11 display configuration !" << std::endl;
                exit(1);
            }

            std::cout << "Create GL 2.1 context." << std::endl;
            m_context = glXCreateContext((::Display*)g_platformData.ndt, m_visualInfo, 0, GL_TRUE);

            if (m_context == NULL)
            {
                std::cerr << "Failed to create GL 2.1 context." << std::endl;
                exit(1);
            }

            XUnlockDisplay((::Display*)g_platformData.ndt);
        }

        glXMakeCurrent((::Display*)g_platformData.ndt, (::Window)g_platformData.nwh, m_context);

        glXSwapIntervalEXT = (PFNGLXSWAPINTERVALEXTPROC)glXGetProcAddress((const GLubyte*)"glXSwapIntervalEXT");
        if (NULL != glXSwapIntervalEXT)
        {
            std::cout << "Using glXSwapIntervalEXT." << std::endl;
            glXSwapIntervalEXT((::Display*)g_platformData.ndt, (::Window)g_platformData.nwh, 0);
        }
        else
        {
            glXSwapIntervalMESA = (PFNGLXSWAPINTERVALMESAPROC)glXGetProcAddress((const GLubyte*)"glXSwapIntervalMESA");
            if (NULL != glXSwapIntervalMESA)
            {
                std::cout << "Using glXSwapIntervalMESA." << std::endl;
                glXSwapIntervalMESA(0);
            }
            else
            {
                glXSwapIntervalSGI = (PFNGLXSWAPINTERVALSGIPROC)glXGetProcAddress((const GLubyte*)"glXSwapIntervalSGI");
                if (NULL != glXSwapIntervalSGI)
                {
                    std::cout << "Using glxSwapIntervalSGI." << std::endl;
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
        bool vsync = !!(flags & PARALLAX_RESET_VSYNC);
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
