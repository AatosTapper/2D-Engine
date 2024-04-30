cmake_minimum_required(VERSION 3.18)

project(main)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(main src/main.cpp src/extern.h)

set(GLFW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/dep/glfw3/include")

if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    find_package(glfw3 REQUIRED)
    set(GLFW_LIB glfw)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(GLFW_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/dep/glfw3/lib-vc2022")
    set(GLFW_LIB glfw3dll)
endif()

include_directories(${GLFW_INCLUDE_DIR})
link_directories(${GLFW_LIBRARY_DIR})

find_package(OpenGL REQUIRED)

target_link_libraries(main ${GLFW_LIB} OpenGL::GL)