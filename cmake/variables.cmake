# Versions of the project
set (ParallaxEngine_API_VERSION     100)
set (ParallaxEngine_VERSION_MAJOR 	1)
set (ParallaxEngine_VERSION_MINOR 	0)
set (ParallaxEngine_VERSION_PATCH   0)
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
set (ParallaxEngine_EXT_DIR			${ParallaxEngine_ROOT_DIR}/externals)
set (ParallaxEngine_3RD_PARTY       ${ParallaxEngine_ROOT_DIR}/3rdparty)
