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
private:
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
public:
        Task(double duration, double cost, const string& name, const vector<shared_ptr<Task > >& dependencies);

    double getDuration() const;

    void setDuration(double duration);

    double getCost() const;

    void setCost(double cost);

    double getEarliestStart() const;

    void setEarliestStart(double earliestStart);

    double getEarliestFinish() const;

    void setEarliestFinish(double earliestFinish);

    double getLatestStart() const;

    void setLatestStart(double latestStart);

    double getLatestFinish() const;

    void setLatestFinish(double latestFinish);

    double getSlackTime() const;

    void setSlackTime(double slackTime);

    int getInDegrees() const;

    void setInDegrees(int inDegrees);

    bool isVisited() const;

    void setVisited(bool visited);

    const string &getName() const;

    void setName(const string &name);

    const vector<shared_ptr<Task> > &getDependencies() const;

    const vector<shared_ptr<Task> > &getChildNodes() const;

    void addChildNode(shared_ptr<Task> newElement);

    void addParentNode(shared_ptr<Task> newElement);

    void deleteParentNode(shared_ptr<Task> newElement);

    void reset();
};
#endif //SCHEDULINGAPP_TASK_H
