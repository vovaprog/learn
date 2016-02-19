project (learn1)

set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -Wall -march=native -pthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -O2 -Wall -march=native")

add_executable(learn1 main.cpp learn_signals.cpp learn_system.cpp wget.c smart_pointers.cpp http_server.cpp 
shared_memory.cpp constructor_exception.cpp systemv_semaphores.cpp posix_semaphores.cpp memory_map.cpp posix_memory_map.cpp message_queue.cpp
learn_priority_queue.cpp learn_resources.cpp array_container.cpp learn_set.cpp posix_threads.cpp habr_packet_capture.cpp learn_classes.cpp learn_casts.cpp learn_rtti.cpp resource_file.o)

add_custom_command(OUTPUT resource_file.o COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} &&  ld -r -b binary -o ./build/resource_file.o resource_file.txt DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/resource_file.txt)

target_link_libraries(learn1 rt boost_thread boost_system)


#add_library(resource_file
#        STATIC
#        resource_file.o)

#SET_SOURCE_FILES_PROPERTIES(
#  resource_file.o
#  PROPERTIES
#  EXTERNAL_OBJECT true
#  GENERATED true
#  )

#SET_TARGET_PROPERTIES(
#  resource_file
#  PROPERTIES
#  LINKER_LANGUAGE C 
#  )

#target_link_libraries(learn1 rt resource_file)


#add_custom_target(resource_file.o DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/resource_file.txt)

#add_dependencies(learn1 resource_file.o)


