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

void Node::setDist(Node *target, int dist) {
    this->dists[target->getNumber()] = dist;
}

int Node::getDist(Node *target) {
    if (this == target) {
        this->setDist(target, 0);
        return 0;
    }
    if (this->dists.count(target->getNumber()) == 0) {
        int updated = 0;
        for (Edge *adj : this->getAdjacent()) {
            if (adj->getOtherNode(this) == target) {
                this->setDist(target, adj->getWeight());
                updated++;
                break;
            }
        }
        if (!updated) { this->setDist(target, 10000 * 50 + 1); }
    }
    return this->dists.at(target->getNumber());
}

void Node::updateSumWeight(int update) {
    this->sumWeight += update;
}

int Node::getSumWeight() const {
    return this->sumWeight;
}

Node::~Node() {
    this->adjacent.clear();
    this->dists.clear();
}
