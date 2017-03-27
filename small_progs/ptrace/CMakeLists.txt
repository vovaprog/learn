cmake_minimum_required(VERSION 2.8)

project (prog)

set(CMAKE_VERBOSE_MAKEFILE on)

include_directories(".")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -std=c++11 -Wall -pedantic -pthread -I ${CMAKE_BINARY_DIR}")

add_custom_command(OUTPUT ${CMAKE_SOURCE_DIR}/syscall_names.cpp
    #WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND bash ${CMAKE_SOURCE_DIR}/generate_syscall_names.sh)

add_executable(ptrace main.cpp)

add_custom_target(syscall_names DEPENDS ${CMAKE_SOURCE_DIR}/syscall_names.cpp)

add_dependencies(ptrace syscall_names)

