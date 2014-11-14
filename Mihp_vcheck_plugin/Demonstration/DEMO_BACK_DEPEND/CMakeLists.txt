project(Mihp_vcheck_Test)
cmake_minimum_required(VERSION 2.8)

add_definitions(-fplugin=${CMAKE_BINARY_DIR}/Plugin/src/libmihpvcheckplugin.so)

add_executable(demo_back_depend main.c)
target_link_libraries(demo_back_depend mihpvcheck)

add_test(NAME DemoBackDepend
	WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../../../Demonstration/Results/"
	COMMAND "${CMAKE_CURRENT_BINARY_DIR}/demo_back_depend" " > demo_back_depend.txt")



