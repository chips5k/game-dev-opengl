cmake_minimum_required(VERSION 3.9)
project(learning--opengl)

set(CMAKE_CXX_STANDARD 11)

add_custom_target(main)


add_executable(learning--opengl main.cpp)
add_library(glad vendor/src/glad/glad.c)
add_library(stb vendor/src/stb/stb_image.cpp)

add_custom_command(TARGET main
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources
        ${CMAKE_BINARY_DIR}/resources)

include_directories(vendor/includes)
add_subdirectory(vendor/src/glfw-3.2.1)

target_link_libraries(learning--opengl glfw glad stb)

