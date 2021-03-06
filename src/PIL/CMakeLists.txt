# PIL project

set (PIL_SRCS
	Debug.cpp
	Strings.cpp
	Platform.cpp

    Threads/Task.cpp
    Threads/Worker.cpp
    Threads/ThreadManager.cpp
    Threads/ThreadPool.cpp

    FS/fs.cpp
    FS/URL.cpp
    FS/File.cpp
    FS/Path.cpp
    FS/IFileSystem.cpp

    FS/POSIX/LocalFileSystem.cpp
    FS/POSIX/LocalFileHandler.cpp

	Renderers/IRenderer.cpp
    Renderers/RendererGL.cpp
    Renderers/RendererVulkan.cpp
    Renderers/GLContexts/glx.cpp
    Renderers/GLContexts/wgl.cpp

	Window/Windows.cpp
	Window/X11.cpp

	Physics/Physics.cpp
)

add_library (PIL STATIC ${PIL_SRCS} ${PARALLAX_HEADERS})
target_link_libraries(PIL ${OPENSSL_LIBRARIES} ${OPENSSL_SSL_LIBRARY} ${OPENSSL_CRYPTO_LIBRARY} ${Vulkan_LIBRARIES} ${OPENGL_LIBRARIES})
add_coverage (PIL)
