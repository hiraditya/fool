cmake_minimum_required(VERSION 2.8)
project(memory_map)
include_directories(${CMAKE_SOURCE_DIR} "/home/vmplanet/Documents/examples/MemoryMapping/version3/")
link_directories("/home/vmplanet/Documents/examples/MemoryMapping/version3/build")
#set(CMAKE_CXX_COMPILER "/media/space/opt_149739_build/bin/clang++")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}  "-g -std=c++0x ")
add_executable(main
  test1_writing.cpp
  ../MemoryMap.cpp
)
target_link_libraries(main filemap rt)
#add_subdirectory(test)

