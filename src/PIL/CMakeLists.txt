# PIL project

set (PIL_SRCS
    Threads/Task.cpp
    Threads/Worker.cpp
    Threads/ThreadManager.cpp
    Threads/ThreadPool.cpp
)

add_library (PIL SHARED ${PIL_SRCS})
add_coverage (PIL)
