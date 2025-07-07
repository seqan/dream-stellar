# SPDX-FileCopyrightText: 2006-2025 Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2025 Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: CC0-1.0

cmake_minimum_required (VERSION 3.25)

# Define the application name and version.
project (dream-stellar
         LANGUAGES CXX
         VERSION 1.0.0
         DESCRIPTION "Find the set of local alignments between sets of reference and query sequences."
         HOMEPAGE_URL "https://github.com/seqan/dream-stellar"
)

# This allows including `*.cmake` files from the `cmake` directory without specifying the full path.
list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Sets C++ standard and link time optimisation.
include (cxx_config)

# Specify the directories where to store the built archives, libraries and executables.
include (output_directories)

# Add packages.
# We use CPM for package management: https://github.com/cpm-cmake/CPM.cmake
# The added packages (e.g., hibf, sharg, seqan3) are defined in the `cmake/package-lock.cmake` file.
option (DREAM_STELLAR_PACKAGE "Enable packaging for dream-stellar." OFF)
if (DREAM_STELLAR_PACKAGE)
    set (CPM_SOURCE_CACHE "${CMAKE_CURRENT_BINARY_DIR}/vendor")
    set (CPM_USE_LOCAL_PACKAGES OFF)
    include (package)
elseif (EXISTS "${CMAKE_CURRENT_LIST_DIR}/vendor")
    set (CPM_SOURCE_CACHE "${CMAKE_CURRENT_LIST_DIR}/vendor")
endif ()

include (CPM)
CPMUsePackageLock (${CMAKE_CURRENT_LIST_DIR}/cmake/package-lock.cmake)

CPMGetPackage (use_ccache) # Speeds up compilation by caching files that have been compiled before.

# Comment/Uncomment entries as needed.
# If you change something here, make sure to add/remove the target in target_link_libraries of src/CMakeLists.txt.
CPMGetPackage (use_ccache)
CPMGetPackage (sharg)
CPMGetPackage (seqan2)
CPMGetPackage (seqan3)

# Add the application. This will include `src/CMakeLists.txt`.
add_subdirectory (src)

# An option to disable configuring and building the tests. Tests are enabled if this is the main CMakeLists.txt.
# It can be used when calling CMake: `cmake .. -DDREAM_STELLAR_TEST=OFF`.
# It is good practice to allow disabling tests. If another project includes your application,
# it might not want to build your tests.
option (DREAM_STELLAR_TEST "Enable testing for dream-stellar." ${PROJECT_IS_TOP_LEVEL})

if (DREAM_STELLAR_TEST)
    list (APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure;--no-tests=error") # Must be before `enable_testing ()`.
    enable_testing () # Makes ctest work in root build directory.
    # Add the tests. This will include `test/CMakeLists.txt`.
    add_subdirectory (test)
endif ()
