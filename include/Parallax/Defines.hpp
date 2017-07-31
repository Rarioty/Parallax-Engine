#ifndef PARALLAX_DEFINES_HPP_GUARD
#define PARALLAX_DEFINES_HPP_GUARD

#include <Parallax/Platform.hpp>

#if PARALLAX_COMPILER_MSVC
	#define not		!
#endif

#define IGNORE_C4127(x)	((bool)(!!(x)))

#endif
