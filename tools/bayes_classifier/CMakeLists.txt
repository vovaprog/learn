cmake_minimum_required(VERSION 2.8)

project (bayes_classifier)

set(CMAKE_VERBOSE_MAKEFILE on)

include_directories(".")

set(SOURCE
    bayes_classifier.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

add_executable(bayes_classifier ${SOURCE})


