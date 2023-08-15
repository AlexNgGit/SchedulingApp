#include "Task.h"

Task::Task(double duration, double cost, string name, vector<shared_ptr<Task> > dependencies) {
    this->duration = duration;
    this->cost = cost;
    this->name = name;
    this->dependencies = dependencies;
    this->earliestStart = 0;
    this->earliestFinish = 0;
    dependencies.size() == 0 ? this->in_degrees = 1: this->in_degrees = this->dependencies.size();
    this->visited = false;
}