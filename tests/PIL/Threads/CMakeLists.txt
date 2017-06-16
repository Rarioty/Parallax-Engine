# Generate all tests for PIL library

set (cpptests
    thread_manager_default
    thread_manager_pause
    thread_manager_stop
    thread_manager_callback
    thread_manager_errors
    thread_manager_worker
)

foreach (cpptest ${cpptests})
    add_executable(${cpptest} test_${cpptest}.cpp)
    target_link_libraries(${cpptest} tests ParallaxEngine)
    set_target_properties(${cpptest} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ParallaxEngine_BUILD_DIR}/tests/threads/)
    add_test(${cpptest} ${ParallaxEngine_BUILD_DIR}/tests/threads/${cpptest})
    add_coverage(${cpptest})
endforeach()
