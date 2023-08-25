#ifndef SCHEDULINGAPP_PROJECT_H
#define SCHEDULINGAPP_PROJECT_H

#include "OpenXLSX.hpp"
#include <string>
#include <vector>
#include "../../controller/Task/Task.h"
#include <future>

using namespace std;
using namespace OpenXLSX;

class Project {
public:
    Project();
    Project(string name);
    void performAnalysis();
    void loadProjectHelper(string pathname);


private:
    string name;
    double ECT;
    vector<shared_ptr<Task> > input;
    vector<vector<shared_ptr<Task>> > bfsGraph;
public:
    const vector<shared_ptr<Task>> &getInput() const;

private:
    vector<shared_ptr<Task> > criticalPath;
    vector<vector<Task> > graphPresentation;
    /* Helpers */
    int loadExcelFiles(string path);
    shared_ptr<Task> findTask(string taskName);
    void addDependecies(vector<string>& dependencies);
};


#endif //SCHEDULINGAPP_PROJECT_H
