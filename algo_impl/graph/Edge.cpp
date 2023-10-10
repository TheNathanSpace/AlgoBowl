//
// Created by nathan on 10/2/23.
//

#include <iostream>
#include "Edge.h"

Edge::Edge(int weight, Node *node1, Node *node2) {
    this->weight = weight;
    this->nodes = std::pair(node1, node2);
}

Node *Edge::getOtherNode(Node *startingNode) const {
    if (this->nodes.first->getNumber() == startingNode->getNumber()) {
        return this->nodes.second;
    } else {
        return this->nodes.first;
    }
}

int Edge::getWeight() const {
    return weight;
}

bool Edge::isSelected() const {
    return selected;
}

void Edge::setSelected(bool selected) {
    this->selected = selected;
}

std::pair<Node *, Node *> Edge::getNodes() {
    return this->nodes;
}
