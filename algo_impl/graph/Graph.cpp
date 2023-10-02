//
// Created by nathan on 10/2/23.
//

#include <fstream>
#include <utility>
#include <iostream>
#include "Graph.h"
#include "../util/util.h"

Graph::Graph(std::string name, int numVertices, int numEdges, int sizeR, std::vector<int> *requiredVertices,
             std::unordered_map<int, Node *> *nodeMap) {
    construct(std::move(name), numVertices, numEdges, sizeR, requiredVertices, nodeMap);
}

void Graph::construct(std::string name, int numVertices, int numEdges, int sizeR, std::vector<int> *requiredVertices,
                      std::unordered_map<int, Node *> *nodeMap) {
    this->name = std::move(name);
    this->numVertices = numVertices;
    this->numEdges = numEdges;
    this->sizeR = sizeR;
    this->requiredVertices = requiredVertices;
    this->nodeMap = nodeMap;
}

Graph::Graph(const std::string &inputFileName) {
    std::string line;
    std::ifstream inputFile(inputFileName);
    if (inputFile.is_open()) {
        this->requiredVertices = new std::vector<int>;
        this->nodeMap = new std::unordered_map<int, Node *>;

        int lineNum = 1;
        while (getline(inputFile, line)) {
            switch (lineNum) {
                case 1:
                    numVertices = std::stoi(splitGetFirst(line, " "));
                    for (int i = 0; i < numVertices; ++i) {
                        Node *node = new Node(i + 1);
                        nodeMap->insert(std::pair(i + 1, node));
                    }

                    numEdges = std::stoi(splitGetFirst(line, " "));
                    sizeR = std::stoi(splitGetFirst(line, " "));
                    lineNum++;
                    break;
                case 2:
                    for (int i = 0; i < sizeR; ++i) {
                        int required = std::stoi(splitGetFirst(line, " "));
                        requiredVertices->push_back(required);
                        nodeMap->find(required)->second->setRequired(true);
                    }
                    lineNum++;
                    break;
                default:
                    int node1 = std::stoi(splitGetFirst(line, " "));
                    Node *node1Ptr = nodeMap->find(node1)->second;
                    int node2 = std::stoi(splitGetFirst(line, " "));
                    Node *node2Ptr = nodeMap->find(node2)->second;
                    int weight = std::stoi(splitGetFirst(line, " "));

                    Edge *edge = new Edge(weight, node1Ptr, node2Ptr);

                    node1Ptr->addAdjacent(edge);
                    node2Ptr->addAdjacent(edge);

                    lineNum++;
                    break;
            }
        }
        inputFile.close();

        construct(inputFileName, numVertices, numEdges, sizeR, requiredVertices, nodeMap);
    } else {
        std::cerr << "Unable to open file " << inputFileName << std::endl;
        exit(-1);
    }
}

void Graph::writeToDot() {
    std::string outputName = this->name + ".dot";

    // Clear file contents.
    fclose(fopen(outputName.c_str(), "w"));

    std::ofstream outputFile;
    outputFile.open(outputName, std::ios_base::app);

    if (outputFile.is_open()) {
        outputFile << "graph {\n";
        outputFile << "  # https://dreampuf.github.io/GraphvizOnline/\n\n";

        int edgeCount = 0;

        // Loop through nodes, writing each node and its edges to the DOT file.
        std::unordered_map<int, Node *>::iterator it;
        for (it = this->nodeMap->begin(); it != this->nodeMap->end(); it++) {
            Node *node = it->second;

            outputFile << "  " << node->getNumber() << " [label=\"" << node->getNumber() << "\"";
            if (node->isRequired()) {
                outputFile << ", color=\"blue\"";
            }
            outputFile << "];\n";

            for (Edge *edge: node->getAdjacent()) {
                if (edge->getWritten()) {
                    continue;
                }
                Node *otherNode = edge->getOtherNode(node);
                outputFile << "  " << node->getNumber() << " -- " << otherNode->getNumber() << " [label=\""
                           << edge->getWeight() << "\"";
                if (edge->isSelected()) {
                    outputFile << ", color=\"blue\"";
                }
                outputFile << "];\n";

                edge->setWritten(true);
                edgeCount++;
            }
        }
        outputFile << "\n  # Node count: " << this->nodeMap->size() << "\n  # Edge count: " << edgeCount << "\n}";
    }
}

Node *Graph::getNode(int nodeNum) {
    return this->nodeMap->find(nodeNum)->second;
}
