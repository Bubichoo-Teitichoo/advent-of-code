cmake_minimum_required(VERSION 3.30)
project("Advent of Code 2025/01" LANGUAGES CXX)

set(AOC_DAY "01")
if (NOT DEFINED AOC_YEAR)
    message(FATAL_ERROR "'AOC_YEAR' not defined")
endif()

add_executable("${AOC_YEAR}-${AOC_DAY}" solution.cpp)
set_target_properties("${AOC_YEAR}-${AOC_DAY}" PROPERTIES OUTPUT_NAME solution)
