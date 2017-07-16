#include <Parallax/Parallax.hpp>

#include <Parallax/Window.hpp>
#include <Parallax/Renderers/RendererGL.hpp>

std::string getParallaxVersion()
{
    return std::string(PARALLAX_API_VERSION) + std::string(".") + std::string(PARALLAX_MAKE_DATE) + std::string(PARALLAX_MAKE_HOUR);
}

namespace Parallax
{
	static Renderer::RendererGL m_renderer;

	bool init(const char* name)
	{
		createWindow(name, 1024, 768);

		return m_renderer.init();
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