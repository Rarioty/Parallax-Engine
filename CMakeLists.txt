cmake_minimum_required (VERSION 2.6)
project (ParallaxEngine)

include (cmake/find_packages.cmake)
include (cmake/options.cmake)
include (cmake/variables.cmake)
include (cmake/include_externals.cmake)
include (cmake/configure.cmake)
include (cmake/configure_cmake.cmake)

add_subdirectory(src)
if (BUILD_TESTS)
    add_subdirectory(tests)
endif (BUILD_TESTS)
