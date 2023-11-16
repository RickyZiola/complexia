# CMake minimum version
cmake_minimum_required(VERSION 3.0)

# Project name
project(YourProjectName)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB TEST_SOURCES tests/*.c)

# Iterate over each test source file
foreach(TEST_SOURCE ${TEST_SOURCES})
    # Extract the file name without extension
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)

    # Create an executable for each test source file
    add_executable(${TEST_NAME} ${TEST_SOURCE} parser.c)

    # Optionally, link any necessary libraries
    # target_link_libraries(${TEST_NAME} some_library)
endforeach()