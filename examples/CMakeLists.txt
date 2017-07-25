# Generate all tests for PIL library
set (simple-examples
    00-helloworld
)

foreach (example ${simple-examples})
    add_executable(${example} ${example}/${example}.cpp)
    target_link_libraries(${example} ParallaxEngine)
    set_target_properties(${example} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ParallaxEngine_BUILD_DIR}/examples/)
    add_coverage(${example})
endforeach()
