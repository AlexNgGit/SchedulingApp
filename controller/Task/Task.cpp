#include "Task.h"

Task::Task(double duration, double cost, std::string name, std::vector<Task> dependencies) {
    this->duration = duration;
    this->cost = cost;
    this->name = name;
    /**
     * TODO: find a way in cpp to deep copy the dependencies array
     */
     this->dependencies = dependencies;
}