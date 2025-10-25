# SPDX-FileCopyrightText: 2006-2025, Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2025, Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: CC0-1.0

# CPM Package Lock
# This file should be committed to version control

# cmake-format: off

# seqan2
set (DREAM_STELLAR_SEQAN2_VERSION 2.5.1 CACHE STRING "")
CPMDeclarePackage (seqan2
                   NAME seqan2
                   VERSION ${DREAM_STELLAR_SEQAN2_VERSION}
                   GIT_TAG seqan-v${DREAM_STELLAR_SEQAN2_VERSION}
                   GITHUB_REPOSITORY seqan/seqan
                   DOWNLOAD_ONLY TRUE
                   QUIET TRUE
)

# seqan3
set (DREAM_STELLAR_SEQAN3_VERSION 3.4.0 CACHE STRING "")
CPMDeclarePackage (seqan3
                   NAME seqan3
                   VERSION ${DREAM_STELLAR_SEQAN3_VERSION}
                   GIT_TAG ${DREAM_STELLAR_SEQAN3_VERSION}
                   GITHUB_REPOSITORY seqan/seqan3
                   SYSTEM TRUE
                   EXCLUDE_FROM_ALL TRUE
                   OPTIONS "INSTALL_SEQAN3 OFF" "CMAKE_MESSAGE_LOG_LEVEL WARNING"
)

# sharg
set (DREAM_STELLAR_SHARG_VERSION cafa602ced86f3a347064c5b8188316db09ade72 CACHE STRING "")
CPMDeclarePackage (sharg
                   NAME sharg
                   GIT_TAG ${DREAM_STELLAR_SHARG_VERSION} # main
                   GITHUB_REPOSITORY seqan/sharg-parser
                   SYSTEM TRUE
                   EXCLUDE_FROM_ALL TRUE
                   OPTIONS "INSTALL_SHARG OFF" "INSTALL_TDL OFF" "CMAKE_MESSAGE_LOG_LEVEL WARNING" "BUILD_TESTING OFF"
)

# googletest
set (DREAM_STELLAR_GOOGLETEST_VERSION 1.17.0 CACHE STRING "")
CPMDeclarePackage (googletest
                   NAME GTest
                   VERSION ${DREAM_STELLAR_GOOGLETEST_VERSION}
                   GITHUB_REPOSITORY google/googletest
                   SYSTEM TRUE
                   OPTIONS "BUILD_GMOCK OFF" "INSTALL_GTEST OFF" "CMAKE_MESSAGE_LOG_LEVEL WARNING"
)

# use_ccache
set (USE_CCACHE_VERSION d2a54ef555b6fc2d496a4c9506dbeb7cf899ce37 CACHE STRING "")
CPMDeclarePackage (use_ccache
                   NAME use_ccache
                   GIT_TAG ${USE_CCACHE_VERSION} # main
                   GITHUB_REPOSITORY seqan/cmake-scripts
                   SOURCE_SUBDIR ccache
                   SYSTEM TRUE
                   EXCLUDE_FROM_ALL TRUE
)

# cmake-format: on
