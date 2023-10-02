//
// Created by nathan on 10/2/23.
//

#ifndef ALGOBOWL_EDGE_H
#define ALGOBOWL_EDGE_H


#include "Node.h"

// Forward declaration because of circular dependency
class Node;

/// Object representing a weighted edge connecting two nodes.
class Edge {

private:
    int weight;
    std::pair<Node *, Node *> nodes;
    bool written;


public:
    Edge(int weight, Node *node1, Node *node2);

    [[nodiscard]] int getWeight() const;

    [[nodiscard]] bool getWritten() const;

    /// Mark this edge as already written to the output
    /// DOT file (avoid duplicate edges).
    void setWritten(bool written);

    /// Returns the node connected at the opposite end of the given node.
    Node *getOtherNode(Node *startingNode) const;
};


#endif //ALGOBOWL_EDGE_H

