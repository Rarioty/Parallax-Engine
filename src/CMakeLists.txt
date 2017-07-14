# Make all sub-projects
add_subdirectory(PIL)
add_subdirectory(Core)

set (ROOT_SRCS
    Parallax.cpp
    Debug.cpp
    Strings.cpp
)

add_library(ParallaxEngine SHARED ${ROOT_SRCS})
set_property(TARGET ParallaxEngine PROPERTY CXX_STANDARD 17)
target_link_libraries(ParallaxEngine PIL)
target_link_libraries(ParallaxEngine Core)
target_link_libraries(ParallaxEngine ${OPENGL_LIBRARIES})
target_link_libraries(ParallaxEngine ${Vulkan_LIBRARIES})
