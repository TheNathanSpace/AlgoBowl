//
// Created by nathan on 10/2/23.
//

#ifndef ALGOBOWL_GRAPH_H
#define ALGOBOWL_GRAPH_H


#include <vector>
#include <unordered_map>
#include <string>
#include "Node.h"

/// Object representing an undirected, weighted graph.
class Graph {

private:
    std::string name;
public:
    [[nodiscard]] const std::string &getName() const;

private:

    int numVertices;
    int numEdges;
    int sizeR;
    std::vector<int> requiredVertices;
    std::unordered_map<int, Node *> nodeMap;

    /*
     * This could be changed to a map (node1, node2) -> edge, but I'm not
     * sure that's necessary so haven't done it yet.
     */
    std::vector<Edge *> edges;

    std::vector<Edge *> selectedEdges;
    int selectedWeight = 0;

public:
    /// Construct Graph by reading in a text file.
    /// Text file specification is defined in the AlgoBowl instructions.
    explicit Graph(const std::string &inputFileName);


    /// Helper method to reduce redundant construction.
    void construct(std::string name, int numVertices, int numEdges, int sizeR);

    virtual ~Graph();

    /// Outputs the Graph to a .DOT file, to be used in graph
    /// visualization software like https://dreampuf.github.io/GraphvizOnline/
    void writeToDot(const std::string &outputFileName);

    /// Write the Graph to a TXT file in the proper AlgoBowl output format.
    void writeAlgoBowlOutput(const std::string &outputFileName);

    /// Get Node object by node number.
    Node *getNode(int nodeNum);

    /// Select an Edge, updating Graph data structures.
    void selectEdge(Edge *edge) {
        edge->setSelected(true);
        this->selectedEdges.push_back(edge);
        this->selectedWeight += edge->getWeight();
    }

    /// Resets chosen/written edges so you can run more algorithms.
    void reset();

};


#endif //ALGOBOWL_GRAPH_H
