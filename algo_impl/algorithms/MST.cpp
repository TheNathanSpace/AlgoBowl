//
// Created by nathan on 10/4/23.
//

#include "MST.h"

void MST::run() {
    // TODO: Implement MST here, choosing selected Edges on the Graph.
}

MST::MST(Graph *graph) : Algorithm("mst", graph) {
}

void MST::writeToDot() {
    Algorithm::writeToDot(this->getName());
}

void MST::writeAlgoBowlOutput() {
    Algorithm::writeAlgoBowlOutput(this->getName());
}
