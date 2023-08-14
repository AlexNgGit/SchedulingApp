#ifndef SCHEDULINGAPP_VERTEX_H
#define SCHEDULINGAPP_VERTEX_H
#include <vector>
#include <string>
#include "../../Task/Task.h"

class Vertex {
public:
    int in_degrees;
    Task* presentingTask;
    Vertex(Task* presentingTask);
    void editInDegree(int offset);
};


#endif //SCHEDULINGAPP_VERTEX_H
