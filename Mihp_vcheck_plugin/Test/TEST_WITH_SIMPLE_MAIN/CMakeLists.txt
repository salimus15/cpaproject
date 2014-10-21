project(Mihp_vcheck_Test)
cmake_minimum_required(VERSION 2.8)

link_directories(${CMAKE_BINARY_DIR}/Plugin/src/)

add_definitions(-fplugin=${CMAKE_BINARY_DIR}/Plugin/src/libmihpvcheckplugin.so)

add_executable(test_with_simple_plugin main.c)
target_link_libraries(test_with_simple_plugin mihpvcheck)


