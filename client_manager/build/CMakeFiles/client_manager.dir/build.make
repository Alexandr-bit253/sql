# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/yoda/c_projects/sql/client_manager

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yoda/c_projects/sql/client_manager/build

# Include any dependencies generated for this target.
include CMakeFiles/client_manager.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/client_manager.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/client_manager.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/client_manager.dir/flags.make

CMakeFiles/client_manager.dir/src/client_manager.cpp.o: CMakeFiles/client_manager.dir/flags.make
CMakeFiles/client_manager.dir/src/client_manager.cpp.o: /home/yoda/c_projects/sql/client_manager/src/client_manager.cpp
CMakeFiles/client_manager.dir/src/client_manager.cpp.o: CMakeFiles/client_manager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/yoda/c_projects/sql/client_manager/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/client_manager.dir/src/client_manager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client_manager.dir/src/client_manager.cpp.o -MF CMakeFiles/client_manager.dir/src/client_manager.cpp.o.d -o CMakeFiles/client_manager.dir/src/client_manager.cpp.o -c /home/yoda/c_projects/sql/client_manager/src/client_manager.cpp

CMakeFiles/client_manager.dir/src/client_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/client_manager.dir/src/client_manager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yoda/c_projects/sql/client_manager/src/client_manager.cpp > CMakeFiles/client_manager.dir/src/client_manager.cpp.i

CMakeFiles/client_manager.dir/src/client_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/client_manager.dir/src/client_manager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yoda/c_projects/sql/client_manager/src/client_manager.cpp -o CMakeFiles/client_manager.dir/src/client_manager.cpp.s

# Object files for target client_manager
client_manager_OBJECTS = \
"CMakeFiles/client_manager.dir/src/client_manager.cpp.o"

# External object files for target client_manager
client_manager_EXTERNAL_OBJECTS =

libclient_manager.so: CMakeFiles/client_manager.dir/src/client_manager.cpp.o
libclient_manager.so: CMakeFiles/client_manager.dir/build.make
libclient_manager.so: /usr/lib/x86_64-linux-gnu/libpq.so
libclient_manager.so: CMakeFiles/client_manager.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/yoda/c_projects/sql/client_manager/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libclient_manager.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client_manager.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/client_manager.dir/build: libclient_manager.so
.PHONY : CMakeFiles/client_manager.dir/build

CMakeFiles/client_manager.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/client_manager.dir/cmake_clean.cmake
.PHONY : CMakeFiles/client_manager.dir/clean

CMakeFiles/client_manager.dir/depend:
	cd /home/yoda/c_projects/sql/client_manager/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yoda/c_projects/sql/client_manager /home/yoda/c_projects/sql/client_manager /home/yoda/c_projects/sql/client_manager/build /home/yoda/c_projects/sql/client_manager/build /home/yoda/c_projects/sql/client_manager/build/CMakeFiles/client_manager.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/client_manager.dir/depend

