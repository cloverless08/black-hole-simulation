cmake_minimum_required(VERSION 3.12)
project(CSC1060_Capstone_Project CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED CONFIG)

file(GLOB_RECURSE ALL_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/raytrace/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/raytrace/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

add_executable(CSC1060_CAPSTONE_PROJECT ${ALL_SOURCES})

target_include_directories(CSC1060_CAPSTONE_PROJECT PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(CSC1060_CAPSTONE_PROJECT PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
)