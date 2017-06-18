include_directories(${ParallaxEngine_HEADER_DIR})

# Make all sub-projects
add_subdirectory(PIL)
add_subdirectory(Core)

add_library(ParallaxEngine SHARED Parallax.cpp)
target_link_libraries(ParallaxEngine PIL)
target_link_libraries(ParallaxEngine Core)
