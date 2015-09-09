project (learn1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -Wall -march=native -pthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -O2 -Wall -march=native")

add_executable(learn1 main.cpp learn_signals.cpp learn_system.cpp wget.c smart_pointers.cpp http_server.cpp 
shared_memory.cpp constructor_exception.cpp systemv_semaphores.cpp posix_semaphores.cpp memory_map.cpp posix_memory_map.cpp message_queue.cpp)

target_link_libraries(learn1 rt)
