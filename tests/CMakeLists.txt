# Add all projects tests
include_directories(${ParallaxEngine_HEADER_DIR})
include_directories(".")

# Generate libtest
add_library(tests SHARED tests.cpp)

add_subdirectory(PIL)
