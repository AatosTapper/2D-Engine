cmake_minimum_required(VERSION 3.18)

project(main)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_executable(main src/main.cpp src/glad/glad.c)

if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    find_package(glfw3 REQUIRED)
    set(GLFW_LIB glfw)

    target_compile_options(main PRIVATE 
        -O3
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion -Wsign-conversion
        -Wno-deprecated-declarations
    )
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(GLFW_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/dep/libglfw3/lib-vc2022")
    set(GLFW_LIB glfw3dll)

    set(CMAKE_CXX_COMPILER "cl")

    target_compile_options(main PRIVATE 
        "/W3"
    )
endif()

set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/dep")
include_directories(${INCLUDE_DIR})
link_directories(${GLFW_LIBRARY_DIR})

find_package(OpenGL REQUIRED)

target_link_libraries(main ${GLFW_LIB} OpenGL::GL)