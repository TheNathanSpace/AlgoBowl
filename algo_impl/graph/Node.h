//
// Created by nathan on 10/2/23.
//

#ifndef ALGOBOWL_NODE_H
#define ALGOBOWL_NODE_H


#include <vector>
#include "Edge.h"

// Forward declaration because of circular dependency
class Edge;

/// Object representing node.
class Node {

private:
    int number;
    bool required;
    bool visited;
    std::vector<Edge *> adjacent;

public:
    explicit Node(int nodeNum);

    [[nodiscard]] int getNumber() const;

    [[nodiscard]] bool isRequired() const;

    [[nodiscard]] bool isVisited() const;

    void setRequired(bool required);

    void setVisited(bool visited);

    [[nodiscard]] const std::vector<Edge *> &getAdjacent() const;

    void addAdjacent(Edge *adjacentEdge);
};


#endif //ALGOBOWL_NODE_H
