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
CMAKE_SOURCE_DIR = /home/frederickampsup/Documents/complexia

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/frederickampsup/Documents/complexia

# Include any dependencies generated for this target.
include CMakeFiles/complexia.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/complexia.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/complexia.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/complexia.dir/flags.make

CMakeFiles/complexia.dir/utils/complexia_cli.c.o: CMakeFiles/complexia.dir/flags.make
CMakeFiles/complexia.dir/utils/complexia_cli.c.o: utils/complexia_cli.c
CMakeFiles/complexia.dir/utils/complexia_cli.c.o: CMakeFiles/complexia.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/frederickampsup/Documents/complexia/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/complexia.dir/utils/complexia_cli.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/complexia.dir/utils/complexia_cli.c.o -MF CMakeFiles/complexia.dir/utils/complexia_cli.c.o.d -o CMakeFiles/complexia.dir/utils/complexia_cli.c.o -c /home/frederickampsup/Documents/complexia/utils/complexia_cli.c

CMakeFiles/complexia.dir/utils/complexia_cli.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/complexia.dir/utils/complexia_cli.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/frederickampsup/Documents/complexia/utils/complexia_cli.c > CMakeFiles/complexia.dir/utils/complexia_cli.c.i

CMakeFiles/complexia.dir/utils/complexia_cli.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/complexia.dir/utils/complexia_cli.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/frederickampsup/Documents/complexia/utils/complexia_cli.c -o CMakeFiles/complexia.dir/utils/complexia_cli.c.s

CMakeFiles/complexia.dir/backend.c.o: CMakeFiles/complexia.dir/flags.make
CMakeFiles/complexia.dir/backend.c.o: backend.c
CMakeFiles/complexia.dir/backend.c.o: CMakeFiles/complexia.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/frederickampsup/Documents/complexia/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/complexia.dir/backend.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/complexia.dir/backend.c.o -MF CMakeFiles/complexia.dir/backend.c.o.d -o CMakeFiles/complexia.dir/backend.c.o -c /home/frederickampsup/Documents/complexia/backend.c

CMakeFiles/complexia.dir/backend.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/complexia.dir/backend.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/frederickampsup/Documents/complexia/backend.c > CMakeFiles/complexia.dir/backend.c.i

CMakeFiles/complexia.dir/backend.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/complexia.dir/backend.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/frederickampsup/Documents/complexia/backend.c -o CMakeFiles/complexia.dir/backend.c.s

# Object files for target complexia
complexia_OBJECTS = \
"CMakeFiles/complexia.dir/utils/complexia_cli.c.o" \
"CMakeFiles/complexia.dir/backend.c.o"

# External object files for target complexia
complexia_EXTERNAL_OBJECTS =

bin/complexia: CMakeFiles/complexia.dir/utils/complexia_cli.c.o
bin/complexia: CMakeFiles/complexia.dir/backend.c.o
bin/complexia: CMakeFiles/complexia.dir/build.make
bin/complexia: CMakeFiles/complexia.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/frederickampsup/Documents/complexia/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable bin/complexia"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/complexia.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/complexia.dir/build: bin/complexia
.PHONY : CMakeFiles/complexia.dir/build

CMakeFiles/complexia.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/complexia.dir/cmake_clean.cmake
.PHONY : CMakeFiles/complexia.dir/clean

CMakeFiles/complexia.dir/depend:
	cd /home/frederickampsup/Documents/complexia && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/frederickampsup/Documents/complexia /home/frederickampsup/Documents/complexia /home/frederickampsup/Documents/complexia /home/frederickampsup/Documents/complexia /home/frederickampsup/Documents/complexia/CMakeFiles/complexia.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/complexia.dir/depend
