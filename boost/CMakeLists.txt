cmake_minimum_required (VERSION 2.8.11)
project (boost_network)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
include_directories (/Users/Family/programming/boost_1_63_0)
link_directories (/Users/Family/programming/boost_1_63_0/stage/lib)

add_executable (timer1 src/timer1.cpp)
target_link_libraries (timer1 boost_system)

add_executable (timer2 src/timer2.cpp)
target_link_libraries (timer2 boost_system)

add_executable (timer3 src/timer3.cpp)
target_link_libraries (timer3 boost_system)

add_executable (timer4 src/timer4.cpp)
target_link_libraries (timer4 boost_system)



add_executable (daytime1 src/daytime1.cpp)
target_link_libraries (daytime1 boost_system)

add_executable (daytime2 src/daytime2.cpp)
target_link_libraries (daytime2 boost_system)

add_executable (daytime3 src/daytime3.cpp)
target_link_libraries (daytime3 boost_system)
