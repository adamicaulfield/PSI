# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ac7717/Documents/PSI/HE/PSI

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ac7717/Documents/PSI/HE/PSI

# Include any dependencies generated for this target.
include CMakeFiles/Project1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Project1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Project1.dir/flags.make

CMakeFiles/Project1.dir/main.cpp.o: CMakeFiles/Project1.dir/flags.make
CMakeFiles/Project1.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ac7717/Documents/PSI/HE/PSI/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Project1.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project1.dir/main.cpp.o -c /home/ac7717/Documents/PSI/HE/PSI/main.cpp

CMakeFiles/Project1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project1.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ac7717/Documents/PSI/HE/PSI/main.cpp > CMakeFiles/Project1.dir/main.cpp.i

CMakeFiles/Project1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project1.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ac7717/Documents/PSI/HE/PSI/main.cpp -o CMakeFiles/Project1.dir/main.cpp.s

CMakeFiles/Project1.dir/Encryptor.cpp.o: CMakeFiles/Project1.dir/flags.make
CMakeFiles/Project1.dir/Encryptor.cpp.o: Encryptor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ac7717/Documents/PSI/HE/PSI/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Project1.dir/Encryptor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project1.dir/Encryptor.cpp.o -c /home/ac7717/Documents/PSI/HE/PSI/Encryptor.cpp

CMakeFiles/Project1.dir/Encryptor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project1.dir/Encryptor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ac7717/Documents/PSI/HE/PSI/Encryptor.cpp > CMakeFiles/Project1.dir/Encryptor.cpp.i

CMakeFiles/Project1.dir/Encryptor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project1.dir/Encryptor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ac7717/Documents/PSI/HE/PSI/Encryptor.cpp -o CMakeFiles/Project1.dir/Encryptor.cpp.s

CMakeFiles/Project1.dir/FileSystem.cpp.o: CMakeFiles/Project1.dir/flags.make
CMakeFiles/Project1.dir/FileSystem.cpp.o: FileSystem.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ac7717/Documents/PSI/HE/PSI/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Project1.dir/FileSystem.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project1.dir/FileSystem.cpp.o -c /home/ac7717/Documents/PSI/HE/PSI/FileSystem.cpp

CMakeFiles/Project1.dir/FileSystem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project1.dir/FileSystem.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ac7717/Documents/PSI/HE/PSI/FileSystem.cpp > CMakeFiles/Project1.dir/FileSystem.cpp.i

CMakeFiles/Project1.dir/FileSystem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project1.dir/FileSystem.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ac7717/Documents/PSI/HE/PSI/FileSystem.cpp -o CMakeFiles/Project1.dir/FileSystem.cpp.s

CMakeFiles/Project1.dir/Util.cpp.o: CMakeFiles/Project1.dir/flags.make
CMakeFiles/Project1.dir/Util.cpp.o: Util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ac7717/Documents/PSI/HE/PSI/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Project1.dir/Util.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project1.dir/Util.cpp.o -c /home/ac7717/Documents/PSI/HE/PSI/Util.cpp

CMakeFiles/Project1.dir/Util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project1.dir/Util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ac7717/Documents/PSI/HE/PSI/Util.cpp > CMakeFiles/Project1.dir/Util.cpp.i

CMakeFiles/Project1.dir/Util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project1.dir/Util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ac7717/Documents/PSI/HE/PSI/Util.cpp -o CMakeFiles/Project1.dir/Util.cpp.s

CMakeFiles/Project1.dir/BasicExamples.cpp.o: CMakeFiles/Project1.dir/flags.make
CMakeFiles/Project1.dir/BasicExamples.cpp.o: BasicExamples.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ac7717/Documents/PSI/HE/PSI/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Project1.dir/BasicExamples.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project1.dir/BasicExamples.cpp.o -c /home/ac7717/Documents/PSI/HE/PSI/BasicExamples.cpp

CMakeFiles/Project1.dir/BasicExamples.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project1.dir/BasicExamples.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ac7717/Documents/PSI/HE/PSI/BasicExamples.cpp > CMakeFiles/Project1.dir/BasicExamples.cpp.i

CMakeFiles/Project1.dir/BasicExamples.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project1.dir/BasicExamples.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ac7717/Documents/PSI/HE/PSI/BasicExamples.cpp -o CMakeFiles/Project1.dir/BasicExamples.cpp.s

CMakeFiles/Project1.dir/Calculator.cpp.o: CMakeFiles/Project1.dir/flags.make
CMakeFiles/Project1.dir/Calculator.cpp.o: Calculator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ac7717/Documents/PSI/HE/PSI/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Project1.dir/Calculator.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project1.dir/Calculator.cpp.o -c /home/ac7717/Documents/PSI/HE/PSI/Calculator.cpp

CMakeFiles/Project1.dir/Calculator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project1.dir/Calculator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ac7717/Documents/PSI/HE/PSI/Calculator.cpp > CMakeFiles/Project1.dir/Calculator.cpp.i

CMakeFiles/Project1.dir/Calculator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project1.dir/Calculator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ac7717/Documents/PSI/HE/PSI/Calculator.cpp -o CMakeFiles/Project1.dir/Calculator.cpp.s

CMakeFiles/Project1.dir/Vector.cpp.o: CMakeFiles/Project1.dir/flags.make
CMakeFiles/Project1.dir/Vector.cpp.o: Vector.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ac7717/Documents/PSI/HE/PSI/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Project1.dir/Vector.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project1.dir/Vector.cpp.o -c /home/ac7717/Documents/PSI/HE/PSI/Vector.cpp

CMakeFiles/Project1.dir/Vector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project1.dir/Vector.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ac7717/Documents/PSI/HE/PSI/Vector.cpp > CMakeFiles/Project1.dir/Vector.cpp.i

CMakeFiles/Project1.dir/Vector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project1.dir/Vector.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ac7717/Documents/PSI/HE/PSI/Vector.cpp -o CMakeFiles/Project1.dir/Vector.cpp.s

CMakeFiles/Project1.dir/Matrix.cpp.o: CMakeFiles/Project1.dir/flags.make
CMakeFiles/Project1.dir/Matrix.cpp.o: Matrix.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ac7717/Documents/PSI/HE/PSI/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Project1.dir/Matrix.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project1.dir/Matrix.cpp.o -c /home/ac7717/Documents/PSI/HE/PSI/Matrix.cpp

CMakeFiles/Project1.dir/Matrix.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project1.dir/Matrix.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ac7717/Documents/PSI/HE/PSI/Matrix.cpp > CMakeFiles/Project1.dir/Matrix.cpp.i

CMakeFiles/Project1.dir/Matrix.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project1.dir/Matrix.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ac7717/Documents/PSI/HE/PSI/Matrix.cpp -o CMakeFiles/Project1.dir/Matrix.cpp.s

# Object files for target Project1
Project1_OBJECTS = \
"CMakeFiles/Project1.dir/main.cpp.o" \
"CMakeFiles/Project1.dir/Encryptor.cpp.o" \
"CMakeFiles/Project1.dir/FileSystem.cpp.o" \
"CMakeFiles/Project1.dir/Util.cpp.o" \
"CMakeFiles/Project1.dir/BasicExamples.cpp.o" \
"CMakeFiles/Project1.dir/Calculator.cpp.o" \
"CMakeFiles/Project1.dir/Vector.cpp.o" \
"CMakeFiles/Project1.dir/Matrix.cpp.o"

# External object files for target Project1
Project1_EXTERNAL_OBJECTS =

/home/ac7717/Documents/PSI/deps/bin/Project1: CMakeFiles/Project1.dir/main.cpp.o
/home/ac7717/Documents/PSI/deps/bin/Project1: CMakeFiles/Project1.dir/Encryptor.cpp.o
/home/ac7717/Documents/PSI/deps/bin/Project1: CMakeFiles/Project1.dir/FileSystem.cpp.o
/home/ac7717/Documents/PSI/deps/bin/Project1: CMakeFiles/Project1.dir/Util.cpp.o
/home/ac7717/Documents/PSI/deps/bin/Project1: CMakeFiles/Project1.dir/BasicExamples.cpp.o
/home/ac7717/Documents/PSI/deps/bin/Project1: CMakeFiles/Project1.dir/Calculator.cpp.o
/home/ac7717/Documents/PSI/deps/bin/Project1: CMakeFiles/Project1.dir/Vector.cpp.o
/home/ac7717/Documents/PSI/deps/bin/Project1: CMakeFiles/Project1.dir/Matrix.cpp.o
/home/ac7717/Documents/PSI/deps/bin/Project1: CMakeFiles/Project1.dir/build.make
/home/ac7717/Documents/PSI/deps/bin/Project1: CMakeFiles/Project1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ac7717/Documents/PSI/HE/PSI/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable /home/ac7717/Documents/PSI/deps/bin/Project1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Project1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Project1.dir/build: /home/ac7717/Documents/PSI/deps/bin/Project1

.PHONY : CMakeFiles/Project1.dir/build

CMakeFiles/Project1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Project1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Project1.dir/clean

CMakeFiles/Project1.dir/depend:
	cd /home/ac7717/Documents/PSI/HE/PSI && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ac7717/Documents/PSI/HE/PSI /home/ac7717/Documents/PSI/HE/PSI /home/ac7717/Documents/PSI/HE/PSI /home/ac7717/Documents/PSI/HE/PSI /home/ac7717/Documents/PSI/HE/PSI/CMakeFiles/Project1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Project1.dir/depend

