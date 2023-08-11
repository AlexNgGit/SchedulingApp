find_package(Catch2 CONFIG REQUIRED)
add_executable(simpleTest main.cpp)
target_link_libraries(simpleTest PRIVATE Catch2::Catch2WithMain)
