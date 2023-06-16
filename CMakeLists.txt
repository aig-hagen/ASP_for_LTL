cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)

project(InconsistencyMeasureAlgorithms
  VERSION
    1.0
  DESCRIPTION
    "Implementations of algorithms for inconsistency measurement in LTL"
)

add_executable(ltl_app main.cpp)
add_subdirectory(src/)
add_subdirectory(lib/clingo)
target_link_libraries(ltl_app libclingo)
