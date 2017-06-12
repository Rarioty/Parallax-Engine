# Versions of the project
set (ParallaxEngine_VERSION_MAJOR 	1)
set (ParallaxEngine_VERSION_MINOR 	0)
string (TIMESTAMP ParallaxEngine_MAKE_DATE "%m%d%y")
string (TIMESTAMP ParallaxEngine_MAKE_HOUR "%H%M%S")

# Defines directories variables
set (ParallaxEngine_ROOT_DIR		${CMAKE_CURRENT_SOURCE_DIR})
set (ParallaxEngine_BUILD_DIR		${ParallaxEngine_ROOT_DIR}/build)
set (ParallaxEngine_HEADER_DIR		${ParallaxEngine_ROOT_DIR}/include)
set (ParallaxEngine_CONFIG_DIR		${ParallaxEngine_ROOT_DIR}/config)
set (ParallaxEngine_SRC_DIR			${ParallaxEngine_ROOT_DIR}/src)
set (ParallaxEngine_DOC_DIR			${ParallaxEngine_ROOT_DIR}/doc)
set (ParallaxEngine_LIB_DIR			${ParallaxEngine_ROOT_DIR}/lib)

# Set build variables
if (UNIX)
    set (PARALLAX_BUILD_SYSTEM_UNIX true)
endif (UNIX)
if (WIN32)
    set (PARALLAX_BUILD_SYSTEM_WIN32 true)
endif (WIN32)
if (APPLE)
    set (PARALLAX_BUILD_SYSTEM_APPLE true)
endif (APPLE)
