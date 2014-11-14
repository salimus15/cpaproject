project(Mihp_vcheck_Test)
cmake_minimum_required(VERSION 2.8)

add_executable(test_without_plugin_vector_size main.c)
target_link_libraries(test_without_plugin_vector_size mihpvcheck)

