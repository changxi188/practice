# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/mr/Downloads/practice/opencv2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mr/Downloads/practice/opencv2/src

# Include any dependencies generated for this target.
include src/CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/main.dir/flags.make

src/CMakeFiles/main.dir/main.cpp.o: src/CMakeFiles/main.dir/flags.make
src/CMakeFiles/main.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mr/Downloads/practice/opencv2/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/main.dir/main.cpp.o"
	cd /home/mr/Downloads/practice/opencv2/src/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/main.cpp.o -c /home/mr/Downloads/practice/opencv2/src/main.cpp

src/CMakeFiles/main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cpp.i"
	cd /home/mr/Downloads/practice/opencv2/src/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mr/Downloads/practice/opencv2/src/main.cpp > CMakeFiles/main.dir/main.cpp.i

src/CMakeFiles/main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cpp.s"
	cd /home/mr/Downloads/practice/opencv2/src/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mr/Downloads/practice/opencv2/src/main.cpp -o CMakeFiles/main.dir/main.cpp.s

src/CMakeFiles/main.dir/main.cpp.o.requires:

.PHONY : src/CMakeFiles/main.dir/main.cpp.o.requires

src/CMakeFiles/main.dir/main.cpp.o.provides: src/CMakeFiles/main.dir/main.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/main.dir/build.make src/CMakeFiles/main.dir/main.cpp.o.provides.build
.PHONY : src/CMakeFiles/main.dir/main.cpp.o.provides

src/CMakeFiles/main.dir/main.cpp.o.provides.build: src/CMakeFiles/main.dir/main.cpp.o


# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

src/main: src/CMakeFiles/main.dir/main.cpp.o
src/main: src/CMakeFiles/main.dir/build.make
src/main: src/libmy_lib.so
src/main: /usr/lib/x86_64-linux-gnu/libopencv_shape.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_aruco.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_bgsegm.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_bioinspired.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_ccalib.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_datasets.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_dpm.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_face.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_freetype.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_fuzzy.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_hdf.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_line_descriptor.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_optflow.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_video.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_plot.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_reg.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_saliency.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_stereo.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_structured_light.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_viz.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_phase_unwrapping.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_rgbd.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_surface_matching.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_text.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_ximgproc.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_xobjdetect.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_xphoto.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_videoio.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_imgcodecs.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.3.2.0
src/main: /usr/lib/x86_64-linux-gnu/libopencv_core.so.3.2.0
src/main: src/CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mr/Downloads/practice/opencv2/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable main"
	cd /home/mr/Downloads/practice/opencv2/src/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/main.dir/build: src/main

.PHONY : src/CMakeFiles/main.dir/build

src/CMakeFiles/main.dir/requires: src/CMakeFiles/main.dir/main.cpp.o.requires

.PHONY : src/CMakeFiles/main.dir/requires

src/CMakeFiles/main.dir/clean:
	cd /home/mr/Downloads/practice/opencv2/src/src && $(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/main.dir/clean

src/CMakeFiles/main.dir/depend:
	cd /home/mr/Downloads/practice/opencv2/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mr/Downloads/practice/opencv2 /home/mr/Downloads/practice/opencv2/src /home/mr/Downloads/practice/opencv2/src /home/mr/Downloads/practice/opencv2/src/src /home/mr/Downloads/practice/opencv2/src/src/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/main.dir/depend

