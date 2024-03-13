cmake_minimum_required(VERSION 3.7...3.28)

project(aia VERSION 1.0
            DESCRIPTION "A simple arena allocator implementation" 
            LANGUAGES CXX)

add_library(${PROJECT_NAME} aia.cpp aia.hpp)