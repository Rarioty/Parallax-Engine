#ifndef PARALLAX_GL_CONTEXT_GLX_HPP_GUARD
#define PARALLAX_GL_CONTEXT_GLX_HPP_GUARD

#if PARALLAX_USE_GLX

#include <X11/Xlib.h>
#include <GL/glew.h>
#include <GL/glx.h>

#include <Parallax/Types.hpp>

namespace Parallax
{
    namespace Renderer
    {
        class GLContext
        {
        public:
            GLContext();

            void    create(U32 width, U32 height);
            void    destroy();
            void    resize(U32 width, U32 height, U32 flags);

            void    swapBuffers() const;

            U64     getCaps() const;

            bool    isValid() const;

        private:
            GLXContext      m_context;
            XVisualInfo*    m_visualInfo;
        };
    }
}

#endif

#endif
