cmake_minimum_required(VERSION 3.7...3.28)

project(aia VERSION 1.0
            DESCRIPTION "A simple arena allocator implementation" 
            LANGUAGES CXX)

add_subdirectory(src)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    Include(FetchContent)

    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0 # or a later release
    )

    FetchContent_MakeAvailable(Catch2)

    include(CTest)
    add_subdirectory(tests)
endif()