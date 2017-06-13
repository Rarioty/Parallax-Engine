# PIL project

set (PIL_SRCS
        FileSystem/File.cpp
)

add_library (PIL SHARED ${PIL_SRCS})
add_coverage (PIL)
