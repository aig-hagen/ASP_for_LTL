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
CMAKE_SOURCE_DIR = /home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms

# Utility rule file for gen2.

# Include the progress variables for this target.
include lib/clingo/libgringo/CMakeFiles/gen2.dir/progress.make

lib/clingo/libgringo/CMakeFiles/gen2: lib/clingo/libgringo/src/input/groundtermlexer.hh


lib/clingo/libgringo/src/input/groundtermlexer.hh: lib/clingo/libgringo/src/input/groundtermlexer.xh
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "[RE2C][groundtermlexer] Building lexer with re2c 0.103.0"
	cd /home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/lib/clingo/libgringo && /usr/bin/re2c -o /home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/lib/clingo/libgringo//src/input/groundtermlexer.hh /home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/lib/clingo/libgringo//src/input/groundtermlexer.xh

gen2: lib/clingo/libgringo/CMakeFiles/gen2
gen2: lib/clingo/libgringo/src/input/groundtermlexer.hh
gen2: lib/clingo/libgringo/CMakeFiles/gen2.dir/build.make

.PHONY : gen2

# Rule to build all files generated by this target.
lib/clingo/libgringo/CMakeFiles/gen2.dir/build: gen2

.PHONY : lib/clingo/libgringo/CMakeFiles/gen2.dir/build

lib/clingo/libgringo/CMakeFiles/gen2.dir/clean:
	cd /home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/lib/clingo/libgringo && $(CMAKE_COMMAND) -P CMakeFiles/gen2.dir/cmake_clean.cmake
.PHONY : lib/clingo/libgringo/CMakeFiles/gen2.dir/clean

lib/clingo/libgringo/CMakeFiles/gen2.dir/depend:
	cd /home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms /home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/lib/clingo/libgringo /home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms /home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/lib/clingo/libgringo /home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/lib/clingo/libgringo/CMakeFiles/gen2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/clingo/libgringo/CMakeFiles/gen2.dir/depend

