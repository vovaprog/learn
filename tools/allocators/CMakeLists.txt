cmake_minimum_required(VERSION 2.8)

project (allocators)

set(CMAKE_VERBOSE_MAKEFILE on)

include_directories("." "/home/vova/tools/include")
link_directories("/home/vova/tools/lib")

set(SOURCE main.cpp TrivialAllocator.h BlockAllocator.h)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -std=c++11 -Wall -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11 -Wall -pedantic")

add_executable(allocators ${SOURCE})

target_link_libraries(allocators EASTL)
