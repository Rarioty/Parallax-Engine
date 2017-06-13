include_directories(${ParallaxEngine_HEADER_DIR})

# Make all sub-projects
add_subdirectory(PIL)

add_library(ParallaxEngine SHARED empty.cpp)
target_link_libraries(ParallaxEngine PIL)
