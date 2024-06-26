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
    "src/*.h"
    "src/*.cpp"
    "src/rendering/*.h"
    "src/rendering/*.cpp"
    "src/entities/*.h"
    "src/entities/*.cpp"
    "src/components/*.h"
    "src/components/*.cpp"
    "src/systems/*.h"
    "src/systems/*.cpp"
    "src/utils/*.h"
    "src/utils/*.cpp"
    "src/scenes/*.h"
    "src/scenes/*.cpp"
)

add_executable(main ${files} dep/glad/glad.c)

if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    find_package(glfw3 REQUIRED)
    set(GLFW_LIB glfw)

    find_package(Lua REQUIRED)
    include_directories(${LUA_INCLUDE_DIR})

    set(CMAKE_CXX_COMPILER clang++) # seems a bit faster

    target_compile_options(main PRIVATE 
        -O3
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion -Wsign-conversion
    )
else () # windows
    set(GLFW_LIBRARY_DIR "C:/Program Files/glfw-3.4/glfw-3.4.bin.WIN64")

    # TODO: fucking windows bullshit

    #find_package(glfw3 REQUIRED)
    set(GLFW_LIB glfw3dll)

    set(CMAKE_CXX_COMPILER "cl")

    target_compile_options(main PRIVATE 
        "/W3" "/O3" "/DNDEBUG" "/Zi" "/Gy"
    )
endif()

set(INCLUDE_DIR "${main_SOURCE_DIR}/dep")
target_include_directories(main PUBLIC ${INCLUDE_DIR})
target_include_directories(main PRIVATE src)
target_link_directories(main PUBLIC ${GLFW_LIBRARY_DIR})

find_package(OpenGL REQUIRED)

target_link_libraries(main ${GLFW_LIB} ${LUA_LIBRARIES} OpenGL::GL)