cmake_minimum_required(VERSION 2.8)

project (maps)

set(CMAKE_VERBOSE_MAKEFILE on)

include_directories("." "../map_tests" "~/tools/EASTL/usr/local/include" "~/tools/sparsehash/include")
link_directories("~/tools/EASTL/usr/local/lib" "~/tools/sparsehash/")

set(SOURCE main.cpp "../map_tests/MapTests.h")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -std=c++11 -Wall -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11 -Wall -pedantic")

add_executable(maps ${SOURCE})

target_link_libraries(maps EASTL)
