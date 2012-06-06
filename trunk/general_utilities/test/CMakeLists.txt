CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(test)

SET(CMAKE_CXX_FLAGS "-pedantic -Wall -g -std=c++0x")
 
INCLUDE_DIRECTORIES(/home/hiraditya/Documents/fool/general_utilities)


ADD_EXECUTABLE(test
                 testprint_typename.cpp
  )
