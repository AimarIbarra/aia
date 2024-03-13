cmake_minimum_required(VERSION 3.7...3.28)

project(aia VERSION 1.0
            DESCRIPTION "A simple arena allocator implementation" 
            LANGUAGES CXX)

add_library(${PROJECT_NAME} aia.cpp aia.hpp)
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIRECTORY}")

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
    add_executable(build_test build_test.cpp)
    target_link_libraries(build_test aia)
    add_test("Builds" build_test)
endif()