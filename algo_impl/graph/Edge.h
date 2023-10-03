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
    bool selected;

public:
    Edge(int weight, Node *node1, Node *node2);

    [[nodiscard]] int getWeight() const;

    /// Returns the node connected at the opposite end of the given node.
    Node *getOtherNode(Node *startingNode) const;

    /// Get whether or not the edge has been selected in the tree.
    bool isSelected() const;

    /// Set whether or not the edge has been selected in the tree.
    void setSelected(bool selected);

    std::pair<Node *, Node *> getNodes();
};


#endif //ALGOBOWL_EDGE_H

