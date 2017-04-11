cmake_minimum_required(VERSION 2.8)

project (prog)

set(CMAKE_VERBOSE_MAKEFILE on)

include_directories(".")

set(SOURCE
    main.cpp HttpRequest.cpp TimeUtils.cpp HttpRequestTest.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

add_executable(prog ${SOURCE})

target_link_libraries(prog boost_regex pcre)
