cmake_minimum_required(VERSION 3.15)
project(solutions)

set(CMAKE_CXX_STANDARD 14)

add_executable(solutions main.cpp minesweeper.cpp minesweeper.h field.h MSBoardTextView.h MSBoardTextView.cpp MSTextController.cpp MSTextController.h)