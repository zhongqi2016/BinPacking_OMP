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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/wuzhongqi/CLionProjects/BinPacking_OMP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/wuzhongqi/CLionProjects/BinPacking_OMP/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/BinPacking_OMP.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/BinPacking_OMP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BinPacking_OMP.dir/flags.make

CMakeFiles/BinPacking_OMP.dir/main.cpp.o: CMakeFiles/BinPacking_OMP.dir/flags.make
CMakeFiles/BinPacking_OMP.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wuzhongqi/CLionProjects/BinPacking_OMP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/BinPacking_OMP.dir/main.cpp.o"
	/opt/homebrew/Cellar/gcc/11.1.0_1/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BinPacking_OMP.dir/main.cpp.o -c /Users/wuzhongqi/CLionProjects/BinPacking_OMP/main.cpp

CMakeFiles/BinPacking_OMP.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BinPacking_OMP.dir/main.cpp.i"
	/opt/homebrew/Cellar/gcc/11.1.0_1/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wuzhongqi/CLionProjects/BinPacking_OMP/main.cpp > CMakeFiles/BinPacking_OMP.dir/main.cpp.i

CMakeFiles/BinPacking_OMP.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BinPacking_OMP.dir/main.cpp.s"
	/opt/homebrew/Cellar/gcc/11.1.0_1/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wuzhongqi/CLionProjects/BinPacking_OMP/main.cpp -o CMakeFiles/BinPacking_OMP.dir/main.cpp.s

CMakeFiles/BinPacking_OMP.dir/LowerBound.cpp.o: CMakeFiles/BinPacking_OMP.dir/flags.make
CMakeFiles/BinPacking_OMP.dir/LowerBound.cpp.o: ../LowerBound.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wuzhongqi/CLionProjects/BinPacking_OMP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/BinPacking_OMP.dir/LowerBound.cpp.o"
	/opt/homebrew/Cellar/gcc/11.1.0_1/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BinPacking_OMP.dir/LowerBound.cpp.o -c /Users/wuzhongqi/CLionProjects/BinPacking_OMP/LowerBound.cpp

CMakeFiles/BinPacking_OMP.dir/LowerBound.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BinPacking_OMP.dir/LowerBound.cpp.i"
	/opt/homebrew/Cellar/gcc/11.1.0_1/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wuzhongqi/CLionProjects/BinPacking_OMP/LowerBound.cpp > CMakeFiles/BinPacking_OMP.dir/LowerBound.cpp.i

CMakeFiles/BinPacking_OMP.dir/LowerBound.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BinPacking_OMP.dir/LowerBound.cpp.s"
	/opt/homebrew/Cellar/gcc/11.1.0_1/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wuzhongqi/CLionProjects/BinPacking_OMP/LowerBound.cpp -o CMakeFiles/BinPacking_OMP.dir/LowerBound.cpp.s

CMakeFiles/BinPacking_OMP.dir/UpperBound.cpp.o: CMakeFiles/BinPacking_OMP.dir/flags.make
CMakeFiles/BinPacking_OMP.dir/UpperBound.cpp.o: ../UpperBound.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wuzhongqi/CLionProjects/BinPacking_OMP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/BinPacking_OMP.dir/UpperBound.cpp.o"
	/opt/homebrew/Cellar/gcc/11.1.0_1/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BinPacking_OMP.dir/UpperBound.cpp.o -c /Users/wuzhongqi/CLionProjects/BinPacking_OMP/UpperBound.cpp

CMakeFiles/BinPacking_OMP.dir/UpperBound.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BinPacking_OMP.dir/UpperBound.cpp.i"
	/opt/homebrew/Cellar/gcc/11.1.0_1/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wuzhongqi/CLionProjects/BinPacking_OMP/UpperBound.cpp > CMakeFiles/BinPacking_OMP.dir/UpperBound.cpp.i

CMakeFiles/BinPacking_OMP.dir/UpperBound.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BinPacking_OMP.dir/UpperBound.cpp.s"
	/opt/homebrew/Cellar/gcc/11.1.0_1/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wuzhongqi/CLionProjects/BinPacking_OMP/UpperBound.cpp -o CMakeFiles/BinPacking_OMP.dir/UpperBound.cpp.s

CMakeFiles/BinPacking_OMP.dir/DataInput.cpp.o: CMakeFiles/BinPacking_OMP.dir/flags.make
CMakeFiles/BinPacking_OMP.dir/DataInput.cpp.o: ../DataInput.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wuzhongqi/CLionProjects/BinPacking_OMP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/BinPacking_OMP.dir/DataInput.cpp.o"
	/opt/homebrew/Cellar/gcc/11.1.0_1/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BinPacking_OMP.dir/DataInput.cpp.o -c /Users/wuzhongqi/CLionProjects/BinPacking_OMP/DataInput.cpp

CMakeFiles/BinPacking_OMP.dir/DataInput.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BinPacking_OMP.dir/DataInput.cpp.i"
	/opt/homebrew/Cellar/gcc/11.1.0_1/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wuzhongqi/CLionProjects/BinPacking_OMP/DataInput.cpp > CMakeFiles/BinPacking_OMP.dir/DataInput.cpp.i

CMakeFiles/BinPacking_OMP.dir/DataInput.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BinPacking_OMP.dir/DataInput.cpp.s"
	/opt/homebrew/Cellar/gcc/11.1.0_1/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wuzhongqi/CLionProjects/BinPacking_OMP/DataInput.cpp -o CMakeFiles/BinPacking_OMP.dir/DataInput.cpp.s

CMakeFiles/BinPacking_OMP.dir/Algorithm.cpp.o: CMakeFiles/BinPacking_OMP.dir/flags.make
CMakeFiles/BinPacking_OMP.dir/Algorithm.cpp.o: ../Algorithm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wuzhongqi/CLionProjects/BinPacking_OMP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/BinPacking_OMP.dir/Algorithm.cpp.o"
	/opt/homebrew/Cellar/gcc/11.1.0_1/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BinPacking_OMP.dir/Algorithm.cpp.o -c /Users/wuzhongqi/CLionProjects/BinPacking_OMP/Algorithm.cpp

CMakeFiles/BinPacking_OMP.dir/Algorithm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BinPacking_OMP.dir/Algorithm.cpp.i"
	/opt/homebrew/Cellar/gcc/11.1.0_1/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wuzhongqi/CLionProjects/BinPacking_OMP/Algorithm.cpp > CMakeFiles/BinPacking_OMP.dir/Algorithm.cpp.i

CMakeFiles/BinPacking_OMP.dir/Algorithm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BinPacking_OMP.dir/Algorithm.cpp.s"
	/opt/homebrew/Cellar/gcc/11.1.0_1/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wuzhongqi/CLionProjects/BinPacking_OMP/Algorithm.cpp -o CMakeFiles/BinPacking_OMP.dir/Algorithm.cpp.s

CMakeFiles/BinPacking_OMP.dir/Bin.cpp.o: CMakeFiles/BinPacking_OMP.dir/flags.make
CMakeFiles/BinPacking_OMP.dir/Bin.cpp.o: ../Bin.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wuzhongqi/CLionProjects/BinPacking_OMP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/BinPacking_OMP.dir/Bin.cpp.o"
	/opt/homebrew/Cellar/gcc/11.1.0_1/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BinPacking_OMP.dir/Bin.cpp.o -c /Users/wuzhongqi/CLionProjects/BinPacking_OMP/Bin.cpp

CMakeFiles/BinPacking_OMP.dir/Bin.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BinPacking_OMP.dir/Bin.cpp.i"
	/opt/homebrew/Cellar/gcc/11.1.0_1/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wuzhongqi/CLionProjects/BinPacking_OMP/Bin.cpp > CMakeFiles/BinPacking_OMP.dir/Bin.cpp.i

CMakeFiles/BinPacking_OMP.dir/Bin.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BinPacking_OMP.dir/Bin.cpp.s"
	/opt/homebrew/Cellar/gcc/11.1.0_1/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wuzhongqi/CLionProjects/BinPacking_OMP/Bin.cpp -o CMakeFiles/BinPacking_OMP.dir/Bin.cpp.s

# Object files for target BinPacking_OMP
BinPacking_OMP_OBJECTS = \
"CMakeFiles/BinPacking_OMP.dir/main.cpp.o" \
"CMakeFiles/BinPacking_OMP.dir/LowerBound.cpp.o" \
"CMakeFiles/BinPacking_OMP.dir/UpperBound.cpp.o" \
"CMakeFiles/BinPacking_OMP.dir/DataInput.cpp.o" \
"CMakeFiles/BinPacking_OMP.dir/Algorithm.cpp.o" \
"CMakeFiles/BinPacking_OMP.dir/Bin.cpp.o"

# External object files for target BinPacking_OMP
BinPacking_OMP_EXTERNAL_OBJECTS =

BinPacking_OMP: CMakeFiles/BinPacking_OMP.dir/main.cpp.o
BinPacking_OMP: CMakeFiles/BinPacking_OMP.dir/LowerBound.cpp.o
BinPacking_OMP: CMakeFiles/BinPacking_OMP.dir/UpperBound.cpp.o
BinPacking_OMP: CMakeFiles/BinPacking_OMP.dir/DataInput.cpp.o
BinPacking_OMP: CMakeFiles/BinPacking_OMP.dir/Algorithm.cpp.o
BinPacking_OMP: CMakeFiles/BinPacking_OMP.dir/Bin.cpp.o
BinPacking_OMP: CMakeFiles/BinPacking_OMP.dir/build.make
BinPacking_OMP: CMakeFiles/BinPacking_OMP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/wuzhongqi/CLionProjects/BinPacking_OMP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable BinPacking_OMP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BinPacking_OMP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BinPacking_OMP.dir/build: BinPacking_OMP
.PHONY : CMakeFiles/BinPacking_OMP.dir/build

CMakeFiles/BinPacking_OMP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BinPacking_OMP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BinPacking_OMP.dir/clean

CMakeFiles/BinPacking_OMP.dir/depend:
	cd /Users/wuzhongqi/CLionProjects/BinPacking_OMP/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/wuzhongqi/CLionProjects/BinPacking_OMP /Users/wuzhongqi/CLionProjects/BinPacking_OMP /Users/wuzhongqi/CLionProjects/BinPacking_OMP/cmake-build-debug /Users/wuzhongqi/CLionProjects/BinPacking_OMP/cmake-build-debug /Users/wuzhongqi/CLionProjects/BinPacking_OMP/cmake-build-debug/CMakeFiles/BinPacking_OMP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BinPacking_OMP.dir/depend

