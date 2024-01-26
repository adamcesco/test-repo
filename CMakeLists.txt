cmake_minimum_required(VERSION 3.15)
project(think_cell_assignment_project)

set(CMAKE_CXX_STANDARD 17)

# show compiler output and enable warnings
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_VERBOSE_MAKEFILE OFF)

# testing with the single_include versions of Catch2 V2 (in directory catch2)
include(CTest)
add_executable(tests tests.cpp Solution.h Create.h)
add_test(NAME TestAssignment COMMAND tests)
