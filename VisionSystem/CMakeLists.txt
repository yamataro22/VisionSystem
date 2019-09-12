cmake_minimum_required(VERSION 3.12)
project(visonSystem)

set(CMAKE_CXX_STANDARD 17)
file(GLOB_RECURSE SRC *.cpp)
include_directories(".")

message(STATUS "Adding executable")
add_executable(visonSystem ${SRC})
