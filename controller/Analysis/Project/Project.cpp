#include "Project.h"
#include <vector>
#include <queue>

Project::Project(std::vector<Task*> input) {
    this->input = input;
}

void Project::createVertices() {
    auto begin = this->input.begin();
    auto end = this->input.end();
    for (auto i = begin; i != end; i++) {
        Vertex* value =  new Vertex(*i);
        this->verticesMap[*i] = value;
    }
}

void Project::editInDegree() {
    vector<Task> emptySTART;
    Task* newSTART = new Task(0, 0, "START", emptySTART);
    Vertex* START = new Vertex(newSTART);
    this->verticesMap[newSTART] = START;

    /*vector<Task> emptyEND;
    Task* newEND = new Task(0, 0, "END", emptyEND);
    Vertex* END = new Vertex(newEND);*/

    auto begin = this->verticesMap.begin();
    auto end = this->verticesMap.end();
    for (auto i = begin; i != end; i++) {
        if ((*i).first->dependencies.size() == 0) {
            START->presentingTask->dependencies.push_back(*((*i).first));
        }
        for (auto element: (*i).first->dependencies) {
            auto currTask = this->verticesMap[&element]->presentingTask;
            auto value = this->verticesMap[currTask];
            value->in_degrees++;
        }
    }
}

Project Project::performAnalysis() {
    try {
        std::queue<std::unique_ptr<Vertex>> queue = {};
    } catch (std::logic_error) {
        printf("NOT IMPLEMENTED YET");
    }
}


