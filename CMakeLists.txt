CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(SchedulingApp VERSION 0.0)
#find_package(Xlnt CONFIG REQUIRED)
#target_link_libraries(main PRIVATE xlnt::xlnt)

add_subdirectory("controller")
add_subdirectory("view")
add_subdirectory("test")
