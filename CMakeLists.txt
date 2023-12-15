cmake_minimum_required(VERSION 3.20)
project(Parse_algorithms)

set(CMAKE_CXX_STANDARD 14)
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

include_directories(.)

add_executable(Parse_algorithms
        earley.cpp
        earley.h
        main.cpp
        test.cpp)

target_link_directories(Parse_algorithms PRIVATE ${GTEST_INCLUDE_DIRS})

target_link_libraries(Parse_algorithms PRIVATE GTest::GTest Threads::Threads)
