project(Mihp_vcheck_Test)
cmake_minimum_required(VERSION 2.8)

add_definitions(-fplugin=${CMAKE_BINARY_DIR}/Plugin/src/libmihpvcheckplugin.so)

add_executable(test_pragma_mihp main.c)
target_link_libraries(test_pragma_mihp mihpvcheck)


