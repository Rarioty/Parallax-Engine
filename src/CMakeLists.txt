# Make all sub-projects
add_subdirectory(PIL)
add_subdirectory(Core)

set (ROOT_SRCS
    Parallax.cpp
)

add_library(ParallaxEngine STATIC ${ROOT_SRCS})
target_link_libraries(ParallaxEngine PIL)
target_link_libraries(ParallaxEngine Core)
target_link_libraries(ParallaxEngine ${OPENGL_LIBRARIES})
target_link_libraries(ParallaxEngine ${Vulkan_LIBRARIES})
