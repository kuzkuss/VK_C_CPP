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
CMAKE_SOURCE_DIR = /home/anastasia/tp_c_cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anastasia/tp_c_cpp/build

# Include any dependencies generated for this target.
include project/posts_lib/CMakeFiles/posts_lib.dir/depend.make

# Include the progress variables for this target.
include project/posts_lib/CMakeFiles/posts_lib.dir/progress.make

# Include the compile flags for this target's objects.
include project/posts_lib/CMakeFiles/posts_lib.dir/flags.make

project/posts_lib/CMakeFiles/posts_lib.dir/src/post.c.o: project/posts_lib/CMakeFiles/posts_lib.dir/flags.make
project/posts_lib/CMakeFiles/posts_lib.dir/src/post.c.o: ../project/posts_lib/src/post.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anastasia/tp_c_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object project/posts_lib/CMakeFiles/posts_lib.dir/src/post.c.o"
	cd /home/anastasia/tp_c_cpp/build/project/posts_lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/posts_lib.dir/src/post.c.o   -c /home/anastasia/tp_c_cpp/project/posts_lib/src/post.c

project/posts_lib/CMakeFiles/posts_lib.dir/src/post.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/posts_lib.dir/src/post.c.i"
	cd /home/anastasia/tp_c_cpp/build/project/posts_lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/anastasia/tp_c_cpp/project/posts_lib/src/post.c > CMakeFiles/posts_lib.dir/src/post.c.i

project/posts_lib/CMakeFiles/posts_lib.dir/src/post.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/posts_lib.dir/src/post.c.s"
	cd /home/anastasia/tp_c_cpp/build/project/posts_lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/anastasia/tp_c_cpp/project/posts_lib/src/post.c -o CMakeFiles/posts_lib.dir/src/post.c.s

project/posts_lib/CMakeFiles/posts_lib.dir/src/posts_array.c.o: project/posts_lib/CMakeFiles/posts_lib.dir/flags.make
project/posts_lib/CMakeFiles/posts_lib.dir/src/posts_array.c.o: ../project/posts_lib/src/posts_array.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anastasia/tp_c_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object project/posts_lib/CMakeFiles/posts_lib.dir/src/posts_array.c.o"
	cd /home/anastasia/tp_c_cpp/build/project/posts_lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/posts_lib.dir/src/posts_array.c.o   -c /home/anastasia/tp_c_cpp/project/posts_lib/src/posts_array.c

project/posts_lib/CMakeFiles/posts_lib.dir/src/posts_array.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/posts_lib.dir/src/posts_array.c.i"
	cd /home/anastasia/tp_c_cpp/build/project/posts_lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/anastasia/tp_c_cpp/project/posts_lib/src/posts_array.c > CMakeFiles/posts_lib.dir/src/posts_array.c.i

project/posts_lib/CMakeFiles/posts_lib.dir/src/posts_array.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/posts_lib.dir/src/posts_array.c.s"
	cd /home/anastasia/tp_c_cpp/build/project/posts_lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/anastasia/tp_c_cpp/project/posts_lib/src/posts_array.c -o CMakeFiles/posts_lib.dir/src/posts_array.c.s

project/posts_lib/CMakeFiles/posts_lib.dir/src/return_codes.c.o: project/posts_lib/CMakeFiles/posts_lib.dir/flags.make
project/posts_lib/CMakeFiles/posts_lib.dir/src/return_codes.c.o: ../project/posts_lib/src/return_codes.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anastasia/tp_c_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object project/posts_lib/CMakeFiles/posts_lib.dir/src/return_codes.c.o"
	cd /home/anastasia/tp_c_cpp/build/project/posts_lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/posts_lib.dir/src/return_codes.c.o   -c /home/anastasia/tp_c_cpp/project/posts_lib/src/return_codes.c

project/posts_lib/CMakeFiles/posts_lib.dir/src/return_codes.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/posts_lib.dir/src/return_codes.c.i"
	cd /home/anastasia/tp_c_cpp/build/project/posts_lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/anastasia/tp_c_cpp/project/posts_lib/src/return_codes.c > CMakeFiles/posts_lib.dir/src/return_codes.c.i

project/posts_lib/CMakeFiles/posts_lib.dir/src/return_codes.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/posts_lib.dir/src/return_codes.c.s"
	cd /home/anastasia/tp_c_cpp/build/project/posts_lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/anastasia/tp_c_cpp/project/posts_lib/src/return_codes.c -o CMakeFiles/posts_lib.dir/src/return_codes.c.s

project/posts_lib/CMakeFiles/posts_lib.dir/src/count/sequential_count.c.o: project/posts_lib/CMakeFiles/posts_lib.dir/flags.make
project/posts_lib/CMakeFiles/posts_lib.dir/src/count/sequential_count.c.o: ../project/posts_lib/src/count/sequential_count.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anastasia/tp_c_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object project/posts_lib/CMakeFiles/posts_lib.dir/src/count/sequential_count.c.o"
	cd /home/anastasia/tp_c_cpp/build/project/posts_lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/posts_lib.dir/src/count/sequential_count.c.o   -c /home/anastasia/tp_c_cpp/project/posts_lib/src/count/sequential_count.c

project/posts_lib/CMakeFiles/posts_lib.dir/src/count/sequential_count.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/posts_lib.dir/src/count/sequential_count.c.i"
	cd /home/anastasia/tp_c_cpp/build/project/posts_lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/anastasia/tp_c_cpp/project/posts_lib/src/count/sequential_count.c > CMakeFiles/posts_lib.dir/src/count/sequential_count.c.i

project/posts_lib/CMakeFiles/posts_lib.dir/src/count/sequential_count.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/posts_lib.dir/src/count/sequential_count.c.s"
	cd /home/anastasia/tp_c_cpp/build/project/posts_lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/anastasia/tp_c_cpp/project/posts_lib/src/count/sequential_count.c -o CMakeFiles/posts_lib.dir/src/count/sequential_count.c.s

# Object files for target posts_lib
posts_lib_OBJECTS = \
"CMakeFiles/posts_lib.dir/src/post.c.o" \
"CMakeFiles/posts_lib.dir/src/posts_array.c.o" \
"CMakeFiles/posts_lib.dir/src/return_codes.c.o" \
"CMakeFiles/posts_lib.dir/src/count/sequential_count.c.o"

# External object files for target posts_lib
posts_lib_EXTERNAL_OBJECTS =

project/posts_lib/libposts_lib.a: project/posts_lib/CMakeFiles/posts_lib.dir/src/post.c.o
project/posts_lib/libposts_lib.a: project/posts_lib/CMakeFiles/posts_lib.dir/src/posts_array.c.o
project/posts_lib/libposts_lib.a: project/posts_lib/CMakeFiles/posts_lib.dir/src/return_codes.c.o
project/posts_lib/libposts_lib.a: project/posts_lib/CMakeFiles/posts_lib.dir/src/count/sequential_count.c.o
project/posts_lib/libposts_lib.a: project/posts_lib/CMakeFiles/posts_lib.dir/build.make
project/posts_lib/libposts_lib.a: project/posts_lib/CMakeFiles/posts_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anastasia/tp_c_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C static library libposts_lib.a"
	cd /home/anastasia/tp_c_cpp/build/project/posts_lib && $(CMAKE_COMMAND) -P CMakeFiles/posts_lib.dir/cmake_clean_target.cmake
	cd /home/anastasia/tp_c_cpp/build/project/posts_lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/posts_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
project/posts_lib/CMakeFiles/posts_lib.dir/build: project/posts_lib/libposts_lib.a

.PHONY : project/posts_lib/CMakeFiles/posts_lib.dir/build

project/posts_lib/CMakeFiles/posts_lib.dir/clean:
	cd /home/anastasia/tp_c_cpp/build/project/posts_lib && $(CMAKE_COMMAND) -P CMakeFiles/posts_lib.dir/cmake_clean.cmake
.PHONY : project/posts_lib/CMakeFiles/posts_lib.dir/clean

project/posts_lib/CMakeFiles/posts_lib.dir/depend:
	cd /home/anastasia/tp_c_cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anastasia/tp_c_cpp /home/anastasia/tp_c_cpp/project/posts_lib /home/anastasia/tp_c_cpp/build /home/anastasia/tp_c_cpp/build/project/posts_lib /home/anastasia/tp_c_cpp/build/project/posts_lib/CMakeFiles/posts_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : project/posts_lib/CMakeFiles/posts_lib.dir/depend

