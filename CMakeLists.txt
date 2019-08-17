
cmake_minimum_required(VERSION 3.0)

project(c-plugins)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()

add_subdirectory(src/plugin_launcher)
add_subdirectory(src/plugins/plugin_test)

