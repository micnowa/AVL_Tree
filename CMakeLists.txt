cmake_minimum_required(VERSION 3.12)
project(lab)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab main.cpp Sequence.cpp List.cpp Ring.cpp AVLTree.cpp)