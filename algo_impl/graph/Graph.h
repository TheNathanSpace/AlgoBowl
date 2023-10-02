//
// Created by nathan on 10/2/23.
//

#ifndef ALGOBOWL_GRAPH_H
#define ALGOBOWL_GRAPH_H


#include <vector>
#include <unordered_map>
#include <string>
#include "Node.h"

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

    void writeToDot();
};


#endif //ALGOBOWL_GRAPH_H
