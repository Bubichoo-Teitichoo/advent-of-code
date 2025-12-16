cmake_minimum_required(VERSION 3.30)
project("Advent of Code 2025" LANGUAGES CXX)

set(AOC_YEAR "2025")

option(AOC_BUILD_2025_DAY01 "Build day 1 of 2025s AoC puzzles." ON)
option(AOC_BUILD_2025_DAY02 "Build day 2 of 2025s AoC puzzles." ON)

if (AOC_BUILD_2025_DAY01)
    add_executable("aoc-2025-day01-reference" day01/reference.cpp)
    add_executable("aoc-2025-day01-solution" day01/solution.cpp)
endif()

if (AOC_BUILD_2025_DAY02)
    add_subdirectory(day02)
endif()
