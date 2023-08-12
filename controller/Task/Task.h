#ifndef SCHEDULINGAPP_TASK_H
#define SCHEDULINGAPP_TASK_H
#include <string>
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
