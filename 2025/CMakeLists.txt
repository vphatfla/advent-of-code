cmake_minimum_required(VERSION 3.10)

project(AdventOfCode2025 VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(ENABLE_PROFILING "Build with debug symbols for Instruments" ON)
if(ENABLE_PROFILING)
    add_compile_options(-g -O2 -fno-omit-frame-pointer)
endif()

set(SOURCE_FILES
    src/main.cpp
)

add_executable(main ${SOURCE_FILES})

add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/data"
        "${CMAKE_BINARY_DIR}/data"
    COMMENT "Copying data folder to build directory..."
)
