
project(plugin-launcher C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist/${CMAKE_BUILD_TYPE}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -no-pie")

add_executable(${PROJECT_NAME} 
	main_plugin_launcher.c
)

target_link_libraries(${PROJECT_NAME}
	dl	
)

