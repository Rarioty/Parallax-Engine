# Find all packages

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Find doxygen
find_package(Doxygen)
find_package(codecov)
find_package(OpenSSL)
find_package(Threads REQUIRED)
