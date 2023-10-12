//
// Created by nathan on 10/2/23.
//

#ifndef ALGOBOWL_NODE_H
#define ALGOBOWL_NODE_H


#include <vector>
#include <unordered_map>
#include "Edge.h"
#define MAX_EDGE (10000 * 50 + 1)

// Forward declaration because of circular dependency
class Edge;

/// Object representing node.
class Node {

private:
    int number = -1;
    int sumWeight = 0;
    bool required = false;
    bool visited = false;
    std::vector<Edge *> adjacent;
    std::unordered_map<int, int> dists;

public:
    explicit Node(int nodeNum);

    ~Node();

    [[nodiscard]] int getNumber() const;

    [[nodiscard]] bool isRequired() const;

    [[nodiscard]] bool isVisited() const;

    void setRequired(bool required);

    void setVisited(bool visited);

    void setDist(Node *target, int dist);

    int getDist(Node *target);

    void updateSumWeight(int update);

    int getSumWeight() const;

    [[nodiscard]] const std::vector<Edge *> &getAdjacent() const;

    void addAdjacent(Edge *adjacentEdge);
};


#endif //ALGOBOWL_NODE_H
