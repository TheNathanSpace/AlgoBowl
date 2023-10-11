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
    int shortestTotalWeight = 10000 * 50 + 1;
    // Calculates the source node with the shortest path to every other node
    // Won't start at a required node if a normal node creates the shortest path
    // Modified to search from any one node to all the required nodes
    for (int k = 1; k <= getGraph()->getNumNodes(); k++) {
        Node *kNode = getGraph()->getNode(k);
        // Effectively a brute force algorithm
        for (int i = 1; i <= getGraph()->getNumNodes(); i++) {
            Node *iNode = getGraph()->getNode(i);
            for (int j = 1; j <= getGraph()->getNumNodes(); j++) {
                Node *jNode = getGraph()->getNode(j);
                // Check if distance from i to j is less than the distance
                // of distance from i to k plus distance from k to j
                int sumDist = iNode->getDist(kNode) + kNode->getDist(jNode);
                int minDist = std::min(iNode->getDist(jNode), sumDist);
                // Add that distance to the min weights for that node
                iNode->setDist(jNode, minDist);
            }
            int currentSum = 0;
            for (int nodeNum : getGraph()->getRequiredNodes()) {
                currentSum += iNode->getDist(getGraph()->getNode(nodeNum));
            }
            if (currentSum <= shortestTotalWeight) {
                shortestTotalWeight = currentSum;
                shortestNodeSource = i;
            }
        }
    }
    // After this algorithm finishes, the smallest distances to all nodes is computed
    /**************
    * 2D-Dijkstra *
    **************/
    // Starts building from the source node that was just computed
    // Continues building the graph until every required node has been met
    std::priority_queue<std::tuple<int, int>, std::vector<std::tuple<int,int>>, std::greater<>> nodes;
    // Tuple represents <dist, node num>
    nodes.emplace(0, shortestNodeSource);
    std::unordered_map<int, std::tuple<Edge *, int>> min_dists;
    std::unordered_map<Node*, Edge*> prev;
    min_dists[shortestNodeSource] = std::tuple(nullptr, 0);
    int metRequired = 0; // Once this equals # of required nums, stop graph

    while (!nodes.empty() || metRequired < getGraph()->getRequiredNodes().size()) {
        // Get the node with the min dist
        std::tuple<int, int> currentElm = nodes.top();
        Node *currentNode = getGraph()->getNode(std::get<1>(currentElm));
        nodes.pop();
        getGraph()->visitNode(currentNode);

        // Iterate over each neighbor to reduce dist
        for (Edge *adj : currentNode->getAdjacent()) {
            Node *adjNode = adj->getOtherNode(currentNode);
            // Set distance to infinity if it isn't present
            if (min_dists.count(adjNode->getNumber()) == 0) {
                min_dists[adjNode->getNumber()] = std::tuple(adj, 10000 * 50 + 1);
            }
            int alt = std::get<1>(min_dists[currentNode->getNumber()]) + adj->getWeight();
            // If the dist equals the distance from Floyd then the shortest path has been found
            if (adjNode->isRequired() && getGraph()->getNode(shortestNodeSource)->getDist(adjNode) == std::get<1>(min_dists[adjNode->getNumber()])) {
                metRequired++;
                continue;
            }
            // Check if the new distance is lower than the saved distance
            if (alt < std::get<1>(min_dists[adjNode->getNumber()])) {
                getGraph()->visitNode(adjNode);
                prev[adjNode] = adj;
                min_dists[adjNode->getNumber()] = std::tuple(adj, alt);
                nodes.emplace(std::get<1>(min_dists[adjNode->getNumber()]), currentNode->getNumber());
            }
        }
    }
    // Iterate over required nodes and select all edges back to the source node
    Node *finalParent = getGraph()->getNode(shortestNodeSource);
    for (int requiredNode : getGraph()->getRequiredNodes()) {
        // Get the requiredNode's parent edge
        Edge *parentEdge = prev[getGraph()->getNode(requiredNode)];
        if (parentEdge == nullptr) {
            continue;
        }
        Node *parentNode = parentEdge->getOtherNode(getGraph()->getNode(requiredNode));
        // Repeat until the parent node is equal to the source node
        do {
            // Select edge since it connects the requiredNode to the source Node
            if (!parentEdge->isSelected()) getGraph()->selectEdge(parentEdge);
            parentEdge = prev[parentNode];
            if (parentEdge == nullptr) {
                continue;
            }
            parentNode = parentEdge->getOtherNode(parentNode);
        } while (parentNode != finalParent || parentEdge != nullptr);

    }


    min_dists.clear();
    nodes = std::priority_queue<std::tuple<int, int>, std::vector<std::tuple<int,int>>, std::greater<>>();
    prev.clear();
}

Floyd_Dijkstra::Floyd_Dijkstra(Graph *graph) : Algorithm("fl_dk", graph) {
}

void Floyd_Dijkstra::writeToDot() {
    Algorithm::writeToDot(this->getName());
}

std::string Floyd_Dijkstra::writeAlgoBowlOutput() {
    return Algorithm::writeAlgoBowlOutput(this->getName());
}
