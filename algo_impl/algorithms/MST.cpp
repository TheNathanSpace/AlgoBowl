//
// Created by nathan on 10/4/23.
//

#include "MST.h"

Edge *getCheapestEdge(vector<Node *> visited) {
    int min = 51; // No edge is greater than 50
    Edge *minEdge = nullptr;
    for (Node *node : visited) {
        for (Edge *edge : node.getAdjacent()) {
            // Check if the node isn't in the MST already
            auto check = std::find(visited.begin(), visited.end(), edge);
            if (edge.getWeight() < min && check != visited.end()) {
                min = edge.getWeight();
                minEdge = edge;
            }
        }
    }
    return minEdge;
}

void MST::run() {
    // Setting up the random number generator
    srand((unsigned) time(NULL));
    int random = rand();

    // Using Prim's algorithm
    // Choosing a random node -> change to node with cheapest edges
    int firstNodeNum = random % graph->getNumNodes();
    vector<Node *> visited = new vector<Node *>();
    visited.push_back(graph->getNode(firstNodeNum));
    // repeat until all nodes are in the formula
    while (visited.size() != graph->getNumNodes()) {
        Edge *cheapestEdge = getCheapestEdge(visited);
        // selected nodes are effectively in the new MST
        cheapestEdge.setSelected(true);
        visited.push_back(cheapestEdge.getOtherNode(currentNode));
    }
}

MST::MST(Graph *graph) : Algorithm("mst", graph) {
}

void MST::writeToDot() {
    Algorithm::writeToDot(this->getName());
}

void MST::writeAlgoBowlOutput() {
    Algorithm::writeAlgoBowlOutput(this->getName());
}
