cmake_minimum_required(VERSION 3.5)
project(sample)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/sanitizers.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

add_executable(sample sample.cpp)
