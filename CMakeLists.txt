cmake_minimum_required(VERSION 3.28)
project(Assignment_5_Programming_Paradigms)

set(CMAKE_CXX_STANDARD 26)

add_executable(Assignment_5_Programming_Paradigms Assignment_5/main.cpp
        Assignment_5/Stack/Stack.cpp
        Assignment_5/Stack/Stack.h
        Assignment_5/RPN/RPN.cpp
        Assignment_5/RPN/RPN.h)
