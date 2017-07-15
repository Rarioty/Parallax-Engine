# Find all packages

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Find doxygen
find_package(Doxygen)
find_package(codecov)
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Vulkan REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR})
include_directories(${Vulkan_INCLUDE_DIR})