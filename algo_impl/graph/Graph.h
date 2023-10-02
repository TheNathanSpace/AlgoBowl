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

    int numVertices;
    int numEdges;
    int sizeR;
    std::vector<int> *requiredVertices;
    std::unordered_map<int, Node *> *nodeMap;

public:
    Graph(std::string name, int numVertices, int numEdges, int sizeR, std::vector<int> *requiredVertices,
          std::unordered_map<int, Node *> *nodeMap);

    /// Construct Graph by reading in a text file.
    /// Text file specification is defined in the AlgoBowl instructions.
    explicit Graph(const std::string &inputFileName);

    /// Outputs the Graph to a .DOT file, to be used in graph
    /// visualization software like https://dreampuf.github.io/GraphvizOnline/
    void writeToDot();

    /// Helper method to reduce redundant construction.
    void construct(std::string name, int numVertices, int numEdges, int sizeR, std::vector<int> *requiredVertices,
                   std::unordered_map<int, Node *> *nodeMap);
};


#endif //ALGOBOWL_GRAPH_H
