//
// Created by nathan on 10/2/23.
//

#ifndef ALGOBOWL_NODE_H
#define ALGOBOWL_NODE_H


#include <vector>
#include "Edge.h"

class Edge;

class Node {

private:
    int number;
    std::vector<Edge *> adjacent;

public:
    explicit Node(int nodeNum);

    int getNumber() const;

    const std::vector<Edge *> &getAdjacent() const;

    void addAdjacent(Edge *adjacentEdge);
};


#endif //ALGOBOWL_NODE_H
