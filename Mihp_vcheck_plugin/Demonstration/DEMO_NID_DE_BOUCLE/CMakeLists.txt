project(Mihp_vcheck_Test)
cmake_minimum_required(VERSION 2.8)

add_definitions(-fplugin=${CMAKE_BINARY_DIR}/Plugin/src/libmihpvcheckplugin.so)

add_executable(demo_nid_de_boucle main.c)
target_link_libraries(demo_nid_de_boucle mihpvcheck)

add_test(NAME DemoNidDeBoucle
	WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../../../Demonstration/Results/"
	COMMAND "${CMAKE_CURRENT_BINARY_DIR}/demo_nid_de_boucle"
	OUTPUT "demo_nid_de_boucle.txt")



