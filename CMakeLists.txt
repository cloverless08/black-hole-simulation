cmake_minimum_required(VERSION 3.12) # Note: Upgraded from 3.10 for CONFIGURE_DEPENDS
project(CSC1060_Capstone_Project CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Find Dependencies
find_package(SDL2 REQUIRED CONFIG)

# 2. Automatically harvest ALL .cpp and .h files dynamically
file(GLOB_RECURSE ALL_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

# 3. Define the Executable using the automated list
add_executable(CSC1060_CAPSTONE_PROJECT ${ALL_SOURCES})

# 4. Include Directories so your .h files can find each other
target_include_directories(CSC1060_CAPSTONE_PROJECT PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# 5. Link Libraries
target_link_libraries(CSC1060_CAPSTONE_PROJECT PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
)