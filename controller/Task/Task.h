#ifndef SCHEDULINGAPP_TASK_H
#define SCHEDULINGAPP_TASK_H
#include <string>
/**
 * Task is an encapsulated object of a real sub component of a real project.
 * Task must have a duration, in double.
 * Task must have a name.
 * Task must have an dependencies array, this can be left empty to denoted the nodes of the first layer of the tree.
 * Task must have a cost associated to it. If it is left empty, will be filled with 0.
 *
 * Optional features for future adds-on:
 * Task can have a description
 * Task can have a start date type Date
 * Task can have extra address information.
 */
using namespace std;
class Task {
    public:
        double duration;
        double cost;
        double earliestStart;
        double earliestFinish;
        double latestStart;
        double latestFinish;
        double slackTime;
        int in_degrees;
        bool visited;
        string name;
        vector<shared_ptr<Task > > dependencies;
        vector<shared_ptr<Task> > childNodes;
        Task(double duration, double cost, string name, vector<shared_ptr<Task > > dependencies);
};
#endif //SCHEDULINGAPP_TASK_H
