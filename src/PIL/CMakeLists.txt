# PIL project

set (PIL_SRCS
    Threads/Task.cpp
    Threads/Worker.cpp
    Threads/ThreadManager.cpp
    Threads/ThreadPool.cpp

    fs/fs.cpp
    fs/URL.cpp
    fs/File.cpp
    fs/Path.cpp

    fs/POSIX/LocalFileSystem.cpp
    fs/POSIX/LocalFileHandler.cpp

    Renderers/RendererGL.cpp
    Renderers/RendererVulkan.cpp
    Renderers/GLContexts/glx.cpp
)

add_library (PIL SHARED ${PIL_SRCS})
target_link_libraries(PIL ${OPENSSL_LIBRARIES})
add_coverage (PIL)
