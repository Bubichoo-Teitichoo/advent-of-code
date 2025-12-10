cmake_minimum_required(VERSION 3.30)
project("Advent of Code" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARDS_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# not the "modern cmake" way, but it makes helper functions available for every target.
include_directories(include)

add_subdirectory(puzzles)

if (CMAKE_EXPORT_COMPILE_COMMANDS)
    cmake_language(DEFER CALL
        file
            CREATE_LINK
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_SOURCE_DIR}/compile_commands.json
            SYMBOLIC
            COPY_ON_ERROR
    )
endif()
