#include "Vertex.h"

using namespace std;
Vertex::Vertex(shared_ptr<Task> presentingTask) {
    this->presentingTask = presentingTask;
    this->in_degrees = 0;
}

void Vertex::editInDegree(int offset) {
    this->in_degrees += offset;
}