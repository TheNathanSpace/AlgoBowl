//
// Created by nathan on 10/4/23.
//

#include "Algorithm.h"

Algorithm::Algorithm(Graph *graph) {
    this->graph = graph;
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
