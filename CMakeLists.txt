cmake_minimum_required(VERSION 3.9)

project(Algorithms_MazeRunner)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

include_directories("C:/MinGW/include/SDL2")
link_directories("C:/MinGW/lib")

add_executable(Algorithms_MazeRunner main.cpp SDL_Plotter.h SDL_Plotter.cpp)
target_link_libraries(Algorithms_MazeRunner mingw32 SDL2main SDL2 SDL2_mixer)