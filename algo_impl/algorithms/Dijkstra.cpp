//
// Created by nathan on 10/10/23.
//

#include "Dijkstra.h"
#include <climits>
#include <utility>
#include <iostream>
#include <queue>

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
     *           Dijkstra's algorithm                 *
     *************************************************/

    // Map node numbers to the distances/Dijkstra paths to every other node
    std::unordered_map<int, std::unordered_map<int, DijkstraPath *> *> outerPaths;

    for (int startingNodeNum: getGraph()->getRequiredNodes()) {
        Node *startingNode = getGraph()->getNode(startingNodeNum);
        std::set<Node *> unvisitedNodes;
        auto pathsToOtherNodes = new std::unordered_map<int, DijkstraPath *>;
        outerPaths.insert(std::pair(startingNodeNum, pathsToOtherNodes));

        // Initialize pathsToOtherNodes
        for (auto it: getGraph()->getNodeMap()) {
            pathsToOtherNodes->insert(std::pair(it.second->getNumber(), new DijkstraPath(startingNode, it.second)));
            unvisitedNodes.insert(it.second);
        }

        // The starting node starts with distance=0
        pathsToOtherNodes->find(startingNode->getNumber())->second->setPathDistance(0);

        // Start by relaxing through the starting node
        Node *relaxThroughNode = startingNode;

        while (!unvisitedNodes.empty()) {
            DijkstraPath *relaxThroughNodePath = pathsToOtherNodes->find(relaxThroughNode->getNumber())->second;

            // Relax each adjacent edge
            for (Edge *adjEdge: relaxThroughNode->getAdjacent()) {
                Node *adjNode = adjEdge->getOtherNode(relaxThroughNode);

                // If adjacent node is unvisited (not yet processed)
                if (unvisitedNodes.find(adjNode) != unvisitedNodes.end()) {
                    // Get new distance through current node
                    int tentDistance = relaxThroughNodePath->getPathDistance() + adjEdge->getWeight();
                    DijkstraPath *adjNodePath = pathsToOtherNodes->find(adjNode->getNumber())->second;

                    // Check if the path through the current node even IS cheaper
                    if (tentDistance < adjNodePath->getPathDistance()) {
                        adjNodePath->setPathDistance(tentDistance);
                        adjNodePath->copyPath(relaxThroughNodePath->getPath(), adjEdge);
                    }
                }
            }

            // Find the next lowest cost unvisitedNodes node
            unvisitedNodes.erase(relaxThroughNode);

            int cheapestWeight = INT_MAX;
            Node *cheapestNode = nullptr;
            for (auto node: unvisitedNodes) {
                if (pathsToOtherNodes->find(node->getNumber())->second->getPathDistance() < cheapestWeight) {
                    cheapestWeight = pathsToOtherNodes->find(node->getNumber())->second->getPathDistance();
                    cheapestNode = node;
                }
            }
            if (cheapestNode == nullptr) {
                break;
            }
            relaxThroughNode = cheapestNode;
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
        std::vector<Edge *> cheapestPath;
        int cheapestPathDistance = INT_MAX;
        Node *cheapestStartingNode;

        for (auto nodeNum: getGraph()->getRequiredNodes()) {
            if (nodeNum == targetNodeNum) {
                continue;
            }

            // Find cheapest path to the target node
            auto startingNodeD = outerPaths.find(nodeNum)->second;
            auto endingNodeD = startingNodeD->find(targetNodeNum)->second;
            if (endingNodeD->getPathDistance() < cheapestPathDistance) {
                cheapestPathDistance = endingNodeD->getPathDistance();
                cheapestPath = endingNodeD->getPath();
                cheapestStartingNode = getGraph()->getNode(nodeNum);
            }
        }

        // Set cheapest path as selected
        for (auto edge: cheapestPath) {
            getGraph()->selectEdge(edge);
        }
    }

    /*
     * 1. While unencountered nodes:
     *   a. BFS, starting at unencountered node. Record all encountered nodes in list.
     * 2. While size of list components > 1:
     *   a. Select edges to connect two node list components. Merge list components.
     */

    auto unencounteredNodes = std::set<Node *>();
    for (auto nodeNum: getGraph()->getRequiredNodes()) {
        unencounteredNodes.insert(getGraph()->getNode(nodeNum));
    }
    auto components = std::set<std::set<Node *> *>();

    while (!unencounteredNodes.empty()) {
        Node *root = *unencounteredNodes.erase(unencounteredNodes.begin());
        auto queue = std::queue<Node *>();
        auto explored = new std::set<Node *>();
        explored->insert(root);
        queue.push(root);
        auto parentMap = std::unordered_map<Node *, Node *>();

        // Do BFS of component
        while (!queue.empty()) {
            Node *node = queue.front();
            queue.pop();

            for (auto edge: node->getAdjacent()) {
                if (!edge->isSelected()) {
                    continue;
                }
                auto otherNode = edge->getOtherNode(node);
                if (explored->find(otherNode) == explored->end()) {
                    explored->insert(otherNode);
                    parentMap[otherNode] = node;
                    queue.push(otherNode);
                }
            }
        }

        auto toErase = std::set<Node *>();
        // Record encountered nodes
        for (auto encounteredNode: *explored) {
            unencounteredNodes.erase(encounteredNode);
            if (!encounteredNode->isRequired()) {
                toErase.insert(encounteredNode);
            }
        }
        for (auto erase: toErase) {
            explored->erase(erase);
        }
        if (!explored->empty()) {
            components.insert(explored);
        }
    }

    while (components.size() > 1) {
        std::cout << "Components count: " << components.size() << std::endl;

        auto comp1 = *components.erase(components.begin());
        auto comp2 = *components.erase(components.begin());

        // Choose two random required to connect
        // TODO: this is not the optimal solution. You should check every possible connection.
        Node *node1 = *comp1->begin();
        Node *node2 = *comp2->begin();

        // Select edges to connect the two components
        std::unordered_map<int, DijkstraPath *> *startNodePaths = outerPaths[node1->getNumber()];
        auto targetNodePath = (*startNodePaths)[node2->getNumber()];
        for (auto edge: targetNodePath->getPath()) {
            getGraph()->selectEdge(edge);
            std::cout << "Selected edge " << edge->getNodes().first->getNumber() << " "
                      << edge->getNodes().second->getNumber() << std::endl;
        }

        // Merge the two components
        for (auto node: *comp2) {
            comp1->insert(node);
        }
        components.insert(comp1);
        delete comp2;
    }

    for (auto component: components) {
        delete component;
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
