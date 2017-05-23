cmake_minimum_required(VERSION 2.8)

project (benchmark)

set(CMAKE_VERBOSE_MAKEFILE on)

include_directories(".")

set(SOURCE
    main.cpp
    BenchStdMap.h BenchStdMap.cpp
    Tools.h Tools.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

add_executable(benchmark ${SOURCE})


