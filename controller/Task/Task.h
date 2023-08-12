#ifndef SCHEDULINGAPP_TASK_H
#define SCHEDULINGAPP_TASK_H
#include <string>
/**
 * Task is an encapsulated object of a real sub component of a real project.
 * Task should have a duration, in double.
 * Task should have a name.
 * Task should have an dependencies array, this can be left empty to denoted the nodes of the first layer of the tree.
 */
class Task {
    public:
        double duration;
        double cost;
        double earliestStart;
        std::string name;
        std::vector<Task> dependencies;
        Task(double duration, double cost, std::string name, std::vector<Task> dependencies);
};
#endif //SCHEDULINGAPP_TASK_H
