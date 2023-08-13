#include "Task.h"

Task::Task(double duration, double cost, std::string name, std::vector<Task> dependencies) {
    this->duration = duration;
    this->cost = cost;
    this->name = name;
    /*
     * TODO: this should be an empty array instead, but for now we do this finish the priority first.
     */
    this->dependencies = dependencies;
}