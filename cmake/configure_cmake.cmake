set (
    CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${ParallaxEngine_BUILD_DIR}
)

set (
    CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ${ParallaxEngine_BUILD_DIR}
)

if (CMAKE_COMPILER_IS_GNUCXX)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
endif (CMAKE_COMPILER_IS_GNUCXX)
