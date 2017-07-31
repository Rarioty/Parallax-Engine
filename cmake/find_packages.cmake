# Find all packages

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Find doxygen
find_package(Doxygen)
find_package(codecov)
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

if (GRAPHICS_ALLOW_OPENGL)
    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIRS})
endif(GRAPHICS_ALLOW_OPENGL)

if (GRAPHICS_ALLOW_VULKAN)
    find_package(Vulkan REQUIRED)
    include_directories(${Vulkan_INCLUDE_DIR})
endif (GRAPHICS_ALLOW_VULKAN)

if (PHYSICS_ALLOW_PHYSX)
    find_package(Physx REQUIRED)
    include_directories(${Physx_INCLUDE_DIR})
endif(PHYSICS_ALLOW_PHYSX)

if (PHYSICS_ALLOW_BULLET)
    find_package(Bullet REQUIRED)
    include_directories(${Bullet_INCLUDE_DIR})
endif(PHYSICS_ALLOW_BULLET)

include_directories(${OPENSSL_INCLUDE_DIR})
