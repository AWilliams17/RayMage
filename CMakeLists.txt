cmake_minimum_required(VERSION 3.10)
project(RayMage)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(RayMage main.cpp test_map.h Auxiliary/renderer.cpp Auxiliary/renderer.h Auxiliary/keyscanner.cpp Auxiliary/keyscanner.h)

target_link_libraries(RayMage ${SDL2_LIBRARIES})