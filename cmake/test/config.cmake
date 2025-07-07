# SPDX-FileCopyrightText: 2006-2025 Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2025 Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: CC0-1.0

list (APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure") # Must be before `enable_testing ()`.
list (APPEND CMAKE_CTEST_ARGUMENTS "--no-tests=error") # Must be before `enable_testing ()`.
CPMGetPackage (googletest)

enable_testing ()

# Set directories for test output files, input data and binaries.
file (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/output)
add_definitions (-DOUTPUTDIR=\"${CMAKE_CURRENT_BINARY_DIR}/output/\")
add_definitions (-DDATADIR=\"${CMAKE_CURRENT_BINARY_DIR}/data/\")
add_definitions (-DBINDIR=\"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/\")

# Add the test interface library.
if (NOT TARGET ${PROJECT_NAME}_test)
    add_library (${PROJECT_NAME}_test INTERFACE)
    target_link_libraries (${PROJECT_NAME}_test INTERFACE GTest::gtest_main ${PROJECT_NAME}_lib)
    add_library (${PROJECT_NAME}::test ALIAS ${PROJECT_NAME}_test)
    
    # !Workaround: Get seqan3 test include dir from seqan3 target
    find_path (SEQAN3_TEST_INCLUDE_DIR
               NAMES seqan3/test/tmp_directory.hpp
               HINTS "${seqan3_SOURCE_DIR}/test/include"
    )
    target_include_directories (${PROJECT_NAME}_test SYSTEM INTERFACE "${SEQAN3_TEST_INCLUDE_DIR}")
endif ()

# Add the check target that builds and runs tests.
add_custom_target (check COMMAND ${CMAKE_CTEST_COMMAND} ${CMAKE_CTEST_ARGUMENTS})

get_directory_property (${PROJECT_NAME}_targets DIRECTORY "${${PROJECT_NAME}_SOURCE_DIR}/src" BUILDSYSTEM_TARGETS)
foreach (target IN LISTS ${PROJECT_NAME}_targets)
    get_target_property (type ${target} TYPE)
    if (type STREQUAL "EXECUTABLE")
        list (APPEND ${PROJECT_NAME}_EXECUTABLE_LIST ${target})
    endif ()
endforeach ()
unset (${PROJECT_NAME}_targets)

macro (add_app_test test_filename)
    file (RELATIVE_PATH source_file "${${PROJECT_NAME}_SOURCE_DIR}" "${CMAKE_CURRENT_LIST_DIR}/${test_filename}")
    get_filename_component (target "${source_file}" NAME_WE)

    add_executable (${target} ${test_filename})
    target_link_libraries (${target} ${PROJECT_NAME}::test)

    add_dependencies (${target} ${${PROJECT_NAME}_EXECUTABLE_LIST})
    add_dependencies (check ${target})

    add_test (NAME ${target} COMMAND ${target})

    unset (source_file)
    unset (target)
endmacro ()
