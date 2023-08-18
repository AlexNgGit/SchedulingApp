#include "ProjectTool.h"
#include <vector>

ProjectTool::ProjectTool(vector<shared_ptr<Task> > input) {
    this->ECT = 0;
    this->input = input;
    this->START.reset(new Task(0, 0, "START", vector<shared_ptr<Task> >()));
    this->END.reset(new Task(0, 0, "END", vector<shared_ptr<Task> >()));
}

void  ProjectTool::reset() {
    if (!this->START->getDependencies().empty()) {
        for (auto element: this->input) {
            element->reset();
        }
    }
}

void ProjectTool::createVertices() {
    for (const auto& task : this->input) {
        if (task->getDependencies().size() == 0) {
            task->addParentNode(START);
        }
        for (const auto& parentTask: task->getDependencies()) {
            parentTask->addChildNode(task);
        }
    }
}

void ProjectTool::calculateTime(shared_ptr<Task> element) {
    auto& task = element;
    for (const auto& subElement : task->getDependencies()) {
        task->setEarliestStart(max(task->getEarliestStart(), subElement->getEarliestFinish()));
    }
    task->setEarliestFinish(task->getEarliestStart() + task->getDuration());
}

void ProjectTool::bfsAnalysis() {
        auto firstLayer = vector<shared_ptr<Task> >();
        firstLayer.push_back(this->START);
        bfsMatrix.push_back(firstLayer);
        int i = 0;

    while (!bfsMatrix[i].empty()) {
        std::vector<std::shared_ptr<Task > > newLayer;
        bfsMatrix.push_back(newLayer);
        for (const auto& element : bfsMatrix[i]) {
            for (const auto& subElement : element->getChildNodes()) {
                if (subElement->isVisited()) {
                    throw std::logic_error("INVALID GRAPH HAS CYCLE AT ");
                }
                auto newDegree = subElement->getInDegrees() - 1;
                subElement->setInDegrees(newDegree);
                if (subElement->getInDegrees() == 0) {
                    bfsMatrix[i + 1].push_back(subElement);
                    calculateTime(subElement);
                }
            }
            element->setVisited(true);
        }
        i++;
    }
}

void ProjectTool::calculateEST() {
    for (auto element: bfsMatrix[bfsMatrix.size()-2]) {
        this->ECT = max(element->getEarliestFinish(), this->ECT);
        END->addParentNode(element);
    }
    END->setLatestFinish(ECT); END->setLatestStart(ECT); END->setEarliestFinish(ECT); END->setEarliestStart(ECT);
    bfsMatrix[bfsMatrix.size() - 1] = vector<shared_ptr<Task> >();
    bfsMatrix[bfsMatrix.size() - 1].push_back(END);
}

void ProjectTool::calculateCriticalPath(const shared_ptr<Task>& currElement) {
   for (auto subNode: currElement->getDependencies()) {
       subNode->setLatestFinish(currElement->getLatestStart());
       subNode->setLatestStart(subNode->getLatestFinish() - subNode->getDuration());
       subNode->setSlackTime(subNode->getLatestFinish() - subNode->getEarliestFinish());
       if (subNode->getSlackTime() == 0 && subNode != START) {
           criticalPath.push_back(subNode);
       }
       this->calculateCriticalPath(subNode);
   }
}

ProjectTool* ProjectTool::getAnalysis() {
    reset();
    createVertices();
    bfsAnalysis();
    calculateEST();
    calculateCriticalPath(this->END);
    return this;
}


