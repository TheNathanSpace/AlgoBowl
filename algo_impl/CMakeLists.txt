cmake_minimum_required(VERSION 3.26)
project(AlgoBowl)

set(CMAKE_CXX_STANDARD 17)

add_executable(AlgoBowl main.cpp
        graph/Graph.cpp
        graph/Graph.h
        util.cpp
        util.h
        graph/Node.cpp
        graph/Node.h
        graph/Edge.cpp
        graph/Edge.h)
