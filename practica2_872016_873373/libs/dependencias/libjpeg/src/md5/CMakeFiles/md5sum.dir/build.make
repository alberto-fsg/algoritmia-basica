# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_SOURCE_DIR = /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg

# Include any dependencies generated for this target.
include src/md5/CMakeFiles/md5sum.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/md5/CMakeFiles/md5sum.dir/compiler_depend.make

# Include the progress variables for this target.
include src/md5/CMakeFiles/md5sum.dir/progress.make

# Include the compile flags for this target's objects.
include src/md5/CMakeFiles/md5sum.dir/flags.make

src/md5/CMakeFiles/md5sum.dir/md5sum.c.o: src/md5/CMakeFiles/md5sum.dir/flags.make
src/md5/CMakeFiles/md5sum.dir/md5sum.c.o: src/md5/md5sum.c
src/md5/CMakeFiles/md5sum.dir/md5sum.c.o: src/md5/CMakeFiles/md5sum.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/md5/CMakeFiles/md5sum.dir/md5sum.c.o"
	cd /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/src/md5 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/md5/CMakeFiles/md5sum.dir/md5sum.c.o -MF CMakeFiles/md5sum.dir/md5sum.c.o.d -o CMakeFiles/md5sum.dir/md5sum.c.o -c /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/src/md5/md5sum.c

src/md5/CMakeFiles/md5sum.dir/md5sum.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/md5sum.dir/md5sum.c.i"
	cd /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/src/md5 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/src/md5/md5sum.c > CMakeFiles/md5sum.dir/md5sum.c.i

src/md5/CMakeFiles/md5sum.dir/md5sum.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/md5sum.dir/md5sum.c.s"
	cd /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/src/md5 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/src/md5/md5sum.c -o CMakeFiles/md5sum.dir/md5sum.c.s

src/md5/CMakeFiles/md5sum.dir/md5.c.o: src/md5/CMakeFiles/md5sum.dir/flags.make
src/md5/CMakeFiles/md5sum.dir/md5.c.o: src/md5/md5.c
src/md5/CMakeFiles/md5sum.dir/md5.c.o: src/md5/CMakeFiles/md5sum.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/md5/CMakeFiles/md5sum.dir/md5.c.o"
	cd /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/src/md5 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/md5/CMakeFiles/md5sum.dir/md5.c.o -MF CMakeFiles/md5sum.dir/md5.c.o.d -o CMakeFiles/md5sum.dir/md5.c.o -c /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/src/md5/md5.c

src/md5/CMakeFiles/md5sum.dir/md5.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/md5sum.dir/md5.c.i"
	cd /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/src/md5 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/src/md5/md5.c > CMakeFiles/md5sum.dir/md5.c.i

src/md5/CMakeFiles/md5sum.dir/md5.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/md5sum.dir/md5.c.s"
	cd /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/src/md5 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/src/md5/md5.c -o CMakeFiles/md5sum.dir/md5.c.s

src/md5/CMakeFiles/md5sum.dir/md5hl.c.o: src/md5/CMakeFiles/md5sum.dir/flags.make
src/md5/CMakeFiles/md5sum.dir/md5hl.c.o: src/md5/md5hl.c
src/md5/CMakeFiles/md5sum.dir/md5hl.c.o: src/md5/CMakeFiles/md5sum.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/md5/CMakeFiles/md5sum.dir/md5hl.c.o"
	cd /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/src/md5 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/md5/CMakeFiles/md5sum.dir/md5hl.c.o -MF CMakeFiles/md5sum.dir/md5hl.c.o.d -o CMakeFiles/md5sum.dir/md5hl.c.o -c /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/src/md5/md5hl.c

src/md5/CMakeFiles/md5sum.dir/md5hl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/md5sum.dir/md5hl.c.i"
	cd /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/src/md5 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/src/md5/md5hl.c > CMakeFiles/md5sum.dir/md5hl.c.i

src/md5/CMakeFiles/md5sum.dir/md5hl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/md5sum.dir/md5hl.c.s"
	cd /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/src/md5 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/src/md5/md5hl.c -o CMakeFiles/md5sum.dir/md5hl.c.s

# Object files for target md5sum
md5sum_OBJECTS = \
"CMakeFiles/md5sum.dir/md5sum.c.o" \
"CMakeFiles/md5sum.dir/md5.c.o" \
"CMakeFiles/md5sum.dir/md5hl.c.o"

# External object files for target md5sum
md5sum_EXTERNAL_OBJECTS =

test/md5sum: src/md5/CMakeFiles/md5sum.dir/md5sum.c.o
test/md5sum: src/md5/CMakeFiles/md5sum.dir/md5.c.o
test/md5sum: src/md5/CMakeFiles/md5sum.dir/md5hl.c.o
test/md5sum: src/md5/CMakeFiles/md5sum.dir/build.make
test/md5sum: src/md5/CMakeFiles/md5sum.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable ../../test/md5sum"
	cd /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/src/md5 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/md5sum.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/md5/CMakeFiles/md5sum.dir/build: test/md5sum
.PHONY : src/md5/CMakeFiles/md5sum.dir/build

src/md5/CMakeFiles/md5sum.dir/clean:
	cd /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/src/md5 && $(CMAKE_COMMAND) -P CMakeFiles/md5sum.dir/cmake_clean.cmake
.PHONY : src/md5/CMakeFiles/md5sum.dir/clean

src/md5/CMakeFiles/md5sum.dir/depend:
	cd /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/src/md5 /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/src/md5 /home/a872016/algoritmia_basica/practica2_872016_873373/libs/dependencias/libjpeg/src/md5/CMakeFiles/md5sum.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/md5/CMakeFiles/md5sum.dir/depend

