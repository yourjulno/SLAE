cmake_minimum_required(VERSION 3.17)
project(SLAE)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES *.h *.cpp *.hpp)

add_library(SLAE INTERFACE ${SOURCES})
