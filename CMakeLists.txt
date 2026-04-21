cmake_minimum_required(VERSION 4.1)
project(Algorithms_MazeRunner)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED)

add_executable(Algorithms_MazeRunner main.cpp)

# Link SDL2 to your project
target_link_libraries(Algorithms_MazeRunner PRIVATE SDL2::SDL2)