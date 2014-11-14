project(Mihp_vcheck_Test)
cmake_minimum_required(VERSION 2.8)

add_definitions(-fplugin=${CMAKE_BINARY_DIR}/Plugin/src/libmihpvcheckplugin.so)

add_executable(demo_vectorisable main.c)
target_link_libraries(demo_vectorisable mihpvcheck)

add_test(NAME DemoVectorisable
	WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../../../Demonstration/Results/"
	COMMAND "${CMAKE_CURRENT_BINARY_DIR}/demo_vectorisable"
	OUTPUT "demo_vectorisable.txt")



