cmake_minimum_required(VERSION 3.15)
project(replay)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

# set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_BINARY_DIR}/build/Release/generators/conan_toolchain.cmake)
# set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_BINARY_DIR}/generators/conan_toolchain.cmake)
set(CMAKE_TOOLCHAIN_FILE generators/conan_toolchain.cmake)

find_package(Boost REQUIRED)

add_library(virtual_time SHARED
        src/virtual_time.cpp
        src/gettimeofday_hijacked.cpp
        src/util.cpp
)
target_include_directories(virtual_time PUBLIC include)
target_link_libraries(virtual_time PUBLIC Boost::boost)
set_target_properties(virtual_time PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_executable(virtual_time_push test/virtual_time_push.cpp)
target_link_libraries(virtual_time_push virtual_time)

add_executable(virtual_time_get test/virtual_time_get.cpp)
target_link_libraries(virtual_time_get virtual_time)

add_executable(get_time_of_day test/get_time_of_day.cpp)