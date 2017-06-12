# Generate all tests for PIL library

add_executable(PIL_sized_types test_types_sizes.cpp)
target_link_libraries(PIL_sized_types tests)
set_target_properties(PIL_sized_types PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ParallaxEngine_BUILD_DIR}/tests/PIL/)
