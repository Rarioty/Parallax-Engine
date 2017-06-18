# Generate all tests for PIL library

set (cpptests
    collection_linked_list
    collection_linked_list_iterator
    collection_vector
    collection_vector_iterator
    collection_stack
)

set (cppperfs
    collection_linked_list
    collection_vector
    collection_stack
)

foreach (cpptest ${cpptests})
    set (cpptest test_${cpptest})
    add_executable(${cpptest} ${cpptest}.cpp)
    target_link_libraries(${cpptest} tests ParallaxEngine)
    set_target_properties(${cpptest} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ParallaxEngine_BUILD_DIR}/tests/collections/)
    add_test(${cpptest} ${ParallaxEngine_BUILD_DIR}/tests/collections/${cpptest})
    add_coverage(${cpptest})
endforeach()

foreach (perf ${cppperfs})
    set (perf perfs_${perf})
    add_executable(${perf} ${perf}.cpp)
    target_link_libraries(${perf} tests ParallaxEngine)
    set_target_properties(${perf} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ParallaxEngine_BUILD_DIR}/perfs/collections/)
endforeach()
