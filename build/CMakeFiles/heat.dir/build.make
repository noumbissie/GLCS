# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/noumbissie/GLCS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/noumbissie/GLCS/build

# Include any dependencies generated for this target.
include CMakeFiles/heat.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/heat.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/heat.dir/flags.make

CMakeFiles/heat.dir/heat.c.o: CMakeFiles/heat.dir/flags.make
CMakeFiles/heat.dir/heat.c.o: ../heat.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/noumbissie/GLCS/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/heat.dir/heat.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/heat.dir/heat.c.o   -c /home/noumbissie/GLCS/heat.c

CMakeFiles/heat.dir/heat.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/heat.dir/heat.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/noumbissie/GLCS/heat.c > CMakeFiles/heat.dir/heat.c.i

CMakeFiles/heat.dir/heat.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/heat.dir/heat.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/noumbissie/GLCS/heat.c -o CMakeFiles/heat.dir/heat.c.s

CMakeFiles/heat.dir/heat.c.o.requires:
.PHONY : CMakeFiles/heat.dir/heat.c.o.requires

CMakeFiles/heat.dir/heat.c.o.provides: CMakeFiles/heat.dir/heat.c.o.requires
	$(MAKE) -f CMakeFiles/heat.dir/build.make CMakeFiles/heat.dir/heat.c.o.provides.build
.PHONY : CMakeFiles/heat.dir/heat.c.o.provides

CMakeFiles/heat.dir/heat.c.o.provides.build: CMakeFiles/heat.dir/heat.c.o

# Object files for target heat
heat_OBJECTS = \
"CMakeFiles/heat.dir/heat.c.o"

# External object files for target heat
heat_EXTERNAL_OBJECTS =

heat: CMakeFiles/heat.dir/heat.c.o
heat: CMakeFiles/heat.dir/build.make
heat: /usr/local/mpich-3.2/lib/libmpi.so
heat: /usr/lib/i386-linux-gnu/libhdf5.so
heat: /usr/lib/i386-linux-gnu/libpthread.so
heat: /usr/lib/i386-linux-gnu/libz.so
heat: /usr/lib/i386-linux-gnu/libdl.so
heat: /usr/lib/i386-linux-gnu/libm.so
heat: CMakeFiles/heat.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable heat"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/heat.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/heat.dir/build: heat
.PHONY : CMakeFiles/heat.dir/build

CMakeFiles/heat.dir/requires: CMakeFiles/heat.dir/heat.c.o.requires
.PHONY : CMakeFiles/heat.dir/requires

CMakeFiles/heat.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/heat.dir/cmake_clean.cmake
.PHONY : CMakeFiles/heat.dir/clean

CMakeFiles/heat.dir/depend:
	cd /home/noumbissie/GLCS/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/noumbissie/GLCS /home/noumbissie/GLCS /home/noumbissie/GLCS/build /home/noumbissie/GLCS/build /home/noumbissie/GLCS/build/CMakeFiles/heat.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/heat.dir/depend

