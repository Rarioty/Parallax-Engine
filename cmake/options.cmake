# Add all options for cmake
option(BUILD_DOCUMENTATION  "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})
option(BUILD_TESTS          "Build and add a make command to launch tests" true)
