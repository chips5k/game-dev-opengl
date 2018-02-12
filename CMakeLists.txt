cmake_minimum_required(VERSION 3.9)
project(opengl)

set(CMAKE_CXX_STANDARD 11)

add_executable(opengl main.cpp glad.c)

include_directories(vendor/includes)
add_subdirectory(vendor/src/glfw-3.2.1)

target_link_libraries(opengl glfw)

