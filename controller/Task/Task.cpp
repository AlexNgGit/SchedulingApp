#include "Task.h"

Task::Task(double duration, double cost, const string& name, const vector<shared_ptr<Task> >& dependencies) {
    this->slackTime = 0;
    this->duration = duration;
    this->cost = cost;
    this->name = name;
    this->dependencies = dependencies;
    this->earliestStart = 0;
    this->earliestFinish = 0;
    this->latestStart = 0;
    this->latestFinish = 0;
    dependencies.empty() ? this->in_degrees = 1: this->in_degrees = this->dependencies.size();
    this->visited = false;
}

double Task::getDuration() const {
    return duration;
}

void Task::setDuration(double duration) {
    Task::duration = duration;
}

double Task::getCost() const {
    return cost;
}

void Task::setCost(double cost) {
    Task::cost = cost;
}

double Task::getEarliestStart() const {
    return earliestStart;
}

void Task::setEarliestStart(double earliestStart) {
    Task::earliestStart = earliestStart;
}

double Task::getEarliestFinish() const {
    return earliestFinish;
}

void Task::setEarliestFinish(double earliestFinish) {
    Task::earliestFinish = earliestFinish;
}

double Task::getLatestStart() const {
    return latestStart;
}

void Task::setLatestStart(double latestStart) {
    Task::latestStart = latestStart;
}

double Task::getLatestFinish() const {
    return latestFinish;
}

void Task::setLatestFinish(double latestFinish) {
    Task::latestFinish = latestFinish;
}

double Task::getSlackTime() const {
    return slackTime;
}

void Task::setSlackTime(double slackTime) {
    Task::slackTime = slackTime;
}

int Task::getInDegrees() const {
    return in_degrees;
}

void Task::setInDegrees(int inDegrees) {
    in_degrees = inDegrees;
}

bool Task::isVisited() const {
    return visited;
}

void Task::setVisited(bool visited) {
    Task::visited = visited;
}

const string &Task::getName() const {
    return name;
}

void Task::setName(const string &name) {
    Task::name = name;
}

const vector<shared_ptr<Task> > &Task::getDependencies() const {
    return dependencies;
}


const vector<shared_ptr<Task> > &Task::getChildNodes() const {
    return childNodes;
}

void Task::addChildNode(shared_ptr<Task> newElement) {
    childNodes.push_back(newElement);
}

void Task::addParentNode(shared_ptr<Task> newElement) {
    dependencies.push_back(newElement);
}

void Task::deleteParentNode(shared_ptr<Task> deleteElement) {
   dependencies.erase(remove(dependencies.begin(), dependencies.end(), deleteElement), dependencies.end());
}

void Task::reset() {
    this->earliestStart = 0;
    this->earliestFinish = 0;
    this->latestStart = 0;
    this->latestFinish = 0;
    this->dependencies.size() == 0 ? in_degrees = 1: in_degrees = dependencies.size();
    this->visited = false;
    this->childNodes.erase(childNodes.begin(), childNodes.end());
}
