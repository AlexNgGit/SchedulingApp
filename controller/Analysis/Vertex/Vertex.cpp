#include "Vertex.h"

using namespace std;
Vertex::Vertex(Task* presentingTask) {
    this->presentingTask = presentingTask;
    this->in_degrees = 0;
}

void Vertex::editInDegree(int offset) {
    this->in_degrees += offset;
}