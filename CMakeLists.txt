cmake_minimum_required(VERSION 3.10)
project(CSC1060_Capstone_Project CXX)

set(CMAKE_CXX_STANDARD 17)
find_package(SDL2 REQUIRED CONFIG)

file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE INCLUDE "*.h")

add_executable(CSC1060_CAPSTONE_PROJECT
    ${SOURCES}
    ${INCLUDE}
)

target_sources(CSC1060_CAPSTONE_PROJECT PRIVATE
"${CMAKE_CURRENT_SOURCE_DIR}/src/loop.cpp"
# "${CMAKE_CURRENT_SOURCE_DIR}/src/main_utils.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/src/keybinds.cpp"
)

target_include_directories(CSC1060_CAPSTONE_PROJECT PRIVATE
"${CMAKE_CURRENT_SOURCE_DIR}/include/"
)

target_link_libraries(CSC1060_CAPSTONE_PROJECT PRIVATE SDL2::SDL2 SDL2::SDL2main)
