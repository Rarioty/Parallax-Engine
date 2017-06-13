# Generate all tests for PIL library

set (cpptests
    sized_types
)

# add_executable(PIL_sized_types test_types_sizes.cpp)
# target_link_libraries(PIL_sized_types tests)
# set_target_properties(PIL_sized_types PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ParallaxEngine_BUILD_DIR}/tests/PIL/)
# add_test(PIL_sized_types ${ParallaxEngine_BUILD_DIR}/tests/PIL/PIL_sized_types)
# add_coverage(PIL_sized_types)

foreach (cpptest ${cpptests})
    add_executable(${cpptest} test_${cpptest}.cpp)
    target_link_libraries(${cpptest} tests ParallaxEngine)
    set_target_properties(${cpptest} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ParallaxEngine_BUILD_DIR}/tests/)
    add_test(${cpptest} ${ParallaxEngine_BUILD_DIR}/tests/${cpptest})
    add_coverage(${cpptest})
endforeach()
