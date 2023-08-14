#include "Project.h"
#include <vector>
#include <queue>

Project::Project(vector<shared_ptr<Task> > input) {
    this->input = input;

    vector<shared_ptr<Task> > emptySTART;
    shared_ptr<Task> newSTART (new Task(0, 0, "START", emptySTART));
    this->START = shared_ptr<Vertex>(new Vertex(newSTART));

    vector<shared_ptr<Task> > emptyEND;
    shared_ptr<Task> newEND (new Task(0, 0, "END", emptyEND));
    this->END = shared_ptr<Vertex>(new Vertex(newEND));
}

unordered_map<shared_ptr<Task>, shared_ptr<Vertex> > Project::createVertices() {
    unordered_map<shared_ptr<Task>, shared_ptr<Vertex> > verticesMap;
    verticesMap.insert(make_pair(this->START->presentingTask, this->START));
    auto begin = this->input.begin();
    auto end = this->input.end();
    for (auto i = begin; i != end; i++) {
        verticesMap[*i] = shared_ptr<Vertex> (new Vertex(*i));
    }
    return verticesMap;
}

void Project::editInDegree(unordered_map<shared_ptr<Task>, shared_ptr<Vertex> >  verticesMap) {

    auto begin = verticesMap.begin();
    auto end = verticesMap.end();

    for (auto i = begin; i != end; i++) {
        if ((*i).first->dependencies.size() == 0) {
            this->START->presentingTask->dependencies.push_back(((*i).first));
        }
        for (auto element: (*i).first->dependencies) {
            auto currTask = verticesMap[element]->presentingTask;
            auto value = verticesMap[currTask];
            value->in_degrees++;
        }
    }
}

void Project::calculateTime(shared_ptr<Vertex> element) {
    for (auto subElement: element->presentingTask->dependencies){
        element->presentingTask->earliestStart = max(element->presentingTask->earliestStart, subElement->earliestFinish);
    }
    element->presentingTask->earliestFinish =
            element->presentingTask->earliestStart + element->presentingTask->duration;
}

Project Project::bfsAnalysis(unordered_map<shared_ptr<Task>, shared_ptr<Vertex> >  verticesMap) {
        auto firstLayer = vector<shared_ptr<Vertex> >();
        firstLayer.push_back(verticesMap[this->START->presentingTask]);
        bfsMatrix.push_back(firstLayer);
        int i = 0;
        while (bfsMatrix[i].size() != 0) {
            auto newLayer = vector<shared_ptr<Vertex> >();
            bfsMatrix.push_back(newLayer);
            for (auto element: bfsMatrix[i]) {
                element->editInDegree(-1);
                if (element->in_degrees == 0) {
                    bfsMatrix[i + 1].push_back(element);
                    this->calculateTime(element);
                }
            }
        }
}

void Project::calculateEST() {
    for (auto element: bfsMatrix[bfsMatrix.size()-1]) {
        this->ECT = max(element->presentingTask->earliestFinish, this->ECT);
    }
}

void Project::calculateCriticalPath() {
    for (auto element: bfsMatrix) {
        for (auto subElement: element) {
            auto currTask = subElement->presentingTask;
            if (currTask->earliestStart + currTask->duration == currTask->earliestFinish) {
                this->criticalPath.push_back(subElement->presentingTask);
            }
        }
    }
}

Project* Project::getAnalysis() {
    auto map = createVertices();
    editInDegree(map);
    bfsAnalysis(map);
    calculateEST();
    calculateCriticalPath();
    return this;
}


