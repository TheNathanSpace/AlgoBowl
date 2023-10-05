//
// Created by nathan on 10/4/23.
//

#include "Algorithm.h"

#include <utility>

Algorithm::Algorithm(std::string name, Graph *graph) {
    this->graph = graph;
    this->name = std::move(name);
}

Graph *Algorithm::getGraph() const {
    return graph;
}

void Algorithm::reset() {
    this->graph->reset();
}

void Algorithm::writeToDot(const std::string &algorithm) {
    this->graph->writeToDot(this->getGraph()->getName() + "_" + algorithm);
}

void Algorithm::writeAlgoBowlOutput(const std::string &algorithm) {
    this->graph->writeAlgoBowlOutput(this->getGraph()->getName() + "_" + algorithm);

}

const std::string &Algorithm::getName() const {
    return name;
}
