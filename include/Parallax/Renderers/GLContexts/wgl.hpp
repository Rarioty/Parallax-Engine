#ifndef PARALLAX_GL_CONTEXT_WGL_HPP_GUARD
#define PARALLAX_GL_CONTEXT_WGL_HPP_GUARD

#if PARALLAX_USE_WGL

#include <wgl/wglext.h>

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

			U64     getCaps() const;

			bool    isValid() const;

		private:
			I32						m_contextAttrs[9];
			I32						m_pixelFormat;
			PIXELFORMATDESCRIPTOR	m_pfd;
			HGLRC					m_context;
			HDC						m_hdc;
		};
	}
}

#endif

#endif