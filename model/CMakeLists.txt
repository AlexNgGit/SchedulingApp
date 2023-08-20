add_library(test Project.h Project.cpp)
target_link_libraries(test OpenXLSX::OpenXLSX TaskLibrary)
