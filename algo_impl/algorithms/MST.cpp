//
// Created by nathan on 10/4/23.
//

#include "MST.h"

void MST::run() {

}

MST::MST(Graph *graph) : Algorithm(graph) {
}

void MST::writeToDot() {
    Algorithm::writeToDot("mst");
}

void MST::writeAlgoBowlOutput() {
    Algorithm::writeAlgoBowlOutput("mst");
}
