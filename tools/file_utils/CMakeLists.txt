cmake_minimum_required(VERSION 2.8)

project (file_utils)

set(CMAKE_VERBOSE_MAKEFILE on)

include_directories(".")

set(SOURCE main.cpp FileUtils.h FileUtils.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -std=c++11 -Wall -pedantic")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11 -Wall -pedantic")

add_executable(file_utils ${SOURCE})

