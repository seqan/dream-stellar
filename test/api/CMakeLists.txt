cmake_minimum_required (VERSION 3.25...3.31)

add_custom_target (api_test ALL)

macro (add_api_test test_filename)
    add_app_test (${test_filename})

    seqan3_test_component (target "${test_filename}" TARGET_NAME)
    add_dependencies (api_test ${target})
endmacro ()

add_subdirectory(utilities)
add_subdirectory(valik)
