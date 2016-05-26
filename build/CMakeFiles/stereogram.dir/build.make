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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/reality-marble/Projects/Autostereogram

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/reality-marble/Projects/Autostereogram/build

# Include any dependencies generated for this target.
include CMakeFiles/stereogram.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/stereogram.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/stereogram.dir/flags.make

CMakeFiles/stereogram.dir/src/StereogramGenerator.cpp.o: CMakeFiles/stereogram.dir/flags.make
CMakeFiles/stereogram.dir/src/StereogramGenerator.cpp.o: ../src/StereogramGenerator.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/reality-marble/Projects/Autostereogram/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/stereogram.dir/src/StereogramGenerator.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/stereogram.dir/src/StereogramGenerator.cpp.o -c /home/reality-marble/Projects/Autostereogram/src/StereogramGenerator.cpp

CMakeFiles/stereogram.dir/src/StereogramGenerator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stereogram.dir/src/StereogramGenerator.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/reality-marble/Projects/Autostereogram/src/StereogramGenerator.cpp > CMakeFiles/stereogram.dir/src/StereogramGenerator.cpp.i

CMakeFiles/stereogram.dir/src/StereogramGenerator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stereogram.dir/src/StereogramGenerator.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/reality-marble/Projects/Autostereogram/src/StereogramGenerator.cpp -o CMakeFiles/stereogram.dir/src/StereogramGenerator.cpp.s

CMakeFiles/stereogram.dir/src/StereogramGenerator.cpp.o.requires:
.PHONY : CMakeFiles/stereogram.dir/src/StereogramGenerator.cpp.o.requires

CMakeFiles/stereogram.dir/src/StereogramGenerator.cpp.o.provides: CMakeFiles/stereogram.dir/src/StereogramGenerator.cpp.o.requires
	$(MAKE) -f CMakeFiles/stereogram.dir/build.make CMakeFiles/stereogram.dir/src/StereogramGenerator.cpp.o.provides.build
.PHONY : CMakeFiles/stereogram.dir/src/StereogramGenerator.cpp.o.provides

CMakeFiles/stereogram.dir/src/StereogramGenerator.cpp.o.provides.build: CMakeFiles/stereogram.dir/src/StereogramGenerator.cpp.o

CMakeFiles/stereogram.dir/src/main.cpp.o: CMakeFiles/stereogram.dir/flags.make
CMakeFiles/stereogram.dir/src/main.cpp.o: ../src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/reality-marble/Projects/Autostereogram/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/stereogram.dir/src/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/stereogram.dir/src/main.cpp.o -c /home/reality-marble/Projects/Autostereogram/src/main.cpp

CMakeFiles/stereogram.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stereogram.dir/src/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/reality-marble/Projects/Autostereogram/src/main.cpp > CMakeFiles/stereogram.dir/src/main.cpp.i

CMakeFiles/stereogram.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stereogram.dir/src/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/reality-marble/Projects/Autostereogram/src/main.cpp -o CMakeFiles/stereogram.dir/src/main.cpp.s

CMakeFiles/stereogram.dir/src/main.cpp.o.requires:
.PHONY : CMakeFiles/stereogram.dir/src/main.cpp.o.requires

CMakeFiles/stereogram.dir/src/main.cpp.o.provides: CMakeFiles/stereogram.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/stereogram.dir/build.make CMakeFiles/stereogram.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/stereogram.dir/src/main.cpp.o.provides

CMakeFiles/stereogram.dir/src/main.cpp.o.provides.build: CMakeFiles/stereogram.dir/src/main.cpp.o

# Object files for target stereogram
stereogram_OBJECTS = \
"CMakeFiles/stereogram.dir/src/StereogramGenerator.cpp.o" \
"CMakeFiles/stereogram.dir/src/main.cpp.o"

# External object files for target stereogram
stereogram_EXTERNAL_OBJECTS =

../bin/stereogram: CMakeFiles/stereogram.dir/src/StereogramGenerator.cpp.o
../bin/stereogram: CMakeFiles/stereogram.dir/src/main.cpp.o
../bin/stereogram: CMakeFiles/stereogram.dir/build.make
../bin/stereogram: /usr/local/build/opencv-3.1.0/lib/libopencv_videostab.so.3.1.0
../bin/stereogram: /usr/local/build/opencv-3.1.0/lib/libopencv_videoio.so.3.1.0
../bin/stereogram: /usr/local/build/opencv-3.1.0/lib/libopencv_video.so.3.1.0
../bin/stereogram: /usr/local/build/opencv-3.1.0/lib/libopencv_superres.so.3.1.0
../bin/stereogram: /usr/local/build/opencv-3.1.0/lib/libopencv_stitching.so.3.1.0
../bin/stereogram: /usr/local/build/opencv-3.1.0/lib/libopencv_shape.so.3.1.0
../bin/stereogram: /usr/local/build/opencv-3.1.0/lib/libopencv_photo.so.3.1.0
../bin/stereogram: /usr/local/build/opencv-3.1.0/lib/libopencv_objdetect.so.3.1.0
../bin/stereogram: /usr/local/build/opencv-3.1.0/lib/libopencv_ml.so.3.1.0
../bin/stereogram: /usr/local/build/opencv-3.1.0/lib/libopencv_imgproc.so.3.1.0
../bin/stereogram: /usr/local/build/opencv-3.1.0/lib/libopencv_imgcodecs.so.3.1.0
../bin/stereogram: /usr/local/build/opencv-3.1.0/lib/libopencv_highgui.so.3.1.0
../bin/stereogram: /usr/local/build/opencv-3.1.0/lib/libopencv_flann.so.3.1.0
../bin/stereogram: /usr/local/build/opencv-3.1.0/lib/libopencv_features2d.so.3.1.0
../bin/stereogram: /usr/local/build/opencv-3.1.0/lib/libopencv_core.so.3.1.0
../bin/stereogram: /usr/local/build/opencv-3.1.0/lib/libopencv_calib3d.so.3.1.0
../bin/stereogram: /usr/local/build/opencv-3.1.0/lib/libopencv_features2d.so.3.1.0
../bin/stereogram: /usr/local/build/opencv-3.1.0/lib/libopencv_ml.so.3.1.0
../bin/stereogram: /usr/local/build/opencv-3.1.0/lib/libopencv_highgui.so.3.1.0
../bin/stereogram: /usr/local/build/opencv-3.1.0/lib/libopencv_videoio.so.3.1.0
../bin/stereogram: /usr/local/build/opencv-3.1.0/lib/libopencv_imgcodecs.so.3.1.0
../bin/stereogram: /usr/local/build/opencv-3.1.0/lib/libopencv_flann.so.3.1.0
../bin/stereogram: /usr/local/build/opencv-3.1.0/lib/libopencv_video.so.3.1.0
../bin/stereogram: /usr/local/build/opencv-3.1.0/lib/libopencv_imgproc.so.3.1.0
../bin/stereogram: /usr/local/build/opencv-3.1.0/lib/libopencv_core.so.3.1.0
../bin/stereogram: CMakeFiles/stereogram.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/stereogram"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stereogram.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/stereogram.dir/build: ../bin/stereogram
.PHONY : CMakeFiles/stereogram.dir/build

CMakeFiles/stereogram.dir/requires: CMakeFiles/stereogram.dir/src/StereogramGenerator.cpp.o.requires
CMakeFiles/stereogram.dir/requires: CMakeFiles/stereogram.dir/src/main.cpp.o.requires
.PHONY : CMakeFiles/stereogram.dir/requires

CMakeFiles/stereogram.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/stereogram.dir/cmake_clean.cmake
.PHONY : CMakeFiles/stereogram.dir/clean

CMakeFiles/stereogram.dir/depend:
	cd /home/reality-marble/Projects/Autostereogram/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/reality-marble/Projects/Autostereogram /home/reality-marble/Projects/Autostereogram /home/reality-marble/Projects/Autostereogram/build /home/reality-marble/Projects/Autostereogram/build /home/reality-marble/Projects/Autostereogram/build/CMakeFiles/stereogram.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/stereogram.dir/depend
