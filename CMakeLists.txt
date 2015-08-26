project (learn1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -Wall -march=native")

add_executable(learn1 main.cpp learn_signals.cpp)

