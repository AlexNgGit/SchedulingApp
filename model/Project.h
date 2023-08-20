#ifndef SCHEDULINGAPP_PROJECT_H
#define SCHEDULINGAPP_PROJECT_H

#include <OpenXLSX.hpp>
#include <string>
#include <vector>
#include "../controller/Task/Task.h"

using namespace std;
using namespace OpenXLSX;

class Project {
public:
    Project();
    Project(string name);
    int loadProject(string pathname);
    void performAnalysis();

private:
    string name;
    double ECT;
    vector<shared_ptr<Task> > input;
    vector<shared_ptr<Task> > criticalPath;
    vector<vector<Task> > graphPresentation;
    /* Helpers */
    int loadExcelFiles(string path);
    shared_ptr<Task> findTask(string taskName);
};


#endif //SCHEDULINGAPP_PROJECT_H
