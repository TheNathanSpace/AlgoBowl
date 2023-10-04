//
// Created by nathan on 10/2/23.
//

#include <fstream>
#include <utility>
#include <iostream>
#include "Graph.h"
#include "../util/util.h"

void Graph::construct(std::string name, int numVertices, int numEdges, int sizeR) {
    this->name = std::move(name);
    this->numVertices = numVertices;
    this->numEdges = numEdges;
    this->sizeR = sizeR;
}

Graph::Graph(const std::string &inputFileName) {
    std::string line;
    std::ifstream inputFile(inputFileName);
    if (inputFile.is_open()) {
        int lineNum = 1;
        while (getline(inputFile, line)) {
            switch (lineNum) {
                case 1:
                    numVertices = std::stoi(splitGetFirst(line, " "));
                    for (int i = 0; i < numVertices; ++i) {
                        Node *node = new Node(i + 1);
                        nodeMap.insert(std::pair(i + 1, node));
                    }

                    numEdges = std::stoi(splitGetFirst(line, " "));
                    sizeR = std::stoi(splitGetFirst(line, " "));
                    lineNum++;
                    break;
                case 2:
                    for (int i = 0; i < sizeR; ++i) {
                        int required = std::stoi(splitGetFirst(line, " "));
                        requiredVertices.push_back(required);
                        nodeMap.find(required)->second->setRequired(true);
                    }
                    lineNum++;
                    break;
                default:
                    int node1 = std::stoi(splitGetFirst(line, " "));
                    Node *node1Ptr = nodeMap.find(node1)->second;
                    int node2 = std::stoi(splitGetFirst(line, " "));
                    Node *node2Ptr = nodeMap.find(node2)->second;
                    int weight = std::stoi(splitGetFirst(line, " "));

                    Edge *edge = new Edge(weight, node1Ptr, node2Ptr);
                    this->edges.push_back(edge);

                    node1Ptr->addAdjacent(edge);
                    node2Ptr->addAdjacent(edge);

                    lineNum++;
                    break;
            }
        }
        inputFile.close();

        construct(inputFileName, numVertices, numEdges, sizeR);
    } else {
        std::cerr << "Unable to open file " << inputFileName << std::endl;
        exit(-1);
    }
}

void Graph::writeToDot(const std::string &outputFileName) {
    std::string outputName = outputFileName + ".dot";

    // Clear file contents.
    fclose(fopen(outputName.c_str(), "w"));

    std::ofstream outputFile;
    outputFile.open(outputName, std::ios_base::app);

    if (outputFile.is_open()) {
        outputFile << "graph {\n";
        outputFile << "  # https://dreampuf.github.io/GraphvizOnline/\n";
        outputFile << "  # Node count: " << this->nodeMap.size() << "\n  # Edge count: " << this->edges.size()
                   << "\n\n";

        // Loop through nodes, writing each node and its edges to the DOT file.
        std::unordered_map<int, Node *>::iterator it;
        for (it = this->nodeMap.begin(); it != this->nodeMap.end(); it++) {
            Node *node = it->second;

            outputFile << "  " << node->getNumber() << " [label=\"" << node->getNumber() << "\"";
            if (node->isRequired()) {
                outputFile << ", color=\"blue\"";
            }
            outputFile << "];\n";
        }
        for (Edge *edge: this->edges) {
            auto nodes = edge->getNodes();
            outputFile << "  " << nodes.first->getNumber() << " -- " << nodes.second->getNumber() << " [label=\""
                       << edge->getWeight() << "\"";
            if (edge->isSelected()) {
                outputFile << ", color=\"blue\"";
            }
            outputFile << "];\n";
        }
        outputFile << "}";
    } else {
        std::cerr << "Unable to write to file " + outputName << std::endl;
    }
    outputFile.close();
}

Node *Graph::getNode(int nodeNum) {
    return this->nodeMap.find(nodeNum)->second;
}

void Graph::reset() {
    for (Edge *edge: this->edges) {
        edge->setSelected(false);
    }
    this->selectedEdges.clear();
    this->selectedWeight = 0;
}

Graph::~Graph() {
    for (Edge *edge: this->edges) {
        delete edge;
    }
    std::unordered_map<int, Node *>::iterator it;
    for (it = this->nodeMap.begin(); it != this->nodeMap.end(); it++) {
        delete it->second;
    }
}

const std::string &Graph::getName() const {
    return name;
}

void Graph::writeAlgoBowlOutput(const std::string &outputFileName) {
    std::string outputName = outputFileName + "_output.txt";

    // Clear file contents.
    fclose(fopen(outputName.c_str(), "w"));

    std::ofstream outputFile;
    outputFile.open(outputName, std::ios_base::app);
    if (outputFile.is_open()) {
        int treeCost = this->selectedWeight;
        int selectedNum = this->selectedEdges.size();
        outputFile << treeCost << "\n";
        outputFile << selectedNum << "\n";

        for (Edge *edge: this->selectedEdges) {
            outputFile << edge->getNodes().first << " " << edge->getNodes().second << "\n";
        }
    } else {
        std::cerr << "Unable to write to file " << outputName << std::endl;
    }
    outputFile.close();
}
