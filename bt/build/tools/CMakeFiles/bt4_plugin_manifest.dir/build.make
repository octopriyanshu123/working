# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /media/octo/d73e6bae-15cd-4017-98c3-0eb873ce5396/home/octo/Desktop/bt/BehaviorTree.CPP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/octo/d73e6bae-15cd-4017-98c3-0eb873ce5396/home/octo/Desktop/bt/build

# Include any dependencies generated for this target.
include tools/CMakeFiles/bt4_plugin_manifest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tools/CMakeFiles/bt4_plugin_manifest.dir/compiler_depend.make

# Include the progress variables for this target.
include tools/CMakeFiles/bt4_plugin_manifest.dir/progress.make

# Include the compile flags for this target's objects.
include tools/CMakeFiles/bt4_plugin_manifest.dir/flags.make

tools/CMakeFiles/bt4_plugin_manifest.dir/bt_plugin_manifest.cpp.o: tools/CMakeFiles/bt4_plugin_manifest.dir/flags.make
tools/CMakeFiles/bt4_plugin_manifest.dir/bt_plugin_manifest.cpp.o: /media/octo/d73e6bae-15cd-4017-98c3-0eb873ce5396/home/octo/Desktop/bt/BehaviorTree.CPP/tools/bt_plugin_manifest.cpp
tools/CMakeFiles/bt4_plugin_manifest.dir/bt_plugin_manifest.cpp.o: tools/CMakeFiles/bt4_plugin_manifest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/octo/d73e6bae-15cd-4017-98c3-0eb873ce5396/home/octo/Desktop/bt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tools/CMakeFiles/bt4_plugin_manifest.dir/bt_plugin_manifest.cpp.o"
	cd /media/octo/d73e6bae-15cd-4017-98c3-0eb873ce5396/home/octo/Desktop/bt/build/tools && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tools/CMakeFiles/bt4_plugin_manifest.dir/bt_plugin_manifest.cpp.o -MF CMakeFiles/bt4_plugin_manifest.dir/bt_plugin_manifest.cpp.o.d -o CMakeFiles/bt4_plugin_manifest.dir/bt_plugin_manifest.cpp.o -c /media/octo/d73e6bae-15cd-4017-98c3-0eb873ce5396/home/octo/Desktop/bt/BehaviorTree.CPP/tools/bt_plugin_manifest.cpp

tools/CMakeFiles/bt4_plugin_manifest.dir/bt_plugin_manifest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bt4_plugin_manifest.dir/bt_plugin_manifest.cpp.i"
	cd /media/octo/d73e6bae-15cd-4017-98c3-0eb873ce5396/home/octo/Desktop/bt/build/tools && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/octo/d73e6bae-15cd-4017-98c3-0eb873ce5396/home/octo/Desktop/bt/BehaviorTree.CPP/tools/bt_plugin_manifest.cpp > CMakeFiles/bt4_plugin_manifest.dir/bt_plugin_manifest.cpp.i

tools/CMakeFiles/bt4_plugin_manifest.dir/bt_plugin_manifest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bt4_plugin_manifest.dir/bt_plugin_manifest.cpp.s"
	cd /media/octo/d73e6bae-15cd-4017-98c3-0eb873ce5396/home/octo/Desktop/bt/build/tools && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/octo/d73e6bae-15cd-4017-98c3-0eb873ce5396/home/octo/Desktop/bt/BehaviorTree.CPP/tools/bt_plugin_manifest.cpp -o CMakeFiles/bt4_plugin_manifest.dir/bt_plugin_manifest.cpp.s

# Object files for target bt4_plugin_manifest
bt4_plugin_manifest_OBJECTS = \
"CMakeFiles/bt4_plugin_manifest.dir/bt_plugin_manifest.cpp.o"

# External object files for target bt4_plugin_manifest
bt4_plugin_manifest_EXTERNAL_OBJECTS =

tools/bt4_plugin_manifest: tools/CMakeFiles/bt4_plugin_manifest.dir/bt_plugin_manifest.cpp.o
tools/bt4_plugin_manifest: tools/CMakeFiles/bt4_plugin_manifest.dir/build.make
tools/bt4_plugin_manifest: libbehaviortree_cpp.so
tools/bt4_plugin_manifest: /usr/lib/x86_64-linux-gnu/libzmq.so
tools/bt4_plugin_manifest: /usr/lib/x86_64-linux-gnu/libsqlite3.so
tools/bt4_plugin_manifest: tools/CMakeFiles/bt4_plugin_manifest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/octo/d73e6bae-15cd-4017-98c3-0eb873ce5396/home/octo/Desktop/bt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bt4_plugin_manifest"
	cd /media/octo/d73e6bae-15cd-4017-98c3-0eb873ce5396/home/octo/Desktop/bt/build/tools && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bt4_plugin_manifest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tools/CMakeFiles/bt4_plugin_manifest.dir/build: tools/bt4_plugin_manifest
.PHONY : tools/CMakeFiles/bt4_plugin_manifest.dir/build

tools/CMakeFiles/bt4_plugin_manifest.dir/clean:
	cd /media/octo/d73e6bae-15cd-4017-98c3-0eb873ce5396/home/octo/Desktop/bt/build/tools && $(CMAKE_COMMAND) -P CMakeFiles/bt4_plugin_manifest.dir/cmake_clean.cmake
.PHONY : tools/CMakeFiles/bt4_plugin_manifest.dir/clean

tools/CMakeFiles/bt4_plugin_manifest.dir/depend:
	cd /media/octo/d73e6bae-15cd-4017-98c3-0eb873ce5396/home/octo/Desktop/bt/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/octo/d73e6bae-15cd-4017-98c3-0eb873ce5396/home/octo/Desktop/bt/BehaviorTree.CPP /media/octo/d73e6bae-15cd-4017-98c3-0eb873ce5396/home/octo/Desktop/bt/BehaviorTree.CPP/tools /media/octo/d73e6bae-15cd-4017-98c3-0eb873ce5396/home/octo/Desktop/bt/build /media/octo/d73e6bae-15cd-4017-98c3-0eb873ce5396/home/octo/Desktop/bt/build/tools /media/octo/d73e6bae-15cd-4017-98c3-0eb873ce5396/home/octo/Desktop/bt/build/tools/CMakeFiles/bt4_plugin_manifest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tools/CMakeFiles/bt4_plugin_manifest.dir/depend

