# Make all sub-projects
add_subdirectory(PIL)
add_subdirectory(Core)

set (ROOT_SRCS
    Parallax.cpp
)

add_library(ParallaxEngine STATIC ${ROOT_SRCS})
target_link_libraries(ParallaxEngine Core PIL ${CMAKE_DL_LIBS} m z swresample lzma)

if (GRAPHICS_ALLOW_OPENGL)
    target_link_libraries(ParallaxEngine ${OPENGL_LIBRARIES})
endif (GRAPHICS_ALLOW_OPENGL)
if (GRAPHICS_ALLOW_VULKAN)
    target_link_libraries(ParallaxEngine ${Vulkan_LIBRARIES})
endif (GRAPHICS_ALLOW_VULKAN)

if (PHYSICS_ALLOW_PHYSX)
    target_link_libraries(ParallaxEngine ${PHYSX_LIBRARIES})
endif (PHYSICS_ALLOW_PHYSX)
if (PHYSICS_ALLOW_BULLET)
    target_link_libraries(ParallaxEngine ${BULLET_LIBRARIES})
endif (PHYSICS_ALLOW_BULLET)
