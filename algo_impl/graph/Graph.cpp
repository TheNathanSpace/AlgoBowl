//
// Created by nathan on 10/2/23.
//

#include <fstream>
#include <utility>
#include <iostream>
#include <filesystem>
#include "Graph.h"
#include "../util/util.h"

const std::string OUTPUT_DIR_NAME = "./outputs";
const std::string INPUT_DIR_NAME = "./inputs";

void Graph::construct(std::string name, int numVertices, int numEdges, int sizeR) {
    this->name = std::move(name);
    this->numNodes = numVertices;
    this->numEdges = numEdges;
    this->sizeR = sizeR;
}

Graph::Graph(const std::string &inputFileName) {
    std::string inputFilePath = INPUT_DIR_NAME + "/" + inputFileName;

    std::string line;
    std::ifstream inputFile(inputFilePath);
    if (inputFile.is_open()) {
        int lineNum = 1;
        while (getline(inputFile, line)) {
            switch (lineNum) {
                case 1:
                    numNodes = std::stoi(splitGetFirst(line, " "));
                    for (int i = 0; i < numNodes; ++i) {
                        Node *node = new Node(i + 1);
                        nodeMap.insert(std::pair(i + 1, node));
                        allNodes.push_back(node);
                    }

                    numEdges = std::stoi(splitGetFirst(line, " "));
                    sizeR = std::stoi(splitGetFirst(line, " "));
                    lineNum++;
                    break;
                case 2:
                    for (int i = 0; i < sizeR; ++i) {
                        int required = std::stoi(splitGetFirst(line, " "));
                        requiredNodes.push_back(required);
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

                    node1Ptr->updateSumWeight(weight);
                    node2Ptr->updateSumWeight(weight);

                    lineNum++;
                    break;
            }
        }
        inputFile.close();

        construct(inputFileName, numNodes, numEdges, sizeR);

//        std::cout << "Required nodes: ";
//        for (auto node: requiredNodes) {
//            std::cout << node << " ";
//        }
//        std::cout << std::endl;

    } else {
        std::cerr << "Unable to open file " << inputFileName << std::endl;
        exit(-1);
    }
}

void Graph::writeToDot(const std::string &outputFileName) {
    std::string outputDir = OUTPUT_DIR_NAME + "/" + this->name;
    std::string outputName = outputDir + "/" + outputFileName + ".dot";

    std::filesystem::create_directories(outputDir);

    // Clear file contents.
    fclose(fopen(outputName.c_str(), "w"));

    std::ofstream outputFile;
    outputFile.open(outputName, std::ios_base::app);

    if (outputFile.is_open()) {
        outputFile << "graph {\n";
        outputFile << "  # https://dreampuf.github.io/GraphvizOnline/\n\n";
        outputFile << "  # Node count: " << this->nodeMap.size() << "\n  # Edge count: " << this->edges.size()
                   << "\n\n";
        outputFile << "  # Required node count: " << this->requiredNodes.size() << "\n  # Selected edge count: "
                   << this->selectedEdges.size() << "\n  # Selected edge weight: " << this->selectedWeight << "\n\n";

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

int Graph::getNumNodes() const {
    return this->numNodes;
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
    std::unordered_map<int, Node *>::iterator it;
    for (it = this->nodeMap.begin(); it != this->nodeMap.end(); it++) {
        it->second->setVisited(false);
    }
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

std::string Graph::writeAlgoBowlOutput(const std::string &outputFileName) {
    std::string outputDir = OUTPUT_DIR_NAME + "/" + this->name;
    std::string outputName = outputDir + "/" + outputFileName + ".txt";

    std::filesystem::create_directories(outputDir);

    // Clear file contents.
    fclose(fopen(outputName.c_str(), "w"));

    std::ofstream outputFile;
    outputFile.open(outputName, std::ios_base::app);
    if (outputFile.is_open()) {
        int treeCost = this->selectedWeight;
        int selectedNum = this->selectedEdges.size();
        outputFile << treeCost << "\n";
        outputFile << selectedNum << "\n";

//        int tempWeight = 0;
        for (Edge *edge: this->selectedEdges) {
            outputFile << edge->getNodes().first->getNumber() << " " << edge->getNodes().second->getNumber() << "\n";
//            tempWeight += edge->getWeight();
        }
//        std::cout << "Newly calculated weight: " << tempWeight << std::endl;
//        auto nodeSet = std::set<Node *>();
//        for (auto edge: this->selectedEdges) {
//            nodeSet.insert(edge->getNodes().first);
//            nodeSet.insert(edge->getNodes().second);
//        }
//        std::cout << "Visited nodes: ";
//        for (auto node: nodeSet) {
//            std::cout << node->getNumber() << " ";
//        }
//        std::cout << std::endl;
    } else {
        std::cerr << "Unable to write to file " << outputName << std::endl;
    }
    outputFile.close();
    return outputName;
}

const std::set<Node *> &Graph::getVisitedNodes() const {
    return visitedNodes;
}

const std::set<Edge *> &Graph::getSelectedEdges() const {
    return selectedEdges;
}

std::vector<Node *> Graph::getAllNodes() {
    return this->allNodes;
}

void Graph::selectEdge(Edge *edge) {
    if (!edge->isSelected()) {
        this->selectedWeight += edge->getWeight();
    }
    edge->setSelected(true);
    this->selectedEdges.insert(edge);
}

void Graph::unselectEdge(Edge *edge) {
    if (edge->isSelected()) {
        this->selectedWeight -= edge->getWeight();
    }
    edge->setSelected(false);
    this->selectedEdges.erase(edge);
}

void Graph::visitNode(Node *node) {
    node->setVisited(true);
    this->visitedNodes.insert(node);
}

const std::vector<int> &Graph::getRequiredNodes() const {
    return requiredNodes;
}

const std::unordered_map<int, Node *> &Graph::getNodeMap() const {
    return nodeMap;
}
