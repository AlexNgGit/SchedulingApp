add_library(ProjectLibrary project.cpp project.h)
target_link_libraries(ProjectLibrary PUBLIC TaskLibrary)