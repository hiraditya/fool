CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(test)

SET(CMAKE_CXX_FLAGS "-pedantic -Wall -std=c++0x")
 
INCLUDE_DIRECTORIES(/home/hiraditya/Documents/fool/containers)

ADD_DEFINITIONS(-DTEST_STACK_SPECIALIZATION)
ADD_EXECUTABLE(test
               testStack.cpp)
