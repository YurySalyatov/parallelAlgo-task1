cmake_minimum_required(VERSION 3.29)
project(parallelAlgo)

set(CMAKE_CXX_STANDARD 14)

find_package(TBB CONFIG REQUIRED)

add_executable(firstTask main.cpp)

target_link_libraries(firstTask TBB::tbb)