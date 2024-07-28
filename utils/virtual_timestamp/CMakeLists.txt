cmake_minimum_required(VERSION 3.15)
project(virtual_timestamp)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

# set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_BINARY_DIR}/build/Release/generators/conan_toolchain.cmake)
# set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_BINARY_DIR}/generators/conan_toolchain.cmake)
set(CMAKE_TOOLCHAIN_FILE generators/conan_toolchain.cmake)

find_package(Boost REQUIRED)

add_library(virtual_time SHARED
        src/virtual_time.cpp
        src/hijacked.cpp
        src/util.cpp
)
target_include_directories(virtual_time PUBLIC
    include
    ${Boost_INCLUDE_DIR}
    )
target_link_libraries(virtual_time PUBLIC Boost::boost)
set_target_properties(virtual_time PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_executable(virtual_time_push test/virtual_time_push.cpp)
target_link_libraries(virtual_time_push virtual_time)

add_executable(virtual_time_get test/virtual_time_get.cpp)
target_link_libraries(virtual_time_get virtual_time)

add_executable(system_clock_now
    test/system_clock_now.cpp
    src/util.cpp
    )

target_include_directories(system_clock_now PUBLIC include)