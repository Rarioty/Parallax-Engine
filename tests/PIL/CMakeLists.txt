# Generate all tests for PIL library

set (cpptests
    sized_types
)

foreach (cpptest ${cpptests})
    add_executable(${cpptest} test_${cpptest}.cpp)
    target_link_libraries(${cpptest} tests ParallaxEngine)
    set_target_properties(${cpptest} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ParallaxEngine_BUILD_DIR}/tests/)
    add_test(${cpptest} ${ParallaxEngine_BUILD_DIR}/tests/${cpptest})
    add_coverage(${cpptest})
endforeach()

add_subdirectory(Threads)
add_subdirectory(Collections)
add_subdirectory(fs)
