cmake_minimum_required(VERSION 3.16.3)
project(grepex)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")
find_package(Threads)

include_directories(./)

add_executable(grepex main.cpp grep.cpp )
