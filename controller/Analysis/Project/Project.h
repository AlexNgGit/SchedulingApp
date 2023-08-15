#ifndef SCHEDULINGAPP_ANALYSIS_H
#define SCHEDULINGAPP_ANALYSIS_H
#include <vector>
#include "../../Task/Task.h"
/**
 * Project is an information object that accept an input of Tasks (more details are in ../Task/Task.h) to generate:
 *      1) Estimated earliest time
 *      2) An array (vector implementation) of critical paths
 *      3) A topological sorted array of all the tasks
 *
 * The performAnalysis function will based on Critical Path Method (CPM) to retrieve those information. Explicitly, the
 * CRM will go through the input array and visit the dependent task of each node/element. If a node has an empty
 * dependencies array then a START node presenting the very first node of the input.
 *
 * The earliest completed time (ECT) will be the total earliest time the project can finish.
 *
 * The critical path will include all the nodes that have of a zero subtraction earliestStart time and the current earliest
 * finish time.
 *
 *
 */
using namespace std;
class Project {
public:
    double ECT;
    std::vector<shared_ptr<Task> > criticalPath;
    vector<shared_ptr<Task> > input;
    vector<vector<shared_ptr<Task> > > bfsMatrix;
    shared_ptr<Task> START;
    shared_ptr<Task> END;

    Project(std::vector<shared_ptr<Task > > input);
    void createVertices();
    void editInDegree(unordered_map<shared_ptr<Task>, shared_ptr<Task> >);
    void bfsAnalysis();
    void calculateTime(shared_ptr<Task> element);
    void calculateEST();
    void calculateCriticalPath(shared_ptr<Task> currElement);
    Project* getAnalysis();
};

#endif //SCHEDULINGAPP_ANALYSIS_H
