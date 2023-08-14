#include "Task.h"

Task::Task(double duration, double cost, string name, vector<shared_ptr<Task> > dependencies) {
    this->duration = duration;
    this->cost = cost;
    this->name = name;
    this->dependencies = dependencies;
    this->earliestStart = 0;
    this->earliestFinish = 0;
}