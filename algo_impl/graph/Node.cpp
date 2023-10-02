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
