cmake_minimum_required(VERSION 3.16)
project(RhysOS)

set(CMAKE_C_STANDARD 11)

include_directories(Headers)

add_executable(RhysOS C/main.cpp)