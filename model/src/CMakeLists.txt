add_library(ProjectModel Project.h Project.cpp)
target_link_libraries(ProjectModel OpenXLSX::OpenXLSX TaskLibrary)