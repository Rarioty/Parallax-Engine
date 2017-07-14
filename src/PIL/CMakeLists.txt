# PIL project

set (PIL_SRCS
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

    Renderers/RendererGL.cpp
    Renderers/RendererVulkan.cpp
    Renderers/GLContexts/glx.cpp
)

add_library (PIL SHARED ${PIL_SRCS})
target_link_libraries(PIL ${OPENSSL_LIBRARIES})
add_coverage (PIL)
