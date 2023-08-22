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
    future<int> addTasks(string pathName);

private:
    string name;
    double ECT;
    vector<shared_ptr<Task> > input;
public:
    const vector<shared_ptr<Task>> &getInput() const;

private:
    vector<shared_ptr<Task> > criticalPath;
    vector<vector<Task> > graphPresentation;
    /* Helpers */
    int loadExcelFiles(string path);
    shared_ptr<Task> findTask(string taskName);
    int loadProjectHelper(string pathname);
    int addDependecies(int rowCount, const XLWorksheet& currSheet);

};


#endif //SCHEDULINGAPP_PROJECT_H
