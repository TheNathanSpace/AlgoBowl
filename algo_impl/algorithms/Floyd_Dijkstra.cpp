//
// Created by Kai Hoshijo on 10/10/2023.
//

#include "Floyd_Dijkstra.h"
#include <queue>
#include <vector>
#include <unordered_map>
#include <algorithm>


void Floyd_Dijkstra::run() {
    /******************
    * Floyd-Warshall *
    *****************/
    int shortestNodeSource = -1;
    int shortestTotalWeight = MAX_EDGE;
    int k = 0;
    // Calculates the source node with the shortest path to every other node
    // Won't start at a required node if a normal node creates the shortest path
    // Modified to search from any one node to all the required nodes
//    for (Node *kNode : getGraph()->getAllNodes()) {
//        // Effectively a brute force algorithm
//        for (Node *iNode : getGraph()->getAllNodes()) {
//            for (Node *jNode: getGraph()->getAllNodes()) {
//                // Check if distance from i to j is less than the distance
//                // of distance from i to k plus distance from k to j
//                int sumDist = iNode->getDist(kNode) + kNode->getDist(jNode);
//                int minDist = std::min(iNode->getDist(jNode), sumDist);
//                // Add that distance to the min weights for that node
//                iNode->setDist(jNode, minDist);
//            }
//            int currentSum = 0;
//            for (int nodeNum : getGraph()->getRequiredNodes()) {
//                int curDist = iNode->getDist(getGraph()->getNode(nodeNum));
//                if (curDist == MAX_EDGE) {
//                    currentSum = MAX_EDGE;
//                } else {
//                    currentSum += curDist;
//                }
//            }
//            if (currentSum < shortestTotalWeight) {
//                shortestTotalWeight = currentSum;
//                shortestNodeSource = iNode->getNumber();
//            }
//        }
//        k++;
//    }
    // Start from min weight test
    // Get first required node with the shortest edge weights
//    int minSumWeight = MAX_EDGE; // Only 10000 edges are allowed at max weight 50
//    for (int nodeNum : getGraph()->getRequiredNodes()) {
//        Node *node = getGraph()->getNode(nodeNum);
//        if (node->getSumWeight() <= minSumWeight) {
//            minSumWeight = node->getSumWeight();
//            shortestNodeSource = nodeNum;
//        }
//    }
    // After this algorithm finishes, the smallest distances to all nodes is computed
    /**************
    * 2D-Dijkstra *
    **************/
    int sweight = -1;
    int actual_shortest = -1;
    std::unordered_map<int, std::tuple<Edge *, int>> min_dists;
    std::unordered_map<Node *, Edge *> prev;
    std::unordered_map<Node *, Edge *> saved_prev;
    for (Node *starting: getGraph()->getAllNodes()) {
        int testWeight = 0;
        // Starts building from the source node that was just computed
        // Continues building the graph until every required node has been met
        std::priority_queue<std::tuple<int, int>, std::vector<std::tuple<int, int>>, std::greater<>> nodes;
        shortestNodeSource = starting->getNumber();
        // Tuple represents <dist, node num>
        nodes.emplace(0, shortestNodeSource);
        min_dists[shortestNodeSource] = std::tuple(nullptr, 0);
        int metRequired = 0; // Once this equals # of required nums, stop graph

        while (!nodes.empty()) {
            // Get the node with the min dist
            std::tuple<int, int> currentElm = nodes.top();
            Node *currentNode = getGraph()->getNode(std::get<1>(currentElm));
            nodes.pop();

            // Iterate over each neighbor to reduce dist
            for (Edge *adj: currentNode->getAdjacent()) {
                Node *adjNode = adj->getOtherNode(currentNode);
                // Set distance to infinity if it isn't present
                if (min_dists.count(adjNode->getNumber()) == 0) {
                    min_dists[adjNode->getNumber()] = std::tuple(adj, MAX_EDGE);
                }
                int alt = std::get<1>(min_dists[currentNode->getNumber()]) + adj->getWeight();
                // If the dist equals the distance from Floyd then the shortest path has been found
//            if (adjNode->isRequired() && getGraph()->getNode(shortestNodeSource)->getDist(adjNode) == std::get<1>(min_dists[adjNode->getNumber()])) {
//                metRequired++;
//                continue;
//            }
                // Check if the new distance is lower than the saved distance
                int distance = std::get<1>(min_dists[adjNode->getNumber()]);
                if (alt < distance) {
                    prev[adjNode] = adj;
                    min_dists[adjNode->getNumber()] = std::tuple(adj, alt);
                    nodes.push(std::tuple(std::get<1>(min_dists[adjNode->getNumber()]), adjNode->getNumber()));
                }
            }
        }
        // Iterate over required nodes and select all edges back to the source node
        Node *finalParent = getGraph()->getNode(shortestNodeSource);
        for (int requiredNode: getGraph()->getRequiredNodes()) {
            // Get the requiredNode's parent edge
            Edge *parentEdge = prev[getGraph()->getNode(requiredNode)];
            if (parentEdge == nullptr) {
                continue;
            }
            Node *parentNode = parentEdge->getOtherNode(getGraph()->getNode(requiredNode));
            // Repeat until the parent node is equal to the source node

            do {
                // Select edge since it connects the requiredNode to the source Node
                if (!parentEdge->isSelected()) {
                    getGraph()->selectEdge(parentEdge);
                    testWeight += parentEdge->getWeight();
                }
                parentEdge = prev[parentNode];
                if (parentEdge == nullptr) {
                    continue;
                }
                parentNode = parentEdge->getOtherNode(parentNode);
            } while (parentNode != finalParent || parentEdge != nullptr);
        }
        if (testWeight < sweight || sweight == -1) {
            sweight = testWeight;
            saved_prev = prev;
            actual_shortest = shortestNodeSource;
            auto edges = getGraph()->getSelectedEdges();
            for (Edge *selected : edges) {
                getGraph()->unselectEdge(selected);
            }
        }
        // Clearing all the memory
        min_dists.clear();
        nodes = std::priority_queue<std::tuple<int, int>, std::vector<std::tuple<int, int>>, std::greater<>>();
        prev.clear();
        auto edges = getGraph()->getSelectedEdges();
        for (Edge *selected : edges) {
            getGraph()->unselectEdge(selected);
        }
    }
    Node *finalParent = getGraph()->getNode(actual_shortest);
    for (int requiredNode: getGraph()->getRequiredNodes()) {
        // Get the requiredNode's parent edge
        Edge *parentEdge = saved_prev[getGraph()->getNode(requiredNode)];
        if (parentEdge == nullptr) {
            continue;
        }
        Node *parentNode = parentEdge->getOtherNode(getGraph()->getNode(requiredNode));
        // Repeat until the parent node is equal to the source node

        do {
            // Select edge since it connects the requiredNode to the source Node
            if (!parentEdge->isSelected()) {
                getGraph()->selectEdge(parentEdge);
            }
            parentEdge = saved_prev[parentNode];
            if (parentEdge == nullptr) {
                continue;
            }
            parentNode = parentEdge->getOtherNode(parentNode);
        } while (parentNode != finalParent || parentEdge != nullptr);
    }
}

Floyd_Dijkstra::Floyd_Dijkstra(Graph *graph) : Algorithm("fl_dka_3", graph) {
}

void Floyd_Dijkstra::writeToDot() {
    Algorithm::writeToDot(this->getName());
}

std::string Floyd_Dijkstra::writeAlgoBowlOutput() {
    return Algorithm::writeAlgoBowlOutput(this->getName());
}
