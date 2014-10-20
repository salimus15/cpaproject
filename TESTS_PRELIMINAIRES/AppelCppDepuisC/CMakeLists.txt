project(AppelCPPDepuisC)
cmake_minimum_required(VERSION 2.8)

add_definitions(-Wall -O0)
add_library(librairie SHARED librairie.cpp)


add_executable(test main.c)
target_link_libraries(test librairie)


