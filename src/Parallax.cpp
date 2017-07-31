#include <Parallax/Parallax.hpp>

#include <Parallax/Threads/ThreadManager.hpp>
#include <Parallax/Renderers/Renderer.hpp>
#include <Parallax/Threads/ThreadPool.hpp>
#include <Parallax/Renderers/Defines.hpp>
#include <Parallax/Physics/Physics.hpp>
#include <Parallax/Debug/Debug.hpp>
#include <Parallax/Settings.hpp>
#include <Parallax/Window.hpp>
#include <Parallax/Types.hpp>

std::string getParallaxVersion()
{
    return std::string(PARALLAX_API_VERSION) + std::string(".") + std::string(PARALLAX_MAKE_DATE) + std::string(PARALLAX_MAKE_HOUR);
}

namespace Parallax
{
    static Threads::ThreadManager*  s_threadManager = nullptr;
    static Threads::ThreadPool*     s_threadPool = nullptr;

	bool init(const char* name)
	{
        U32 width, height, flags, version;
        bool fullscreen, result;
        std::string physicsEngine;
        std::string renderer;

		if (!Debug::Init())
			return false;

        Settings::loadSettings();

        s_threadManager = new Threads::ThreadManager();
        s_threadPool = new Threads::ThreadPool(4, *s_threadManager);
        s_threadPool->start();

        version = Settings::getAsCritical<U32>("version");
        width = Settings::getAsCritical<U32>("Graphics:width");
        height = Settings::getAsCritical<U32>("Graphics:height");
        fullscreen = Settings::getAsCritical<bool>("Graphics:fullscreen");
        renderer = Settings::getAsCritical<std::string>("Graphics:renderer");
        physicsEngine = Settings::getAsCritical<std::string>("Physics:engine");

        PARALLAX_TRACE("Version of settings file: %d", version);
        PARALLAX_TRACE("Creating window with resolution %dx%d%s", width, height, (fullscreen ? " with fullscreen" : ""));

        flags = 0;

        if (fullscreen)
            flags |= PARALLAX_GRAPHICS_FULLSCREEN;

        // Create window
        result = createWindow(name, width, height, flags);
        PARALLAX_FATAL(true == result, "Cannot create window !");

        // Initialize subsystems
        result = Renderer::Init(renderer, width, height);
        PARALLAX_FATAL(true == result, "Renderer could not have been initialized !");

        result = Physics::Init(physicsEngine);
        PARALLAX_FATAL(true == result, "Physics engine could not have been initialized !");

		return result;
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
        Renderer::Shutdown();
		destroyWindow();

        delete s_threadPool;
        delete s_threadManager;
	}
}
