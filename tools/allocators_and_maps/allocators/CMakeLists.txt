cmake_minimum_required(VERSION 2.8)

project (allocators)

set(CMAKE_VERBOSE_MAKEFILE on)

include_directories("." "../map_tests")

set(SOURCE main.cpp TrivialAllocator.h BlockAllocator.h ../map_tests/MapTests.h)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -std=c++11 -Wall -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11 -Wall -pedantic")

add_executable(allocators ${SOURCE})

