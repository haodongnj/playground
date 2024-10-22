cmake_minimum_required(VERSION 3.15)
project(perfetto_example)

set(CMAKE_CXX_STANDARD 17)

find_package(perfetto)

add_executable(perfetto_example
    main.cpp
)

target_include_directories(perfetto_example PRIVATE ${perfetto_INCLUDE_DIRS})
target_link_libraries(perfetto_example perfetto::perfetto)