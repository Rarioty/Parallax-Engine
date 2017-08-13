#include <Parallax/Window.hpp>
#include <Parallax/Platform.hpp>

#if PARALLAX_PLATFORM_LINUX

#include <Parallax/Renderers/RendererGL.hpp>
#include <Parallax/Video/Video.hpp>
#include <Parallax/Debug/Debug.hpp>
#include <Parallax/Types.hpp>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <string.h>
#include <stdio.h>

namespace Parallax
{
	static Display* 				m_display;
	static Window 					m_window;
	static Window 					m_root;
	static I32 						m_depth;
	static Visual*					m_visual;
	static XSetWindowAttributes		m_windowAttrs;
	static bool 					m_running;

	static Atom 					m_wmDeleteWindow;
	static XIM						m_im;
	static XIC 						m_ic;

	static char	 			s_applicationName[255] = {0};
	static const char* 		s_applicationClass = "parallax";

	bool createWindow(const char* name, U32 width, U32 height, U32 flags)
	{
		sprintf(s_applicationName, "%s", name);

		XInitThreads();
		m_display = XOpenDisplay(0);

		I32 screen = DefaultScreen(m_display);
		m_depth = DefaultDepth(m_display, screen);
		m_visual = DefaultVisual(m_display, screen);
		m_root = RootWindow(m_display, screen);

		memset(&m_windowAttrs, 0, sizeof(m_windowAttrs));
		m_windowAttrs.background_pixmap = 0;
		m_windowAttrs.border_pixel = 0;
		m_windowAttrs.event_mask = 0
			| ButtonPressMask
			| ButtonReleaseMask
			| ExposureMask
			| KeyPressMask
			| KeyReleaseMask
			| PointerMotionMask
			| StructureNotifyMask
			;

		m_window = XCreateWindow(m_display
			, m_root
			, 0, 0
			, width, height, 0
			, m_depth
			, InputOutput
			, m_visual
			, CWBorderPixel | CWEventMask
			, &m_windowAttrs
		);

		XSetWindowAttributes attr;
		memset(&attr, 0, sizeof(attr));
		XChangeWindowAttributes(m_display, m_window, CWBackPixel, &attr);

		const char* wmDeleteWindowName = "WM_DELETE_WINDOW";
		XInternAtoms(m_display, (char**)&wmDeleteWindowName, 1, False, &m_wmDeleteWindow);
		XSetWMProtocols(m_display, m_window, &m_wmDeleteWindow, 1);

		XMapWindow(m_display, m_window);
		XStoreName(m_display, m_window, s_applicationName);

		XClassHint* hint = XAllocClassHint();
		hint->res_name = (char*)s_applicationName;
		hint->res_class = (char*)s_applicationClass;
		XSetClassHint(m_display, m_window, hint);
		XFree(hint);

		m_im = XOpenIM(m_display, NULL, NULL, NULL);

		m_ic = XCreateIC(m_im
			, XNInputStyle
			, 0
			| XIMPreeditNothing
			| XIMStatusNothing
			, XNClientWindow
			, m_window
			, NULL
		);

		PlatformData data;
		memset(&data, 0, sizeof(PlatformData));
		data.ndt = m_display;
		data.nwh = (void*)(uintptr_t)m_window;
		data.context = NULL;
		setPlatformData(data);

		m_running = true;

		return true;
	}

	bool isRunning()
	{
		return m_running;
	}

	void processEvents()
	{
		XEvent event;

		while (XCheckWindowEvent(m_display, m_window, m_windowAttrs.event_mask, &event))
		{
			switch(event.type)
			{
			case ClientMessage:
				if ((Atom)event.xclient.data.l[0] == m_wmDeleteWindow)
				{
					m_running = false;
				}
				break;
			case ConfigureNotify:
				Renderer::WindowResized(event.xconfigure.width, event.xconfigure.height);
				Video::WindowResized(event.xconfigure.width, event.xconfigure.height);
				break;
			case KeyPress:
				if (event.xkey.keycode == 0x09)
				{
					m_running = false;
				}
				break;
			}
		}
	}

	void destroyWindow()
	{
		XDestroyIC(m_ic);
		XCloseIM(m_im);

		XUnmapWindow(m_display, m_window);
		XDestroyWindow(m_display, m_window);
	}
}

#endif
