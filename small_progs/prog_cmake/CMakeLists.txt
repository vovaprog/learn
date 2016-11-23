cmake_minimum_required(VERSION 2.8)

project (prog)

set(CMAKE_VERBOSE_MAKEFILE on)

include_directories(".")

set(SOURCE
    main.cpp learn_time.cpp learn_thread_id.cpp ProxySplice.cpp learn_signals.cpp learn_stack_protector.cpp learn_sockets.cpp)


#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -std=c++11 -Wall -pedantic -pthread -fstack-protector-all")

add_executable(prog ${SOURCE})


