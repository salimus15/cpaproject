project(Mihp_vcheck_plugin)
cmake_minimum_required(VERSION 2.8)



add_library(mihpvcheck SHARED mihp_vcheck.cpp)

install(TARGETS mihpvcheck LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${headers} DESTINATION include/Mihp_vcheck_plugin)



