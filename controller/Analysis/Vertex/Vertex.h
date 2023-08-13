#ifndef SCHEDULINGAPP_VERTEX_H
#define SCHEDULINGAPP_VERTEX_H
#include <vector>
#include <string>
#include "../../Task/Task.h"

class Vertex {
public:
    double weight;
    std::vector<Task> parentNodes;
    int in_degrees;
    std::string name;
    Vertex(double weight, std::string name);
    Vertex(double weight, std::string name, std::vector<Task> dependencies);
    void addParentNodes (std::vector<Task> input);
    void editInDegree(int offset);
};


#endif //SCHEDULINGAPP_VERTEX_H
