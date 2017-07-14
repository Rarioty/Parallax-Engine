# Add all projects tests
include_directories(".")

# Generate libtest
add_library(tests SHARED tests.cpp)

add_subdirectory(PIL)
add_subdirectory(Core)

add_executable(parallax_test test_Parallax.cpp)
target_link_libraries(parallax_test tests ParallaxEngine)
set_target_properties(parallax_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ParallaxEngine_BUILD_DIR}/tests/)
add_test(parallax_test ${ParallaxEngine_BUILD_DIR}/tests/parallax_test)
add_coverage(parallax_test)
