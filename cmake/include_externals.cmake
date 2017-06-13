# Add a target to generate API documentation with Doxygen
if (BUILD_DOCUMENTATION)
    if (NOT DOXYGEN_FOUND)
        message (FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif (NOT DOXYGEN_FOUND)

    configure_file(
        ${ParallaxEngine_DOC_DIR}/doxyfile.in
        ${ParallaxEngine_DOC_DIR}/Doxyfile @ONLY
    )

    add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${ParallaxEngine_DOC_DIR}/Doxyfile WORKING_DIRECTORY ${ParallaxEngine_ROOT_DIR} COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif (BUILD_DOCUMENTATION)

if (CMAKE_COMPILER_IS_GNUCXX)
    if (ENABLE_COVERAGE)
        enable_testing()
        coverage_evaluate()
    endif (ENABLE_COVERAGE)
endif (CMAKE_COMPILER_IS_GNUCXX)
