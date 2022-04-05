cmake_minimum_required(VERSION 3.21)
project(7_Ring_Buffer_Stage_7)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(7_Ring_Buffer_Stage_7
        main.cpp
        ringbuf.hpp)
