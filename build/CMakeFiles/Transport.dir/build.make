# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_SOURCE_DIR = /home/robert/Labs/Transport

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/robert/Labs/Transport/build

# Include any dependencies generated for this target.
include CMakeFiles/Transport.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Transport.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Transport.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Transport.dir/flags.make

CMakeFiles/Transport.dir/Transport.cpp.o: CMakeFiles/Transport.dir/flags.make
CMakeFiles/Transport.dir/Transport.cpp.o: /home/robert/Labs/Transport/Transport.cpp
CMakeFiles/Transport.dir/Transport.cpp.o: CMakeFiles/Transport.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/robert/Labs/Transport/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Transport.dir/Transport.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Transport.dir/Transport.cpp.o -MF CMakeFiles/Transport.dir/Transport.cpp.o.d -o CMakeFiles/Transport.dir/Transport.cpp.o -c /home/robert/Labs/Transport/Transport.cpp

CMakeFiles/Transport.dir/Transport.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Transport.dir/Transport.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robert/Labs/Transport/Transport.cpp > CMakeFiles/Transport.dir/Transport.cpp.i

CMakeFiles/Transport.dir/Transport.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Transport.dir/Transport.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robert/Labs/Transport/Transport.cpp -o CMakeFiles/Transport.dir/Transport.cpp.s

# Object files for target Transport
Transport_OBJECTS = \
"CMakeFiles/Transport.dir/Transport.cpp.o"

# External object files for target Transport
Transport_EXTERNAL_OBJECTS =

Transport: CMakeFiles/Transport.dir/Transport.cpp.o
Transport: CMakeFiles/Transport.dir/build.make
Transport: /usr/lib/x86_64-linux-gnu/libcurl.so
Transport: CMakeFiles/Transport.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/robert/Labs/Transport/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Transport"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Transport.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Transport.dir/build: Transport
.PHONY : CMakeFiles/Transport.dir/build

CMakeFiles/Transport.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Transport.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Transport.dir/clean

CMakeFiles/Transport.dir/depend:
	cd /home/robert/Labs/Transport/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/robert/Labs/Transport /home/robert/Labs/Transport /home/robert/Labs/Transport/build /home/robert/Labs/Transport/build /home/robert/Labs/Transport/build/CMakeFiles/Transport.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Transport.dir/depend

