cmake_minimum_required(VERSION 3.3)
project(6561Agent)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    6561Agent.cpp
    Board.cpp
    Board.h
    Tile.cpp
    Tile.h CompetitionMain.cpp CompetitionMain.h Player.h RandomMoveAgent.cpp RandomMoveAgent.h)

add_executable(6561Agent ${SOURCE_FILES})