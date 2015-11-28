cmake_minimum_required(VERSION 3.3)
project(Reversi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp GameBoard.cpp GameBoard.h Players/IPlayer.h Players/RandomPlayer.cpp Players/RandomPlayer.h)
add_executable(Reversi ${SOURCE_FILES})