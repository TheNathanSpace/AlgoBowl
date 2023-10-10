//
// Created by nathan on 10/2/23.
//

#include "Node.h"

Node::Node(int nodeNum) {
    this->number = nodeNum;
}

void Node::addAdjacent(Edge *adjacentEdge) {
    this->adjacent.push_back(adjacentEdge);
}

int Node::getNumber() const {
    return number;
}

const std::vector<Edge *> &Node::getAdjacent() const {
    return adjacent;
}

bool Node::isRequired() const {
    return required;
}

void Node::setRequired(bool aRequired) {
    required = aRequired;
}

bool Node::isVisited() const {
    return visited;
}

void Node::setVisited(bool visited) {
    this->visited = visited;
}
