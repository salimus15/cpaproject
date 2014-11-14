project(Mihp_vcheck_Test)
cmake_minimum_required(VERSION 2.8)

add_definitions(-fplugin=${CMAKE_BINARY_DIR}/Plugin/src/libmihpvcheckplugin.so)

add_executable(demo_fwd_depend main.c)
target_link_libraries(demo_fwd_depend mihpvcheck)

add_test(NAME DemoForwardDepend
	WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../../../Demonstration/Results/"
	COMMAND "${CMAKE_CURRENT_BINARY_DIR}/demo_fwd_depend" " > demo_fwd_depend.txt")



