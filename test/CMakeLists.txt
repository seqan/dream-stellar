cmake_minimum_required (VERSION 3.25...3.31)

# Set directories for test output files, input data and binaries.
file (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/output)
add_definitions (-DOUTPUTDIR=\"${CMAKE_CURRENT_BINARY_DIR}/output/\")
add_definitions (-DDATADIR=\"${CMAKE_CURRENT_BINARY_DIR}/data/\")
add_definitions (-DBINDIR=\"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/\")

# !Workaround: Get seqan3 test dir from seqan3 target
find_path (SEQAN3_TEST_DIR
           NAMES seqan3-test.cmake
           HINTS "${seqan3_SOURCE_DIR}/test"
)
list (APPEND CMAKE_MODULE_PATH "${SEQAN3_TEST_DIR}/cmake")

CPMGetPackage (googletest)

# Build tests just before their execution, because they have not been built with "all" target.
# The trick is here to provide a cmake file as a directory property that executes the build command.
file (WRITE "${CMAKE_CURRENT_BINARY_DIR}/build_test_targets.cmake"
            "execute_process (COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target api_test)\n"
            "execute_process (COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target cli_test)\n"
            "execute_process (COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target header_test)\n")
set_directory_properties (PROPERTIES TEST_INCLUDE_FILE "${CMAKE_CURRENT_BINARY_DIR}/build_test_targets.cmake")

# Test executables and libraries should not mix with the application files.
unset (CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
unset (CMAKE_LIBRARY_OUTPUT_DIRECTORY)
unset (CMAKE_RUNTIME_OUTPUT_DIRECTORY)

include (seqan3_test_component)

# A macro that adds an api or cli test.
macro (add_app_test test_filename)
    # Extract the test target name.
    file (RELATIVE_PATH source_file "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_LIST_DIR}/${test_filename}")
    seqan3_test_component (target "${source_file}" TARGET_NAME)
    seqan3_test_component (test_name "${source_file}" TEST_NAME)

    # Create the test target.
    add_executable (${target} ${test_filename})
    target_link_libraries (${target} "${PROJECT_NAME}_lib" GTest::gtest_main)

    # Make seqan3::test available for both cli and api tests.
    target_include_directories (${target} PUBLIC "${SEQAN3_TEST_DIR}/include")

    # Generate and set the test name.
    add_test (NAME "${test_name}" COMMAND ${target})

    unset (source_file)
    unset (target)
    unset (test_name)
endmacro ()

string (TOUPPER ${PROJECT_NAME} uppercase_project_name)
set (${uppercase_project_name}_HEADER_TEST_ONLY OFF CACHE BOOL "Only build header test.")

if (${uppercase_project_name}_HEADER_TEST_ONLY)
    message (STATUS "${FontBold}Building header test only.${FontReset}")
    add_subdirectory (header)
else ()
    # Fetch data and add the tests.
    include (data/datasources.cmake)
    add_subdirectory (api)
    add_subdirectory (cli)
endif ()

message (STATUS "${FontBold}You can run `make test` to build and run tests.${FontReset}")
