cmake_minimum_required(VERSION 3.24)
project(advanced_programming_group_dijkstra)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

add_executable(advanced_programming_group_dijkstra
        src/main.cpp
        src/utils.h
        src/stb_image.h
        src/stb_image_write.h
        src/Image.h
        src/Image.cpp)
