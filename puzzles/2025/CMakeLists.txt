
project("Advent of Code 2025")

option(AOC_BUILD_2025_DAY01 "Build day 1 of 2025s AoC puzzles." ON)

if (AOC_BUILD_2025_DAY01)
    add_executable("aoc-2025-day01-simple" day01/simple.cpp)
    add_executable("aoc-2025-day01-complex" day01/complex.cpp)
endif()
