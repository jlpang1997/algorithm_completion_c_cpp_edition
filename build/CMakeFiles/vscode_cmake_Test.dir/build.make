# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\庞进林\source\cmake_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\庞进林\source\cmake_test\build

# Include any dependencies generated for this target.
include CMakeFiles/vscode_cmake_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/vscode_cmake_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/vscode_cmake_test.dir/flags.make

CMakeFiles/vscode_cmake_test.dir/Src/a.cpp.obj: CMakeFiles/vscode_cmake_test.dir/flags.make
CMakeFiles/vscode_cmake_test.dir/Src/a.cpp.obj: CMakeFiles/vscode_cmake_test.dir/includes_CXX.rsp
CMakeFiles/vscode_cmake_test.dir/Src/a.cpp.obj: ../Src/a.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\庞进林\source\cmake_test\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/vscode_cmake_test.dir/Src/a.cpp.obj"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\vscode_cmake_test.dir\Src\a.cpp.obj -c C:\Users\庞进林\source\cmake_test\Src\a.cpp

CMakeFiles/vscode_cmake_test.dir/Src/a.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vscode_cmake_test.dir/Src/a.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\庞进林\source\cmake_test\Src\a.cpp > CMakeFiles\vscode_cmake_test.dir\Src\a.cpp.i

CMakeFiles/vscode_cmake_test.dir/Src/a.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vscode_cmake_test.dir/Src/a.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\庞进林\source\cmake_test\Src\a.cpp -o CMakeFiles\vscode_cmake_test.dir\Src\a.cpp.s

CMakeFiles/vscode_cmake_test.dir/Src/b.cpp.obj: CMakeFiles/vscode_cmake_test.dir/flags.make
CMakeFiles/vscode_cmake_test.dir/Src/b.cpp.obj: CMakeFiles/vscode_cmake_test.dir/includes_CXX.rsp
CMakeFiles/vscode_cmake_test.dir/Src/b.cpp.obj: ../Src/b.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\庞进林\source\cmake_test\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/vscode_cmake_test.dir/Src/b.cpp.obj"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\vscode_cmake_test.dir\Src\b.cpp.obj -c C:\Users\庞进林\source\cmake_test\Src\b.cpp

CMakeFiles/vscode_cmake_test.dir/Src/b.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vscode_cmake_test.dir/Src/b.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\庞进林\source\cmake_test\Src\b.cpp > CMakeFiles\vscode_cmake_test.dir\Src\b.cpp.i

CMakeFiles/vscode_cmake_test.dir/Src/b.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vscode_cmake_test.dir/Src/b.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\庞进林\source\cmake_test\Src\b.cpp -o CMakeFiles\vscode_cmake_test.dir\Src\b.cpp.s

CMakeFiles/vscode_cmake_test.dir/Src/make.cpp.obj: CMakeFiles/vscode_cmake_test.dir/flags.make
CMakeFiles/vscode_cmake_test.dir/Src/make.cpp.obj: CMakeFiles/vscode_cmake_test.dir/includes_CXX.rsp
CMakeFiles/vscode_cmake_test.dir/Src/make.cpp.obj: ../Src/make.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\庞进林\source\cmake_test\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/vscode_cmake_test.dir/Src/make.cpp.obj"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\vscode_cmake_test.dir\Src\make.cpp.obj -c C:\Users\庞进林\source\cmake_test\Src\make.cpp

CMakeFiles/vscode_cmake_test.dir/Src/make.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vscode_cmake_test.dir/Src/make.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\庞进林\source\cmake_test\Src\make.cpp > CMakeFiles\vscode_cmake_test.dir\Src\make.cpp.i

CMakeFiles/vscode_cmake_test.dir/Src/make.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vscode_cmake_test.dir/Src/make.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\庞进林\source\cmake_test\Src\make.cpp -o CMakeFiles\vscode_cmake_test.dir\Src\make.cpp.s

# Object files for target vscode_cmake_test
vscode_cmake_test_OBJECTS = \
"CMakeFiles/vscode_cmake_test.dir/Src/a.cpp.obj" \
"CMakeFiles/vscode_cmake_test.dir/Src/b.cpp.obj" \
"CMakeFiles/vscode_cmake_test.dir/Src/make.cpp.obj"

# External object files for target vscode_cmake_test
vscode_cmake_test_EXTERNAL_OBJECTS =

../bin/vscode_cmake_test.exe: CMakeFiles/vscode_cmake_test.dir/Src/a.cpp.obj
../bin/vscode_cmake_test.exe: CMakeFiles/vscode_cmake_test.dir/Src/b.cpp.obj
../bin/vscode_cmake_test.exe: CMakeFiles/vscode_cmake_test.dir/Src/make.cpp.obj
../bin/vscode_cmake_test.exe: CMakeFiles/vscode_cmake_test.dir/build.make
../bin/vscode_cmake_test.exe: CMakeFiles/vscode_cmake_test.dir/linklibs.rsp
../bin/vscode_cmake_test.exe: CMakeFiles/vscode_cmake_test.dir/objects1.rsp
../bin/vscode_cmake_test.exe: CMakeFiles/vscode_cmake_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\庞进林\source\cmake_test\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ..\bin\vscode_cmake_test.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\vscode_cmake_test.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/vscode_cmake_test.dir/build: ../bin/vscode_cmake_test.exe

.PHONY : CMakeFiles/vscode_cmake_test.dir/build

CMakeFiles/vscode_cmake_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\vscode_cmake_test.dir\cmake_clean.cmake
.PHONY : CMakeFiles/vscode_cmake_test.dir/clean

CMakeFiles/vscode_cmake_test.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\庞进林\source\cmake_test C:\Users\庞进林\source\cmake_test C:\Users\庞进林\source\cmake_test\build C:\Users\庞进林\source\cmake_test\build C:\Users\庞进林\source\cmake_test\build\CMakeFiles\vscode_cmake_Test.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/vscode_cmake_test.dir/depend
