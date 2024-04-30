cmake_minimum_required(VERSION 3.18)

project(main)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(main src/main.cpp src/extern.h)

set(GLFW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/dep/glfw3/include")
set(GLFW_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/dep/glfw3/lib-vc2022") # Adjust according to the version of Visual Studio

include_directories(${GLFW_INCLUDE_DIR})
link_directories(${GLFW_LIBRARY_DIR})

find_package(OpenGL REQUIRED)

target_link_libraries(main glfw3dll OpenGL::GL)