//
// Created by nathan on 10/4/23.
//

#include "MST.h"
#include <algorithm>
#include <iostream>

std::tuple<Node *, Edge *> MST::getCheapestEdge() {
    int minWeight = 51; // No edge is greater than 50
    Edge *minEdge = nullptr;
    Node *newNode = nullptr;
    auto selectedEdges = getGraph()->getSelectedEdges();

    /*
     * For every Node in the current MST, check each adjacent Edge.
     * Finally, return the cheapest of all of them.
     */
    for (Node *node: getGraph()->getVisitedNodes()) {
        for (Edge *edge: node->getAdjacent()) {
            // If the Edge isn't cheaper than the current cheapest,
            // fail quickly and move on
            if (edge->getWeight() >= minWeight) {
                continue;
            }

            // Check that the Edge expands the Graph 
            Node *otherNode = edge->getOtherNode(node);
            if (!otherNode->isVisited()) {
                minWeight = edge->getWeight();
                minEdge = edge;
                newNode = otherNode;
            }
        }
    }
    return {newNode, minEdge};
}

void MST::run() {
    /********************
     * Prim's algorithm *
     ********************/

    // Get first required node -> change to node with cheapest edges
    int firstNodeNum = getGraph()->getRequiredNodes().at(0);

    // Mark first node as visited
    getGraph()->visitNode(getGraph()->getNode(firstNodeNum));

    // Repeat until all nodes are in the tree
    auto visitedNodes = getGraph()->getVisitedNodes();
    while (visitedNodes.size() != getGraph()->getNumNodes()) {
        auto [newNode, cheapestEdge] = getCheapestEdge();

        // I think this means no new Edge was found
        if (cheapestEdge == nullptr || newNode == nullptr) {
            return;
        }

        // Selected Node and Edge are now in the new MST
        getGraph()->selectEdge(cheapestEdge);
        getGraph()->visitNode(newNode);
    }
}

MST::MST(Graph *graph) : Algorithm("mst", graph) {
}

void MST::writeToDot() {
    Algorithm::writeToDot(this->getName());
}

std::string MST::writeAlgoBowlOutput() {
    return Algorithm::writeAlgoBowlOutput(this->getName());
}
