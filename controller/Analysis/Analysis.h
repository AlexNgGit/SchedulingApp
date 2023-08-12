#ifndef SCHEDULINGAPP_ANALYSIS_H
#define SCHEDULINGAPP_ANALYSIS_H
#include <vector>
#include "../Task/Task.h"


class Analysis {
public:
    std::vector<Task> taskList;
    double ECT;
    std::vector<Task> criticalPath;
    Task Start;
    Task End;
    Analysis(std::vector<Task> input);
    Analysis performAnalysis();
};

#endif //SCHEDULINGAPP_ANALYSIS_H
