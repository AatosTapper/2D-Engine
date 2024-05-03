cmake_minimum_required(VERSION 3.18)

project(main)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# --------------------------------
# ADD NEW FOLDERS BELOW LIKE THIS
# --------------------------------
# "src/folder/subfolder/etc/*.h"
# "src/folder/subfolder/etc/*.cpp"
# --------------------------------

file(GLOB_RECURSE files
    "src/*.h"
    "src/*.cpp"
    "src/engine/*.h"
    "src/engine/*.cpp"
    "src/engine/rendering/*.h"
    "src/engine/rendering/*.cpp"
    "src/engine/gameobjects/*.h"
    "src/engine/gameobjects/*.cpp"
)

add_executable(main ${files} src/glad/glad.c)

if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    find_package(glfw3 REQUIRED)
    set(GLFW_LIB glfw)

    set(CMAKE_CXX_COMPILER clang++) # seems a bit faster

    target_compile_options(main PRIVATE 
        -O2
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion -Wsign-conversion
        -Wno-deprecated-declarations
    )
else () # windows (no linux here so else is enough)
    set(GLFW_LIBRARY_DIR "${main_SOURCE_DIR}/dep/libglfw3/lib-vc2022")
    set(GLFW_LIB glfw3dll)

    set(CMAKE_CXX_COMPILER "cl")

    target_compile_options(main PRIVATE 
        "/W3" "/O2" "/DNDEBUG" "/Zi" "/Gy"
    )
endif()

set(INCLUDE_DIR "${main_SOURCE_DIR}/dep")
include_directories(${INCLUDE_DIR})
link_directories(${GLFW_LIBRARY_DIR})

find_package(OpenGL REQUIRED)

target_link_libraries(main ${GLFW_LIB} OpenGL::GL)