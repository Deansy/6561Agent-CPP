cmake_minimum_required(VERSION 3.3)
project(6561Agent)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/Users/camsh/caia/6561/bin")

set(SOURCE_FILES
    6561Agent.cpp
    Board.cpp
    Board.h
    Tile.cpp
    Tile.h CompetitionMain.cpp CompetitionMain.h Player.h RandomMoveAgent.cpp RandomMoveAgent.h DepthLimitedDFSAgent.cpp DepthLimitedDFSAgent.h)

add_executable(6561Agent ${SOURCE_FILES})