//
// Created by nathan on 10/2/23.
//

#include <fstream>
#include <utility>
#include "Graph.h"

Graph::Graph(std::string name, int numVertices, int numEdges, int sizeR, std::vector<int> *requiredVertices,
             std::unordered_map<int, Node *> *nodeMap) {
    this->name = std::move(name);
    this->numVertices = numVertices;
    this->numEdges = numEdges;
    this->sizeR = sizeR;
    this->requiredVertices = requiredVertices;
    this->nodeMap = nodeMap;
}

void Graph::writeToDot() {
    std::string outputName = this->name + ".dot";
    fclose(fopen(outputName.c_str(), "w"));
    std::ofstream outputFile;

    outputFile.open(outputName, std::ios_base::app);
    if (outputFile.is_open()) {
        outputFile << "graph {\n";

        int edgeCount = 0;
        std::unordered_map<int, Node *>::iterator it;
        for (it = this->nodeMap->begin(); it != this->nodeMap->end(); it++) {
            outputFile << "  " << it->second->getNumber() << " [label=\"" << it->second->getNumber() << "\"];\n";

            for (Edge *edge: it->second->getAdjacent()) {
                if (edge->getWritten()) {
                    continue;
                }
                Node *otherNode = edge->getOtherNode(it->second);
                outputFile << "  " << it->second->getNumber() << " -- " << otherNode->getNumber() << " [label=\""
                           << edge->getWeight() << "\"];\n";
                edge->setWritten(true);
                edgeCount++;
            }
        }
        outputFile << "\n  # Node count: " << this->nodeMap->size() << "\n  # Edge count: " << edgeCount << "\n}";
    }
}
