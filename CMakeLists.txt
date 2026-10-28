cmake_minimum_required(VERSION 3.10)
project(CSC1060_Capstone_Project CXX)

set(CMAKE_CXX_STANDARD 17)
find_package(SDL2 REQUIRED CONFIG)
find_package(Eigen3 REQUIRED NO_MODULE)
add_executable(CSC1060_CAPSTONE_PROJECT
        src/main.cpp
        include/camera.h
        include/math.h
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
target_link_libraries(example Eigen3::Eigen)
