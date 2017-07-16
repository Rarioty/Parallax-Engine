set (
    CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${ParallaxEngine_BUILD_DIR}
)

set (
    CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ${ParallaxEngine_BUILD_DIR}
)

if (CMAKE_COMPILER_IS_GNUCXX)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -pthread -lX11")
endif (CMAKE_COMPILER_IS_GNUCXX)

if (MSVC_VERSION GREATER_EQUAL "1900")
	add_compile_options("/std:c++latest")
endif (MSVC_VERSION GREATER_EQUAL "1900")
