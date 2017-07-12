configure_file(
	"${ParallaxEngine_CONFIG_DIR}/Parallax.hpp.in"
	"${ParallaxEngine_HEADER_DIR}/Parallax/Parallax.hpp"
	)

file(MAKE_DIRECTORY ${ParallaxEngine_ROOT_DIR}/build)
file(MAKE_DIRECTORY ${ParallaxEngine_BUILD_DIR}/tests)
file(MAKE_DIRECTORY ${ParallaxEngine_BUILD_DIR}/perfs)
file(MAKE_DIRECTORY ${ParallaxEngine_BUILD_DIR}/tests/threads)
file(MAKE_DIRECTORY ${ParallaxEngine_BUILD_DIR}/tests/collections)
