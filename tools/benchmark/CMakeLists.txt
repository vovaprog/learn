cmake_minimum_required(VERSION 2.8)

project (benchmark)

set(CMAKE_VERBOSE_MAKEFILE on)

include_directories(".")

set(SOURCE
    main.cpp
    ArithmeticBenchmark.h ArithmeticBenchmark.cpp
    BenchmarkMap.h BenchmarkMap.cpp
    IntrusiveMapBenchmark.h IntrusiveMapBenchmark.cpp
    StringMapBenchmark.h StringMapBenchmark.cpp
    Tools.h Tools.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -march=native -Wall -pedantic")

add_executable(benchmark ${SOURCE})

target_link_libraries(benchmark boost_filesystem boost_system)
