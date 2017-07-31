# Add all options for cmake
option(BUILD_DOCUMENTATION  "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})
option(BUILD_TESTS          "Build and add a make command to launch tests" true)
option(BUILD_EXAMPLES       "Build examples" true)

# Graphics libraries
option(GRAPHICS_ALLOW_OPENGL        "Allow to use OpenGL"   true)
if (APPLE)
    option(GRAPHICS_ALLOW_VULKAN    "Allow to use Vulkan"   false)
else(APPLE)
    option(GRAPHICS_ALLOW_VULKAN    "Allow to use Vulkan"   true)
endif(APPLE)

# Physics libraries
option(PHYSICS_ALLOW_BULLET         "Allow to use Bullet"   true)
if (WIN32)
    option(PHYSICS_ALLOW_PHYSX      "Allow to use Physx"    true)
else(WIN32)
    option(PHYSICS_ALLOW_PHYSX      "Allow to use Physx"    false)
endif(WIN32)

if (NOT (GRAPHICS_ALLOW_OPENGL OR GRAPHICS_ALLOW_VULKAN))
    message(FATAL_ERROR "Parallax Engine needs at least one graphic library to run")
endif(NOT (GRAPHICS_ALLOW_OPENGL OR GRAPHICS_ALLOW_VULKAN))

if (NOT (PHYSICS_ALLOW_PHYSX OR PHYSICS_ALLOW_BULLET))
    message(FATAL_ERROR "Parallax Engine needs at least one physic library to run")
endif(NOT (PHYSICS_ALLOW_PHYSX OR PHYSICS_ALLOW_BULLET))
