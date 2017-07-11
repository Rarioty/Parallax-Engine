# Generate all tests for PIL library

set (cpptests
    parsers_csv
)

set (cppperfs
)

foreach (cpptest ${cpptests})
    set (cpptest test_${cpptest})
    add_executable(${cpptest} ${cpptest}.cpp)
    target_link_libraries(${cpptest} tests ParallaxEngine)
    set_target_properties(${cpptest} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ParallaxEngine_BUILD_DIR}/tests/parsers/)
    add_test(${cpptest} ${ParallaxEngine_BUILD_DIR}/tests/parsers/${cpptest})
    add_coverage(${cpptest})
endforeach()

foreach (perf ${cppperfs})
    set (perf perfs_${perf})
    add_executable(${perf} ${perf}.cpp)
    target_link_libraries(${perf} tests ParallaxEngine)
    set_target_properties(${perf} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ParallaxEngine_BUILD_DIR}/perfs/parsers/)
endforeach()
