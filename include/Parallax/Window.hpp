#ifndef PARALLAX_IWINDOW_HPP_GUARD
#define PARALLAX_IWINDOW_HPP_GUARD

#include <Parallax/Types.hpp>

namespace Parallax
{
	bool createWindow(const char* name, U32 width, U32 height, U32 flags = 0);
	bool isRunning();
	void processEvents();
	void destroyWindow();
}

#endif