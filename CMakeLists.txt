cmake_minimum_required(VERSION 3.9)
project(opengl)

set(CMAKE_CXX_STANDARD 11)



add_executable(opengl main.cpp glad.c)
add_custom_target(copy-resources)
add_custom_command(TARGET copy-resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders
        ${CMAKE_BINARY_DIR}/shaders)

include_directories(vendor/includes)
add_subdirectory(vendor/src/glfw-3.2.1)

target_link_libraries(opengl glfw)

