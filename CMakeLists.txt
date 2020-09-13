cmake_minimum_required(VERSION 3.6)
project(BinarySearchTrees)

set(CMAKE_CXX_STANDARD 11)

add_executable(BinarySearchTrees main.cpp BST.cpp BST.h AVL.cpp AVL.h Splay.cpp Splay.h json.hpp)
target_compile_options(BinarySearchTrees PRIVATE -Wall -Werror)