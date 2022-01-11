cmake_minimum_required (VERSION 3.8)

# A interface to reuse common properties.
# You can add more external include paths of other projects that are needed for your project.
add_library ("${PROJECT_NAME}_interface" INTERFACE)
target_link_libraries ("${PROJECT_NAME}_interface" INTERFACE seqan3::seqan3)
target_include_directories ("${PROJECT_NAME}_interface" INTERFACE ../include)
target_include_directories ("${PROJECT_NAME}_interface" INTERFACE ../lib/robin-hood-hashing/src/include)
target_compile_options ("${PROJECT_NAME}_interface" INTERFACE "-pedantic" "-Wall" "-Wextra")

#                                    raptor_build_lib  +
#                                                      |
#                                                      +---> raptor_lib +-----> raptor
#                                                      |
# raptor_minimiser_model_lib +-----> raptor_search_lib +

# raptor build
add_library ("${PROJECT_NAME}_build_lib" STATIC raptor_build.cpp)
target_link_libraries ("${PROJECT_NAME}_build_lib" PUBLIC "${PROJECT_NAME}_interface")
target_include_directories ("${PROJECT_NAME}_build_lib" PUBLIC ../include)

# the minimiser model will be used for raptor search
add_library ("${PROJECT_NAME}_minimiser_model_lib" STATIC minimiser_model.cpp)
target_link_libraries ("${PROJECT_NAME}_minimiser_model_lib" PUBLIC "${PROJECT_NAME}_interface")
target_include_directories ("${PROJECT_NAME}_minimiser_model_lib" PUBLIC ../include)

# raptor search
add_library ("${PROJECT_NAME}_search_lib" STATIC raptor_search.cpp)
target_link_libraries ("${PROJECT_NAME}_search_lib" PUBLIC "${PROJECT_NAME}_minimiser_model_lib")

# raptor consists of raptor build and raptor search
add_library ("${PROJECT_NAME}_lib" STATIC raptor.cpp)
target_link_libraries ("${PROJECT_NAME}_lib" PUBLIC "${PROJECT_NAME}_build_lib")
target_link_libraries ("${PROJECT_NAME}_lib" PUBLIC "${PROJECT_NAME}_search_lib")

# the executable
add_executable ("${PROJECT_NAME}" raptor_main.cpp)
target_link_libraries ("${PROJECT_NAME}" "${PROJECT_NAME}_lib")
