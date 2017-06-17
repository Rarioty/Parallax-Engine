# Generate all tests for PIL library

set (cpptests
    collection_linked_list
    collection_linked_list_iterator
)

foreach (cpptest ${cpptests})
    add_executable(${cpptest} test_${cpptest}.cpp)
    target_link_libraries(${cpptest} tests ParallaxEngine)
    set_target_properties(${cpptest} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ParallaxEngine_BUILD_DIR}/tests/collections/)
    add_test(${cpptest} ${ParallaxEngine_BUILD_DIR}/tests/collections/${cpptest})
    add_coverage(${cpptest})
endforeach()
