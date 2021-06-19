cmake_minimum_required(VERSION 3.19)
project(characterRecognition)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexec-charset=GBK")
add_executable(characterRecognition main.cpp)