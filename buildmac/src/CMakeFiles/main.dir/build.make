# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.29.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.29.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/buildmac

# Include any dependencies generated for this target.
include src/CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/main.dir/flags.make

src/CMakeFiles/main.dir/engine/rendering/window.cpp.o: src/CMakeFiles/main.dir/flags.make
src/CMakeFiles/main.dir/engine/rendering/window.cpp.o: /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/src/engine/rendering/window.cpp
src/CMakeFiles/main.dir/engine/rendering/window.cpp.o: src/CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/buildmac/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/main.dir/engine/rendering/window.cpp.o"
	cd /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/buildmac/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/main.dir/engine/rendering/window.cpp.o -MF CMakeFiles/main.dir/engine/rendering/window.cpp.o.d -o CMakeFiles/main.dir/engine/rendering/window.cpp.o -c /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/src/engine/rendering/window.cpp

src/CMakeFiles/main.dir/engine/rendering/window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/engine/rendering/window.cpp.i"
	cd /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/buildmac/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/src/engine/rendering/window.cpp > CMakeFiles/main.dir/engine/rendering/window.cpp.i

src/CMakeFiles/main.dir/engine/rendering/window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/engine/rendering/window.cpp.s"
	cd /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/buildmac/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/src/engine/rendering/window.cpp -o CMakeFiles/main.dir/engine/rendering/window.cpp.s

src/CMakeFiles/main.dir/main.cpp.o: src/CMakeFiles/main.dir/flags.make
src/CMakeFiles/main.dir/main.cpp.o: /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/src/main.cpp
src/CMakeFiles/main.dir/main.cpp.o: src/CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/buildmac/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/main.dir/main.cpp.o"
	cd /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/buildmac/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/main.dir/main.cpp.o -MF CMakeFiles/main.dir/main.cpp.o.d -o CMakeFiles/main.dir/main.cpp.o -c /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/src/main.cpp

src/CMakeFiles/main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cpp.i"
	cd /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/buildmac/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/src/main.cpp > CMakeFiles/main.dir/main.cpp.i

src/CMakeFiles/main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cpp.s"
	cd /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/buildmac/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/src/main.cpp -o CMakeFiles/main.dir/main.cpp.s

src/CMakeFiles/main.dir/glad/glad.c.o: src/CMakeFiles/main.dir/flags.make
src/CMakeFiles/main.dir/glad/glad.c.o: /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/src/glad/glad.c
src/CMakeFiles/main.dir/glad/glad.c.o: src/CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/buildmac/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/CMakeFiles/main.dir/glad/glad.c.o"
	cd /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/buildmac/src && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/main.dir/glad/glad.c.o -MF CMakeFiles/main.dir/glad/glad.c.o.d -o CMakeFiles/main.dir/glad/glad.c.o -c /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/src/glad/glad.c

src/CMakeFiles/main.dir/glad/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/main.dir/glad/glad.c.i"
	cd /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/buildmac/src && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/src/glad/glad.c > CMakeFiles/main.dir/glad/glad.c.i

src/CMakeFiles/main.dir/glad/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/main.dir/glad/glad.c.s"
	cd /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/buildmac/src && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/src/glad/glad.c -o CMakeFiles/main.dir/glad/glad.c.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/engine/rendering/window.cpp.o" \
"CMakeFiles/main.dir/main.cpp.o" \
"CMakeFiles/main.dir/glad/glad.c.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: src/CMakeFiles/main.dir/engine/rendering/window.cpp.o
main: src/CMakeFiles/main.dir/main.cpp.o
main: src/CMakeFiles/main.dir/glad/glad.c.o
main: src/CMakeFiles/main.dir/build.make
main: /opt/homebrew/lib/libglfw.3.4.dylib
main: /Library/Developer/CommandLineTools/SDKs/MacOSX14.2.sdk/System/Library/Frameworks/OpenGL.framework
main: src/CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/buildmac/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ../main"
	cd /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/buildmac/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/main.dir/build: main
.PHONY : src/CMakeFiles/main.dir/build

src/CMakeFiles/main.dir/clean:
	cd /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/buildmac/src && $(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/main.dir/clean

src/CMakeFiles/main.dir/depend:
	cd /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/buildmac && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/src /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/buildmac /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/buildmac/src /Users/aatostapper/Documents/Dev/OpenGL/2D-Engine/buildmac/src/CMakeFiles/main.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/CMakeFiles/main.dir/depend
