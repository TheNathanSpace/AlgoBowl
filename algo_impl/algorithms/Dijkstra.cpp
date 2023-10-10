//
// Created by nathan on 10/10/23.
//

#include "Dijkstra.h"
#include <climits>
#include <utility>
#include <iostream>

class DijkstraPath {
public:
    DijkstraPath(Node *startingNode, Node *targetNode) : startingNode(startingNode), currentNode(targetNode) {}

    [[nodiscard]] Node *getStartingNode() const {
        return startingNode;
    }

    [[nodiscard]] Node *getCurrentNode() const {
        return currentNode;
    }

    [[nodiscard]] std::vector<Edge *> &getPath() {
        return path;
    }

    [[nodiscard]] int getPathDistance() const {
        return pathDistance;
    }

private:
    Node *startingNode;
    Node *currentNode;
    std::vector<Edge *> path;
    int pathDistance = INT_MAX;
public:
    void setPathDistance(int pathDistance) {
        DijkstraPath::pathDistance = pathDistance;
    }

    void copyPath(std::vector<Edge *> otherPath, Edge *adjEdge) {
        this->path = std::move(otherPath);
        this->path.push_back(adjEdge);
    }
};

void Dijkstra::run() {
    /**************************************************
     * Dijkstra's algorithm                           *
     * there's no way this is correct but WOOHOOOOOOO *
     *************************************************/

    std::unordered_map<int, std::unordered_map<int, DijkstraPath *> *> outerPaths;

    for (int outerNodeNum: getGraph()->getRequiredNodes()) {
//        std::cout << "    Starting nodes for " << outerNodeNum << std::endl;

        Node *startingNode = getGraph()->getNode(outerNodeNum);
        std::set<Node *> unvisited;
        auto paths = new std::unordered_map<int, DijkstraPath *>;
        outerPaths.insert(std::pair(outerNodeNum, paths));

        // Initialize paths
        for (auto it: getGraph()->getNodeMap()) {
            paths->insert(std::pair(it.second->getNumber(), new DijkstraPath(startingNode, it.second)));
            unvisited.insert(it.second);
        }
        paths->find(startingNode->getNumber())->second->setPathDistance(0);

        Node *currentNode = startingNode;
        while (!unvisited.empty()) {
//            std::cout << "        Working to relax through " << currentNode->getNumber() << std::endl;
            DijkstraPath *currentNodePath = paths->find(currentNode->getNumber())->second;

            // Relax each adjacent edge
            for (Edge *adjEdge: startingNode->getAdjacent()) {
                Node *otherNode = adjEdge->getOtherNode(startingNode);
                if (unvisited.find(otherNode) != unvisited.end()) {
                    // Update distance through current node
                    int tentDistance = currentNodePath->getPathDistance() + adjEdge->getWeight();
                    DijkstraPath *otherNodePath = paths->find(otherNode->getNumber())->second;
                    if (tentDistance < otherNodePath->getPathDistance()) {
                        // TODO: not always set? the path comparison at the end sometimes compares MAX_INT to itself
                        otherNodePath->setPathDistance(tentDistance);
                        otherNodePath->copyPath(currentNodePath->getPath(), adjEdge);
                    }
                }
            }

            // Find the next lowest cost unvisited node
            unvisited.erase(currentNode);

            int cheapestWeight = INT_MAX;
            Node *cheapestNode = nullptr;
            for (auto node: unvisited) {
                if (paths->find(node->getNumber())->second->getPathDistance() < cheapestWeight) {
                    cheapestWeight = paths->find(node->getNumber())->second->getPathDistance();
                    cheapestNode = node;
                }
            }
            if (cheapestNode == nullptr) {
                break;
            }
            currentNode = cheapestNode;
        }
    }

    /*
     * Do MST?
     *   1. For each required Node:
     *     a. Find cheapest path from other Nodes to it
     *     b. Select edges of the cheapest path
     */
    for (auto targetNodeNum: getGraph()->getRequiredNodes()) {
        Node *requiredNode = getGraph()->getNode(targetNodeNum);
        std::vector<Edge *> *cheapestPath;
        int cheapestPathDistance = INT_MAX;
        int cheapestStartingNode;

//        std::cout << "    Working to reach node " << targetNodeNum << std::endl;

        for (auto nodeNum: getGraph()->getRequiredNodes()) {
            if (nodeNum == targetNodeNum) {
                continue;
            }

            // Find cheapest path to the target node
            auto startingNodeD = outerPaths.find(nodeNum)->second;
            auto endingNodeD = startingNodeD->find(targetNodeNum)->second;
//            std::cout << "       Using node " << nodeNum << ", comparing " << cheapestPathDistance << " "
//                      << endingNodeD->getPathDistance() << std::endl;
            if (endingNodeD->getPathDistance() < cheapestPathDistance) {
                cheapestPathDistance = endingNodeD->getPathDistance();
                cheapestPath = &endingNodeD->getPath();
                cheapestStartingNode = nodeNum;
            }
        }
//        std::cout << "       Selected " << cheapestStartingNode << " with cost " << cheapestPathDistance << std::endl;

        // Set cheapest path as selected
        for (auto edge: *cheapestPath) {
//            std::cout << "       Selecting edge between " << edge->getNodes().first->getNumber() << " and "
//                      << edge->getNodes().second->getNumber() << std::endl;
            getGraph()->selectEdge(edge);
        }
    }

    for (auto path: outerPaths) {
        delete path.second;
    }
}

Dijkstra::Dijkstra(Graph *graph) : Algorithm("dijkstra", graph) {
}

void Dijkstra::writeToDot() {
    Algorithm::writeToDot(this->getName());
}

std::string Dijkstra::writeAlgoBowlOutput() {
    return Algorithm::writeAlgoBowlOutput(this->getName());
}
