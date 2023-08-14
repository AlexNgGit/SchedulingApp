#include "Project.h"
#include <vector>
#include <queue>

Project::Project(std::vector<Task*> input) {
    this->input = input;
    vector<Task> emptySTART;
    Task* newSTART = new Task(0, 0, "START", emptySTART);
    this->START = new Vertex(newSTART);

    vector<Task> emptyEND;
    Task* newEND = new Task(0, 0, "END", emptyEND);
    this->END = new Vertex(newEND);
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
    this->verticesMap[this->START->presentingTask] = START;

    auto begin = this->verticesMap.begin();
    auto end = this->verticesMap.end();

    for (auto i = begin; i != end; i++) {
        if ((*i).first->dependencies.size() == 0) {
            this->START->presentingTask->dependencies.push_back(*((*i).first));
        }
        for (auto element: (*i).first->dependencies) {
            auto currTask = this->verticesMap[&element]->presentingTask;
            auto value = this->verticesMap[currTask];
            value->in_degrees++;
        }
    }
}

void Project::calculateTime(Vertex* element) {
    for (auto subElement: element->presentingTask->dependencies){
        element->presentingTask->earliestStart = max(element->presentingTask->earliestStart, subElement.earliestFinish);
    }
    element->presentingTask->earliestFinish =  element->presentingTask->earliestStart + element->presentingTask->duration;
}

Project Project::performAnalysis() {
    try {
        auto firstLayer = vector<Vertex*>();
        firstLayer.push_back(this->verticesMap[this->START->presentingTask]);
        bfsMatrix.push_back(firstLayer);
        int i = 0;
        while (bfsMatrix[i].size() != 0) {
            auto newLayer = vector<Vertex *>();
            bfsMatrix.push_back(newLayer);
            for (auto element: bfsMatrix[i]) {
                element->editInDegree(-1);
                if (element->in_degrees == 0) {
                    bfsMatrix[i + 1].push_back(element);
                    this->calculateTime(element);
                }
            }
        }
    } catch (logic_error) {
        throw logic_error("NOT IMPLEMENTED YET");
    }
}

void Project::getEST() {
    for (auto element: bfsMatrix[bfsMatrix.size()-1]) {
        this->ECT = max(element->presentingTask->earliestFinish, this->ECT);
    }
}


