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
if (NOT TARGET dream-stellar_test)
    add_library (dream-stellar_test INTERFACE)
    target_link_libraries (dream-stellar_test INTERFACE GTest::gtest_main dream-stellar_lib)
    add_library (dream-stellar::test ALIAS dream-stellar_test)
    
    # !Workaround: Get seqan3 test include dir from seqan3 target
    find_path (SEQAN3_TEST_INCLUDE_DIR
               NAMES seqan3/test/tmp_directory.hpp
               HINTS "${seqan3_SOURCE_DIR}/test/include"
    )
    target_include_directories (dream-stellar_test SYSTEM INTERFACE "${SEQAN3_TEST_INCLUDE_DIR}")
endif ()

# Add the check target that builds and runs tests.
add_custom_target (check COMMAND ${CMAKE_CTEST_COMMAND} ${CMAKE_CTEST_ARGUMENTS})

get_directory_property (dream-stellar_targets DIRECTORY "${dream-stellar_SOURCE_DIR}/src" BUILDSYSTEM_TARGETS)
foreach (target IN LISTS dream-stellar_targets)
    get_target_property (type ${target} TYPE)
    if (type STREQUAL "EXECUTABLE")
        list (APPEND dream-stellar_EXECUTABLE_LIST ${target})
    endif ()
endforeach ()
unset (dream-stellar_targets)

macro (add_app_test test_filename)
    file (RELATIVE_PATH source_file "${dream-stellar_SOURCE_DIR}" "${CMAKE_CURRENT_LIST_DIR}/${test_filename}")
    get_filename_component (target "${source_file}" NAME_WE)

    add_executable (${target} ${test_filename})
    target_link_libraries (${target} dream-stellar::test)

    add_dependencies (${target} ${dream-stellar_EXECUTABLE_LIST})
    add_dependencies (check ${target})

    add_test (NAME ${target} COMMAND ${target})

    unset (source_file)
    unset (target)
endmacro ()
