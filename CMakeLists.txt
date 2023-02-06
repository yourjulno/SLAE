cmake_minimum_required(VERSION 3.24)
project(SLAE)

set(CMAKE_CXX_STANDARD 17)

add_executable(SLAE main.cpp ThreeDiagonalMatrix/three_diagonal.cpp ThreeDiagonalMatrix/three_diagonal.h solve/TreeDiagonalSolve.cpp solve/TreeDiagonalSolve.h)
