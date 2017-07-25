#include <Parallax/Parallax.hpp>

#include <Parallax/Debug/Debug.hpp>
#include <Parallax/Window.hpp>
#include <Parallax/Renderers/RendererVulkan.hpp>

std::string getParallaxVersion()
{
    return std::string(PARALLAX_API_VERSION) + std::string(".") + std::string(PARALLAX_MAKE_DATE) + std::string(PARALLAX_MAKE_HOUR);
}

namespace Parallax
{
	bool init(const char* name)
	{
		if (!Debug::Init())
			return false;

		createWindow(name, 1024, 768);

		return true;
	}

	void launch()
	{
		while (isRunning())
		{
			processEvents();
		}
	}

	void shutdown()
	{
		destroyWindow();
	}
}
