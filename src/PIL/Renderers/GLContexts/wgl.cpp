#include <Parallax/Renderers/RendererGL.hpp>
#include <Parallax/Platform.hpp>

#if PARALLAX_PLATFORM_WINDOWS && PARALLAX_CONFIG_RENDERER_OPENGL

#include <Parallax/Debug.hpp>
#include <iostream>

namespace Parallax::Renderer
{
	static HGLRC createContext(HDC hdc)
	{
		PIXELFORMATDESCRIPTOR pfd;

		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cAlphaBits = 8;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;
		pfd.iLayerType = PFD_MAIN_PLANE;

		int pixelFormat = ChoosePixelFormat(hdc, &pfd);
		PARALLAX_FATAL(0 != pixelFormat, "ChoosePixelFormat failed !");

		DescribePixelFormat(hdc, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

		PARALLAX_TRACE("Pixel format:\n"
			"\tiPixelType %d\n"
			"\tcColorBits %d\n"
			"\tcAlphaBits %d\n"
			"\tcDepthBits %d\n"
			"\tcStencilBits %d\n"
			, pfd.iPixelType
			, pfd.cColorBits
			, pfd.cAlphaBits
			, pfd.cDepthBits
			, pfd.cStencilBits
		);

		int result;
		result = SetPixelFormat(hdc, pixelFormat, &pfd);
		PARALLAX_FATAL(0 != result, "SetPixelFormat failed !");

		HGLRC context = wglCreateContext(hdc);
		PARALLAX_FATAL(NULL != context, "wglCreateContext failed !");

		result = wglMakeCurrent(hdc, context);
		PARALLAX_FATAL(0 != result, "wglMakeCurrent failed !");

		return context;
	}

	GLContext::GLContext()
		: m_context(nullptr)
		, m_hdc(nullptr)
	{}

	void GLContext::create(U32 width, U32 height)
	{
		PARALLAX_WARN(nullptr != g_platformData.nwh
			, "setPlatform with valid window is not called. This might "
			"be intentional when GL context is created by the user.");

		if (nullptr != g_platformData.nwh)
		{
			m_hdc = GetDC((HWND)g_platformData.nwh);
			PARALLAX_FATAL(nullptr != m_hdc, "GetDC failed !");

			HWND hwnd = CreateWindowA("STATIC"
				, ""
				, WS_POPUP | WS_DISABLED
				, -32000
				, -32000
				, 0
				, 0
				, nullptr
				, nullptr
				, GetModuleHandle(nullptr)
				, 0
			);

			HDC hdc = GetDC(hwnd);
			PARALLAX_FATAL(nullptr != hdc, "GetDC failed !");

			HGLRC context = createContext(hdc);

			
		}
	}

	void GLContext::destroy()
	{
		if (nullptr != g_platformData.nwh)
		{
			wglMakeCurrent(nullptr, nullptr);

			wglDeleteContext(m_context);
			m_context = nullptr;

			ReleaseDC((HWND)g_platformData.nwh, m_hdc);
			m_hdc = nullptr;
		}
	}

	void GLContext::resize(U32 width, U32 height, U32 flags)
	{
		
	}

	bool GLContext::isValid() const
	{
		return nullptr != m_context;
	}
}

#endif