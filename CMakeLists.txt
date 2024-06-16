cmake_minimum_required(VERSION 3.28)
project(Hex_Dijkstra)

set(CMAKE_CXX_STANDARD 17)

add_executable(Hex_Dijkstra main.cpp
        Node.h
        Graph.h
        Graph.cpp
        HexSimulation.h
        HexSimulation.cpp
        HexGame.h
        HexGame.cpp)
