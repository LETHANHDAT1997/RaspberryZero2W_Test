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
CMAKE_SOURCE_DIR = /home/ledat/Documents/SPI

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ledat/Documents/SPI/build

# Include any dependencies generated for this target.
include CMakeFiles/MySPI.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MySPI.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MySPI.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MySPI.dir/flags.make

CMakeFiles/MySPI.dir/main.c.o: CMakeFiles/MySPI.dir/flags.make
CMakeFiles/MySPI.dir/main.c.o: /home/ledat/Documents/SPI/main.c
CMakeFiles/MySPI.dir/main.c.o: CMakeFiles/MySPI.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ledat/Documents/SPI/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/MySPI.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MySPI.dir/main.c.o -MF CMakeFiles/MySPI.dir/main.c.o.d -o CMakeFiles/MySPI.dir/main.c.o -c /home/ledat/Documents/SPI/main.c

CMakeFiles/MySPI.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MySPI.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ledat/Documents/SPI/main.c > CMakeFiles/MySPI.dir/main.c.i

CMakeFiles/MySPI.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MySPI.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ledat/Documents/SPI/main.c -o CMakeFiles/MySPI.dir/main.c.s

# Object files for target MySPI
MySPI_OBJECTS = \
"CMakeFiles/MySPI.dir/main.c.o"

# External object files for target MySPI
MySPI_EXTERNAL_OBJECTS =

MySPI: CMakeFiles/MySPI.dir/main.c.o
MySPI: CMakeFiles/MySPI.dir/build.make
MySPI: CMakeFiles/MySPI.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ledat/Documents/SPI/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable MySPI"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MySPI.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MySPI.dir/build: MySPI
.PHONY : CMakeFiles/MySPI.dir/build

CMakeFiles/MySPI.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MySPI.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MySPI.dir/clean

CMakeFiles/MySPI.dir/depend:
	cd /home/ledat/Documents/SPI/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ledat/Documents/SPI /home/ledat/Documents/SPI /home/ledat/Documents/SPI/build /home/ledat/Documents/SPI/build /home/ledat/Documents/SPI/build/CMakeFiles/MySPI.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MySPI.dir/depend

