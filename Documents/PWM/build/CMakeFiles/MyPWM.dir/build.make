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
CMAKE_SOURCE_DIR = /home/ledat/Documents/PWM

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ledat/Documents/PWM/build

# Include any dependencies generated for this target.
include CMakeFiles/MyPWM.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MyPWM.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MyPWM.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyPWM.dir/flags.make

CMakeFiles/MyPWM.dir/main.c.o: CMakeFiles/MyPWM.dir/flags.make
CMakeFiles/MyPWM.dir/main.c.o: /home/ledat/Documents/PWM/main.c
CMakeFiles/MyPWM.dir/main.c.o: CMakeFiles/MyPWM.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ledat/Documents/PWM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/MyPWM.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MyPWM.dir/main.c.o -MF CMakeFiles/MyPWM.dir/main.c.o.d -o CMakeFiles/MyPWM.dir/main.c.o -c /home/ledat/Documents/PWM/main.c

CMakeFiles/MyPWM.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MyPWM.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ledat/Documents/PWM/main.c > CMakeFiles/MyPWM.dir/main.c.i

CMakeFiles/MyPWM.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MyPWM.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ledat/Documents/PWM/main.c -o CMakeFiles/MyPWM.dir/main.c.s

# Object files for target MyPWM
MyPWM_OBJECTS = \
"CMakeFiles/MyPWM.dir/main.c.o"

# External object files for target MyPWM
MyPWM_EXTERNAL_OBJECTS =

MyPWM: CMakeFiles/MyPWM.dir/main.c.o
MyPWM: CMakeFiles/MyPWM.dir/build.make
MyPWM: CMakeFiles/MyPWM.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ledat/Documents/PWM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable MyPWM"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyPWM.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyPWM.dir/build: MyPWM
.PHONY : CMakeFiles/MyPWM.dir/build

CMakeFiles/MyPWM.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyPWM.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyPWM.dir/clean

CMakeFiles/MyPWM.dir/depend:
	cd /home/ledat/Documents/PWM/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ledat/Documents/PWM /home/ledat/Documents/PWM /home/ledat/Documents/PWM/build /home/ledat/Documents/PWM/build /home/ledat/Documents/PWM/build/CMakeFiles/MyPWM.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MyPWM.dir/depend

