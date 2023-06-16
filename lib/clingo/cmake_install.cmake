# Install script for directory: /home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/lib/clingo

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/lib/clingo/clasp/cmake_install.cmake")
  include("/home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/lib/clingo/libreify/cmake_install.cmake")
  include("/home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/lib/clingo/libgringo/cmake_install.cmake")
  include("/home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/lib/clingo/libclingo/cmake_install.cmake")
  include("/home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/lib/clingo/libpyclingo/cmake_install.cmake")
  include("/home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/lib/clingo/libluaclingo/cmake_install.cmake")
  include("/home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/lib/clingo/app/reify/cmake_install.cmake")
  include("/home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/lib/clingo/app/gringo/cmake_install.cmake")
  include("/home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/lib/clingo/app/clingo/cmake_install.cmake")

endif()

