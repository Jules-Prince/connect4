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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.29.6/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.29.6/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/julesprince/GIT/DEV/connect4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/julesprince/GIT/DEV/connect4/build

# Include any dependencies generated for this target.
include CMakeFiles/connect4.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/connect4.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/connect4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/connect4.dir/flags.make

CMakeFiles/connect4.dir/src/main.cpp.o: CMakeFiles/connect4.dir/flags.make
CMakeFiles/connect4.dir/src/main.cpp.o: /Users/julesprince/GIT/DEV/connect4/src/main.cpp
CMakeFiles/connect4.dir/src/main.cpp.o: CMakeFiles/connect4.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/julesprince/GIT/DEV/connect4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/connect4.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/connect4.dir/src/main.cpp.o -MF CMakeFiles/connect4.dir/src/main.cpp.o.d -o CMakeFiles/connect4.dir/src/main.cpp.o -c /Users/julesprince/GIT/DEV/connect4/src/main.cpp

CMakeFiles/connect4.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/connect4.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/julesprince/GIT/DEV/connect4/src/main.cpp > CMakeFiles/connect4.dir/src/main.cpp.i

CMakeFiles/connect4.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/connect4.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/julesprince/GIT/DEV/connect4/src/main.cpp -o CMakeFiles/connect4.dir/src/main.cpp.s

# Object files for target connect4
connect4_OBJECTS = \
"CMakeFiles/connect4.dir/src/main.cpp.o"

# External object files for target connect4
connect4_EXTERNAL_OBJECTS =

connect4: CMakeFiles/connect4.dir/src/main.cpp.o
connect4: CMakeFiles/connect4.dir/build.make
connect4: _deps/raylib-build/raylib/libraylib.a
connect4: CMakeFiles/connect4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/julesprince/GIT/DEV/connect4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable connect4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/connect4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/connect4.dir/build: connect4
.PHONY : CMakeFiles/connect4.dir/build

CMakeFiles/connect4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/connect4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/connect4.dir/clean

CMakeFiles/connect4.dir/depend:
	cd /Users/julesprince/GIT/DEV/connect4/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/julesprince/GIT/DEV/connect4 /Users/julesprince/GIT/DEV/connect4 /Users/julesprince/GIT/DEV/connect4/build /Users/julesprince/GIT/DEV/connect4/build /Users/julesprince/GIT/DEV/connect4/build/CMakeFiles/connect4.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/connect4.dir/depend
