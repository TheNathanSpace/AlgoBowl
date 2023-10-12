//
// Created by nathan on 10/10/23.
//

#include "Dijkstra.h"
#include <climits>
#include <utility>
#include <iostream>
#include <queue>

class DijkstraPath {
private:
    Node *startingNode;
    Node *currentNode;
    std::vector<Edge *> path;
    int pathDistance = INT_MAX;
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

    void setPathDistance(int pathDistance) {
        DijkstraPath::pathDistance = pathDistance;
    }

    void copyPath(std::vector<Edge *> otherPath, Edge *adjEdge) {
        this->path = std::move(otherPath);
        this->path.push_back(adjEdge);
    }
};

bool checkCycle(Node *start, std::set<Node *> *visited, Node *parent) {
    visited->insert(start);
    for (auto adjEdge: start->getAdjacent()) {
        if (!adjEdge->isSelected()) {
            continue;
        }
        auto adjNode = adjEdge->getOtherNode(start);
        if (visited->find(adjNode) == visited->end()) {
            return checkCycle(adjNode, visited, start);
        } else if (adjNode->getNumber() != parent->getNumber()) {
            std::cout << "BFS Cycle detected through " << adjNode->getNumber() << std::endl;
            return true;
        }
    }
    return false;
}

void Dijkstra::run() {
    /**************************************************
     *           Dijkstra's algorithm                 *
     *************************************************/


    /*
     * Map node numbers to the distances/Dijkstra paths to every other node
     */
    std::unordered_map<int, std::unordered_map<int, DijkstraPath *> *> outerPaths;

    // TODO: half of these will be redundant
    for (auto it: getGraph()->getNodeMap()) {
        int startingNodeNum = it.second->getNumber();
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
     * For each required Node, select path between it and the closest other required Node.
     * Note that this may result in multiple components.
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

    while (true) {
        /*
         * Perform BFS to discover each component.
         * Then, find the closest two components.
         * Select the path between their closest nodes.
         *
         * Repeat until there is only 1 component.
         */
        auto components = std::vector<std::set<Node *> *>();

        /*
         * Construct components with BFS
         */
        auto unencounteredNodes = std::set<Node *>();
        for (auto nodeNum: getGraph()->getRequiredNodes()) {
            unencounteredNodes.insert(getGraph()->getNode(nodeNum));
        }
        while (!unencounteredNodes.empty()) {
            Node *root = *unencounteredNodes.begin();
            unencounteredNodes.erase(unencounteredNodes.begin());
            auto queue = std::queue<Node *>();
            auto explored = new std::set<Node *>();
            explored->insert(root);
            queue.push(root);
            auto parentMap = std::unordered_map<Node *, Node *>();

            // BFS loop
            while (!queue.empty()) {
                Node *node = queue.front();
                queue.pop();

                for (auto edge: node->getAdjacent()) {
                    // BFS only through selected edges
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

            // Record encountered nodes in component.
            for (auto encounteredNode: *explored) {
                unencounteredNodes.erase(encounteredNode);
            }
            if (!explored->empty()) {
                components.push_back(explored);
            }

//            // Check for cycle (for debugging purposes)
//            std::set<Node *> visited;
//            bool cycle = checkCycle(*explored->begin(), &visited, nullptr);
        }

        // If there's only one component, then they're all merged and we're done!
        if (components.size() == 1) {
            break;
        }

        /*
         * For each component, for each other component,
         * compare the distance between each node in each
         * component to find the cheapest path to connect
         * the components.
         */

        // Initialize alreadyChecked map
        // This map is used to cut the time taken in half because
        // half the combinations will be redundant (order doesn't matter).
        auto alreadyChecked = std::unordered_map<int, std::set<int> *>();
        for (int i = 0; i < components.size(); ++i) {
            alreadyChecked[i] = new std::set<int>;
        }

        /*
         * Find the single cheapest path between two components
         */
        int cheapestCompPathWeight = INT_MAX;
        DijkstraPath *cheapestCompObj = nullptr;
        for (int i = 0; i < components.size(); ++i) {
            for (int j = 0; j < components.size(); ++j) {
                // SKip if comparing the same component
                if (i == j) {
                    continue;
                }

                // If this combination hasn't been checked yet
                if (alreadyChecked[i]->find(j) == alreadyChecked[i]->end() &&
                    alreadyChecked[j]->find(i) == alreadyChecked[j]->end()) {
                    /*
                     * Find the single cheapest path between these two component's nodes
                     */
                    int cheapestNodePathWeight = INT_MAX;
                    DijkstraPath *cheapestNodeObj = nullptr;

                    // TODO: half of these will be redundant
                    for (Node *outerNode: *components[i]) {
                        for (Node *innerNode: *components[j]) {
                            // Skip if comparing the same node
                            if (outerNode->getNumber() == innerNode->getNumber()) {
                                continue;
                            }

                            std::unordered_map<int, DijkstraPath *> *startNodePaths = outerPaths[outerNode->getNumber()];
                            auto targetNodePath = (*startNodePaths)[innerNode->getNumber()];

                            if (targetNodePath->getPathDistance() < cheapestNodePathWeight) {
                                cheapestNodePathWeight = targetNodePath->getPathDistance();
                                cheapestNodeObj = targetNodePath;
                            }
                        }
                    }

                    if (cheapestNodePathWeight < cheapestCompPathWeight) {
                        cheapestCompPathWeight = cheapestNodePathWeight;
                        cheapestCompObj = cheapestNodeObj;
                    }

                    // Update alreadyChecked to avoid duplicating this combination
                    alreadyChecked[i]->insert(j);
                }
            }
        }

        for (auto i: alreadyChecked) {
            delete i.second;
        }

        // Select edges to connect the two components
        for (auto edge: cheapestCompObj->getPath()) {
            getGraph()->selectEdge(edge);
        }

        // Delete all existing components (we'll recalculate them to avoid cycles)
        for (auto component: components) {
            delete component;
        }
        components.clear();
    }

    // Cleanup map memory
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
