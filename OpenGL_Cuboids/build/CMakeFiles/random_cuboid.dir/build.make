# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/octo/Desktop/ui/OpenGL_Cuboids

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/octo/Desktop/ui/OpenGL_Cuboids/build

# Include any dependencies generated for this target.
include CMakeFiles/random_cuboid.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/random_cuboid.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/random_cuboid.dir/flags.make

CMakeFiles/random_cuboid.dir/src/main.cpp.o: CMakeFiles/random_cuboid.dir/flags.make
CMakeFiles/random_cuboid.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/octo/Desktop/ui/OpenGL_Cuboids/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/random_cuboid.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/random_cuboid.dir/src/main.cpp.o -c /home/octo/Desktop/ui/OpenGL_Cuboids/src/main.cpp

CMakeFiles/random_cuboid.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/random_cuboid.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/octo/Desktop/ui/OpenGL_Cuboids/src/main.cpp > CMakeFiles/random_cuboid.dir/src/main.cpp.i

CMakeFiles/random_cuboid.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/random_cuboid.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/octo/Desktop/ui/OpenGL_Cuboids/src/main.cpp -o CMakeFiles/random_cuboid.dir/src/main.cpp.s

# Object files for target random_cuboid
random_cuboid_OBJECTS = \
"CMakeFiles/random_cuboid.dir/src/main.cpp.o"

# External object files for target random_cuboid
random_cuboid_EXTERNAL_OBJECTS =

random_cuboid: CMakeFiles/random_cuboid.dir/src/main.cpp.o
random_cuboid: CMakeFiles/random_cuboid.dir/build.make
random_cuboid: /usr/lib/x86_64-linux-gnu/libGL.so
random_cuboid: /usr/lib/x86_64-linux-gnu/libglut.so
random_cuboid: /usr/lib/x86_64-linux-gnu/libGLU.so
random_cuboid: /usr/lib/x86_64-linux-gnu/libXmu.so
random_cuboid: /usr/lib/x86_64-linux-gnu/libXi.so
random_cuboid: CMakeFiles/random_cuboid.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/octo/Desktop/ui/OpenGL_Cuboids/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable random_cuboid"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/random_cuboid.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/random_cuboid.dir/build: random_cuboid

.PHONY : CMakeFiles/random_cuboid.dir/build

CMakeFiles/random_cuboid.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/random_cuboid.dir/cmake_clean.cmake
.PHONY : CMakeFiles/random_cuboid.dir/clean

CMakeFiles/random_cuboid.dir/depend:
	cd /home/octo/Desktop/ui/OpenGL_Cuboids/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/octo/Desktop/ui/OpenGL_Cuboids /home/octo/Desktop/ui/OpenGL_Cuboids /home/octo/Desktop/ui/OpenGL_Cuboids/build /home/octo/Desktop/ui/OpenGL_Cuboids/build /home/octo/Desktop/ui/OpenGL_Cuboids/build/CMakeFiles/random_cuboid.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/random_cuboid.dir/depend

