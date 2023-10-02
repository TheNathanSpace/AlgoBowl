//
// Created by nathan on 10/2/23.
//

#ifndef ALGOBOWL_EDGE_H
#define ALGOBOWL_EDGE_H


#include "Node.h"

class Node;

class Edge {

private:
    int weight;
    std::pair<Node*, Node*> nodes;
    bool written;


public:
    Edge(int weight, Node *node1, Node *node2);

    bool getWritten() const;

    int getWeight() const;

    void setWritten(bool written);

    Node *getOtherNode(Node *startingNode) const;
};


#endif //ALGOBOWL_EDGE_H

