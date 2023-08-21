CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(SchedulingApp VERSION 0.0)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(OpenXLSX)
add_subdirectory("controller")
add_subdirectory("model")
add_subdirectory("view")
add_subdirectory("test")
