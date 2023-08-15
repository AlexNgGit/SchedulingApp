#include "Project.h"
#include <vector>

Project::Project(vector<shared_ptr<Task> > input) {
    this->input = input;
    this->START.reset(new Task(0, 0, "START", vector<shared_ptr<Task> >()));
    this->END.reset(new Task(0, 0, "END", vector<shared_ptr<Task> >()));
}

void  Project::reset() {
    if (this->START->childNodes.size() != 0) {
        for (auto element: this->input) {
            element->earliestStart = 0;
            element->earliestFinish = 0;
            element->latestStart = 0;
            element->latestFinish = 0;
            element->dependencies.size() == 0 ? element->in_degrees = 1: element->in_degrees = element->dependencies.size();
            element->visited = false;
        }
    }
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
        task->earliestStart = max(task->earliestStart, subElement->earliestFinish);
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
        END->dependencies.push_back(element);
    }
    END->earliestStart = END->earliestFinish = END->latestFinish = END->latestStart = ECT;
    bfsMatrix[bfsMatrix.size() - 1] = vector<shared_ptr<Task> >();
    bfsMatrix[bfsMatrix.size() - 1].push_back(END);
}

void Project::calculateCriticalPath(shared_ptr<Task> currElement) {
   for (auto subNode: currElement->dependencies) {
       subNode->latestFinish = currElement->latestStart;
       subNode->latestStart = subNode->latestFinish - subNode->duration;
       if (subNode->latestFinish - subNode->earliestFinish == 0 && subNode != START) {
           criticalPath.push_back(subNode);
       }
       this->calculateCriticalPath(subNode);
   }

}

Project* Project::getAnalysis() {
    reset();
    createVertices();
    bfsAnalysis();
    calculateEST();
    calculateCriticalPath(this->END);
    return this;
}


