cmake_minimum_required (VERSION 3.25...3.31)

# A interface to reuse common properties.
# You can add more external include paths of other projects that are needed for your project.

# Shared interface_
add_library ("dream-stellar_interface" INTERFACE)
target_link_libraries ("dream-stellar_interface" INTERFACE seqan3::seqan3)
target_link_libraries ("dream-stellar_interface" INTERFACE sharg::sharg)
target_include_directories ("dream-stellar_interface" INTERFACE ../include)
# SYSTEM keyword turns off compiler warnings for subprojects
target_include_directories ("dream-stellar_interface" SYSTEM INTERFACE ${seqan2_SOURCE_DIR}/include)
target_compile_options ("dream-stellar_interface" INTERFACE "-pedantic" "-Wall" "-Wextra")

option (DREAM_STELLAR_WITH_WERROR "Report compiler warnings as errors." ON)

if (DREAM_STELLAR_WITH_WERROR)
    target_compile_options ("dream-stellar_interface" INTERFACE "-Werror")
    message (STATUS "Building tests with -Werror.")
endif ()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # std::jthread is experimental before LLVM 20.
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 20)
        target_compile_definitions ("dream-stellar_interface" INTERFACE "_LIBCPP_ENABLE_EXPERIMENTAL")
    endif ()
endif ()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # GCC12 and above: Disable warning about std::hardware_destructive_interference_size not being ABI-stable.
    if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 12)
        target_compile_options ("dream-stellar_interface" INTERFACE "-Wno-interference-size")
    endif ()

    # Warn about failed return value optimization.
    if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 14)
        target_compile_options ("dream-stellar_interface" INTERFACE "-Wnrvo")
    endif ()

    # GCC on arm64 (M1): Disable notes about ABI changes. Example:
    # `parameter passing for argument of type 'std::ranges::single_view<double>' when C++17 is enabled changed to match C++14 in GCC 10.1`
    # https://github.com/gcc-mirror/gcc/commit/56fe3ca30e1343e4f232ca539726506440e23dd3
    if ("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "arm64")
        target_compile_options ("dream-stellar_interface" INTERFACE "-Wno-psabi")
    endif ()
endif ()

# Threshold library
add_library ("raptor_threshold" STATIC
             raptor/threshold/threshold.cpp
             raptor/threshold/one_indirect_error_model.cpp
             raptor/threshold/multiple_error_model.cpp
             raptor/threshold/pascal_row.cpp
             raptor/threshold/one_error_model.cpp
             raptor/threshold/precompute_correction.cpp
             raptor/threshold/precompute_threshold.cpp
)
target_link_libraries ("raptor_threshold" PUBLIC "dream-stellar_interface")

# Valik library
add_library ("dream-stellar_lib" STATIC 
             argument_parsing/build.cpp
             argument_parsing/search.cpp
             argument_parsing/shared.cpp
             argument_parsing/top_level.cpp
             consolidate/consolidate_matches.cpp
             consolidate/merge_processes.cpp
             prepare/compute_bin_size.cpp
             split/write_seg_sequences.cpp
             threshold/find.cpp
             valik_build.cpp
             valik_search.cpp
)
target_link_libraries ("dream-stellar_lib" PUBLIC "raptor_threshold")

# Valik executable
add_executable ("dream-stellar" valik_main.cpp)
target_link_libraries ("dream-stellar" PUBLIC "dream-stellar_lib")

if (NOT DEFINED ENV{CI})
    # Log git commit
    execute_process(COMMAND git rev-parse HEAD
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE COMMIT_ID
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    add_custom_command(TARGET "dream-stellar" POST_BUILD
        WORKING_DIRECTORY
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMAND
            ${CMAKE_COMMAND} -E echo ${COMMIT_ID} > version.md
        COMMENT
            "Generating file version.md"
        VERBATIM)
endif ()
