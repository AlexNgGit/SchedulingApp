#include "Vertex.h"

Vertex::Vertex(double weight, std::string name) {
    this->in_degrees = 0;
    this->weight = weight;
    this->name = name;
}

Vertex::Vertex(double weight, std::string name, std::vector<Task> dependencies) {
    this->in_degrees = 0;
    this->weight = weight;
    this->name = name;
    this->parentNodes = dependencies;
}

void Vertex::addParentNodes(std::vector<Task> input) {
    this->parentNodes = input;
}

void Vertex::editInDegree(int offset) {
    this->in_degrees += offset;
}