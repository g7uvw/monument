# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = "/Applications/CMake 2.8-11.app/Contents/bin/cmake"

# The command to remove a file.
RM = "/Applications/CMake 2.8-11.app/Contents/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = "/Applications/CMake 2.8-11.app/Contents/bin/ccmake"

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/dm/scratch/monument/projects/hooke

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/dm/scratch/monument/projects/hooke/build

# Include any dependencies generated for this target.
include CMakeFiles/hooke.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hooke.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hooke.dir/flags.make

CMakeFiles/hooke.dir/serialib.cpp.o: CMakeFiles/hooke.dir/flags.make
CMakeFiles/hooke.dir/serialib.cpp.o: ../serialib.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/dm/scratch/monument/projects/hooke/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/hooke.dir/serialib.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/hooke.dir/serialib.cpp.o -c ../serialib.cpp

CMakeFiles/hooke.dir/serialib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hooke.dir/serialib.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E ../serialib.cpp > CMakeFiles/hooke.dir/serialib.cpp.i

CMakeFiles/hooke.dir/serialib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hooke.dir/serialib.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S ../serialib.cpp -o CMakeFiles/hooke.dir/serialib.cpp.s

CMakeFiles/hooke.dir/serialib.cpp.o.requires:
.PHONY : CMakeFiles/hooke.dir/serialib.cpp.o.requires

CMakeFiles/hooke.dir/serialib.cpp.o.provides: CMakeFiles/hooke.dir/serialib.cpp.o.requires
	$(MAKE) -f CMakeFiles/hooke.dir/build.make CMakeFiles/hooke.dir/serialib.cpp.o.provides.build
.PHONY : CMakeFiles/hooke.dir/serialib.cpp.o.provides

CMakeFiles/hooke.dir/serialib.cpp.o.provides.build: CMakeFiles/hooke.dir/serialib.cpp.o

CMakeFiles/hooke.dir/motor.cpp.o: CMakeFiles/hooke.dir/flags.make
CMakeFiles/hooke.dir/motor.cpp.o: ../motor.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/dm/scratch/monument/projects/hooke/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/hooke.dir/motor.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/hooke.dir/motor.cpp.o -c ../motor.cpp

CMakeFiles/hooke.dir/motor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hooke.dir/motor.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E ../motor.cpp > CMakeFiles/hooke.dir/motor.cpp.i

CMakeFiles/hooke.dir/motor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hooke.dir/motor.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S ../motor.cpp -o CMakeFiles/hooke.dir/motor.cpp.s

CMakeFiles/hooke.dir/motor.cpp.o.requires:
.PHONY : CMakeFiles/hooke.dir/motor.cpp.o.requires

CMakeFiles/hooke.dir/motor.cpp.o.provides: CMakeFiles/hooke.dir/motor.cpp.o.requires
	$(MAKE) -f CMakeFiles/hooke.dir/build.make CMakeFiles/hooke.dir/motor.cpp.o.provides.build
.PHONY : CMakeFiles/hooke.dir/motor.cpp.o.provides

CMakeFiles/hooke.dir/motor.cpp.o.provides.build: CMakeFiles/hooke.dir/motor.cpp.o

CMakeFiles/hooke.dir/main.cpp.o: CMakeFiles/hooke.dir/flags.make
CMakeFiles/hooke.dir/main.cpp.o: ../main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/dm/scratch/monument/projects/hooke/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/hooke.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/hooke.dir/main.cpp.o -c ../main.cpp

CMakeFiles/hooke.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hooke.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E ../main.cpp > CMakeFiles/hooke.dir/main.cpp.i

CMakeFiles/hooke.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hooke.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S ../main.cpp -o CMakeFiles/hooke.dir/main.cpp.s

CMakeFiles/hooke.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/hooke.dir/main.cpp.o.requires

CMakeFiles/hooke.dir/main.cpp.o.provides: CMakeFiles/hooke.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/hooke.dir/build.make CMakeFiles/hooke.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/hooke.dir/main.cpp.o.provides

CMakeFiles/hooke.dir/main.cpp.o.provides.build: CMakeFiles/hooke.dir/main.cpp.o

# Object files for target hooke
hooke_OBJECTS = \
"CMakeFiles/hooke.dir/serialib.cpp.o" \
"CMakeFiles/hooke.dir/motor.cpp.o" \
"CMakeFiles/hooke.dir/main.cpp.o"

# External object files for target hooke
hooke_EXTERNAL_OBJECTS =

hooke: CMakeFiles/hooke.dir/serialib.cpp.o
hooke: CMakeFiles/hooke.dir/motor.cpp.o
hooke: CMakeFiles/hooke.dir/main.cpp.o
hooke: CMakeFiles/hooke.dir/build.make
hooke: CMakeFiles/hooke.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable hooke"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hooke.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hooke.dir/build: hooke
.PHONY : CMakeFiles/hooke.dir/build

CMakeFiles/hooke.dir/requires: CMakeFiles/hooke.dir/serialib.cpp.o.requires
CMakeFiles/hooke.dir/requires: CMakeFiles/hooke.dir/motor.cpp.o.requires
CMakeFiles/hooke.dir/requires: CMakeFiles/hooke.dir/main.cpp.o.requires
.PHONY : CMakeFiles/hooke.dir/requires

CMakeFiles/hooke.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hooke.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hooke.dir/clean

CMakeFiles/hooke.dir/depend:
	cd /Users/dm/scratch/monument/projects/hooke/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/dm/scratch/monument/projects/hooke /Users/dm/scratch/monument/projects/hooke /Users/dm/scratch/monument/projects/hooke/build /Users/dm/scratch/monument/projects/hooke/build /Users/dm/scratch/monument/projects/hooke/build/CMakeFiles/hooke.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hooke.dir/depend

