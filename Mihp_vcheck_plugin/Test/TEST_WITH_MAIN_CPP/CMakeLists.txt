project(Mihp_vcheck_Test)
cmake_minimum_required(VERSION 2.8)


add_definitions(-fplugin=${CMAKE_BINARY_DIR}/Plugin/src/libmihpvcheckplugin.so)

add_executable(test_cpp_with_simple_plugin main.cpp)
target_link_libraries(test_cpp_with_simple_plugin mihpvcheck)


