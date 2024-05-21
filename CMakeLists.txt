cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

project(app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} 
    src/main.cpp 
    src/FileTape.cpp 
    src/TapeSort.cpp) 