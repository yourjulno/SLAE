cmake_minimum_required(VERSION 3.24)
project(SLAE)
add_executable(SLAE main.cpp ThreeDiagonalMatrix/three_diagonal.hpp solve/TreeDiagonalSolve.hpp)

set(CMAKE_CXX_STANDARD 17)
enable_testing()
#add_subdirectory(googletest)
target_link_libraries(SLAE gtest gmock pthread)
target_link_libraries(SLAE gtest_main gmock_main)

add_subdirectory(tests)