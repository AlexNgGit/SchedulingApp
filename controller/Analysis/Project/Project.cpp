#include "Project.h"
#include <vector>

Project::Project(std::vector<Task> input)  {
    std::vector<Task> emptyStart;
    std::vector<Task> emptyEnd;
    this->START = new Task(0, 0, "START", emptyStart);
    this->END = new Task(0, 0, "END", emptyEnd);
    this->taskList = input;
    this->ECT = 0;
}

Project Project::performAnalysis() {
    try {
        throw std::logic_error("NOT IMPLEMENTED YET");
    } catch (std::logic_error error) {
        printf("NOT IMPLEMENTED YET");
    }
}

