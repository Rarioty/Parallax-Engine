#include <Parallax/Window.hpp>
#include <Parallax/Platform.hpp>

#if PARALLAX_PLATFORM_WINDOWS

#include <Parallax/Debug.hpp>
#include <Windows.h>
#include <windowsx.h>
#include <iostream>

namespace Parallax
{
	static HWND	s_hwnd;
	static bool m_running;

	LRESULT CALLBACK wndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void adjust(U32 width, U32 height, bool windowFrame)
	{
		ShowWindow(s_hwnd, SW_SHOWNORMAL);
	}

	void clear()
	{
		RECT rect;
		GetWindowRect(s_hwnd, &rect);
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
		HDC hdc = GetDC(s_hwnd);

		SelectObject(hdc, brush);
		FillRect(hdc, &rect, brush);
	}

	bool createWindow(const char* name, U32 width, U32 height, U32 flags)
	{
		HINSTANCE instance = (HINSTANCE)GetModuleHandle(NULL);

		WNDCLASSEXA wnd;
		memset(&wnd, 0, sizeof(wnd));
		wnd.cbSize = sizeof(wnd);
		wnd.style = CS_HREDRAW | CS_VREDRAW;
		wnd.lpfnWndProc = wndProc;
		wnd.hInstance = instance;
		wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
		wnd.lpszClassName = "parallax";
		wnd.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		RegisterClassExA(&wnd);

		DWORD error = GetLastError();
		PARALLAX_FATAL(0 == error, "RegisterClassExA failed, error code: %d\n", error);

		s_hwnd = CreateWindowA("parallax"
			, name
			, WS_OVERLAPPEDWINDOW | WS_VISIBLE
			, 0
			, 0
			, CW_USEDEFAULT
			, CW_USEDEFAULT
			, NULL
			, NULL
			, instance
			, 0
		);

		PARALLAX_FATAL(NULL != s_hwnd, "HWND is %p, error code: %lu\n", s_hwnd, GetLastError());

		PlatformData data;
		memset(&data, 0, sizeof(PlatformData));

		data.nwh = s_hwnd;
		setPlatformData(data);

		adjust(width, height, true);
		clear();

		m_running = true;

		return true;
	}

	bool isRunning()
	{
		return m_running;
	}

	void processEvents()
	{
		MSG msg;
		while (0 != PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void destroyWindow()
	{
		DestroyWindow(s_hwnd);
	}

	LRESULT CALLBACK wndProc(
		HWND hwnd,        // handle to window
		UINT uMsg,        // message identifier
		WPARAM wParam,    // first message parameter
		LPARAM lParam)    // second message parameter
	{
		switch (uMsg)
		{
		case WM_CREATE:
			return 0;

		case WM_PAINT:
			return 0;

		case WM_SIZE:
			return 0;

		case WM_DESTROY:
			m_running = false;
			return 0;

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
		return 0;
	}
}

#endif