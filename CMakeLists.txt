cmake_minimum_required(VERSION 3.24)
project(SLAE)

set(CMAKE_CXX_STANDARD 17)

add_executable(SLAE main.cpp ThirdDiagonalMatrix/third_diagonal.cpp ThirdDiagonalMatrix/third_diagonal.h)
