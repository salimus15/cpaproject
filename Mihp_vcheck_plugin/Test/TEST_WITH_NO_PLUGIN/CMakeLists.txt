project(Mihp_vcheck_Test)
cmake_minimum_required(VERSION 2.8)

add_executable(test_with_no_plugin main.c)
target_link_libraries(test_with_no_plugin mihpvcheck)

