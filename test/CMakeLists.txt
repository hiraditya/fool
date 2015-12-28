cmake_minimum_required(VERSION 2.8)
project(test)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++11 -g ${CMAKE_CXX_FLAGS}")
include_directories("${cmake_source_directory} ${DIR}/fool")

if(ORIGIN_AVAILABLE)
  add_executable(test_cons test_cons.cpp)
  add_executable(test_fof test_fof.cpp)
  add_executable(test_hof test_hof.cpp)
endif()

add_subdirectory(statistics)
add_executable(test_find_size test_find_size.cpp)
