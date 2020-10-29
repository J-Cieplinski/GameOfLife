cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(Game_of_Life)

add_executable(${PROJECT_NAME} main.cpp Board.cpp Cell.cpp)