#include "Analysis.h"
#include <vector>

Analysis::Analysis(std::vector<Task> input) {
    this->taskList = input;
    this->criticalPath = {};
    this->ECT = 0;
}

Analysis Analysis::performAnalysis() {
    try {
        throw std::logic_error("NOT IMPLEMENTED YET");
    } catch (std::logic_error error) {
        printf("NOT IMPLEMENTED YET");
    }
}

