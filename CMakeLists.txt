cmake_minimum_required(VERSION 3.3)
project(Reversi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# -DNDEBUG отключает обработку assert'ов.
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11 -DNDEBUG")

set(SOURCE_FILES main.cpp
        GameBoard.cpp GameBoard.h
        Players/IPlayer.h Players/IPlayer.cpp
        Players/RandomPlayer.cpp Players/RandomPlayer.h
        Judge.cpp Judge.h
        Players/MaxMovePlayer.cpp Players/MaxMovePlayer.h
        Players/MainPlayer.cpp Players/MainPlayer.h)
add_executable(Reversi ${SOURCE_FILES})