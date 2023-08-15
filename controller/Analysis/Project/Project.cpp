#include "Project.h"
#include <vector>

Project::Project(vector<shared_ptr<Task> > input) {
    this->input = input;
    this->START.reset(new Task(0, 0, "START", vector<shared_ptr<Task> >()));
}

void Project::createVertices() {
    for (const auto& task : this->input) {
        if (task->dependencies.size() == 0) {
            task->dependencies.push_back(START);
        }
        for (const auto& parentTask: task->dependencies) {
            parentTask->childNodes.push_back(task);
        }
    }
}

void Project::calculateTime(shared_ptr<Task> element) {
    auto& task = element;

    for (const auto& subElement : task->dependencies) {
        task->earliestStart = std::max(task->earliestStart, subElement->earliestFinish);
    }

    task->earliestFinish = task->earliestStart + task->duration;
}

void Project::bfsAnalysis() {
        auto firstLayer = vector<shared_ptr<Task> >();
        firstLayer.push_back(this->START);
        bfsMatrix.push_back(firstLayer);
        int i = 0;

    while (!bfsMatrix[i].empty()) {
        std::vector<std::shared_ptr<Task > > newLayer;
        bfsMatrix.push_back(newLayer);
        for (const auto& element : bfsMatrix[i]) {
            for (const auto& subElement : element->childNodes) {
                subElement->in_degrees--;
                if (subElement->in_degrees == 0) {
                    if (subElement->visited) {
                        throw std::logic_error("INVALID GRAPH HAS CYCLE AT ");
                    }
                    bfsMatrix[i + 1].push_back(subElement);
                    calculateTime(subElement);
                    subElement->visited = true;
                }
            }
        }
        i++;
    }
}

void Project::calculateEST() {
    for (auto element: bfsMatrix[bfsMatrix.size()-2]) {
        this->ECT = max(element->earliestFinish, this->ECT);
    }
}

void Project::calculateCriticalPath() {
    for (auto element: bfsMatrix) {
        for (auto subElement: element) {
            auto currTask = subElement;
            if (currTask->earliestStart + currTask->duration == currTask->earliestFinish) {
                this->criticalPath.push_back(subElement);
            }
        }
    }
}

Project* Project::getAnalysis() {
    createVertices();
    bfsAnalysis();
    calculateEST();
    //calculateCriticalPath();
    return this;
}


