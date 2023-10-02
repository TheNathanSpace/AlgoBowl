#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "util.h"
#include "graph/Edge.h"
#include "graph/Graph.h"

int main() {
    std::cout << "Enter input file: ";
    std::string inputFileName;
    std::cin >> inputFileName;
    std::cout << "Reading input file " << inputFileName << std::endl;

    Graph *graph;

    std::string line;
    std::ifstream inputFile(inputFileName);
    if (inputFile.is_open()) {
        std::cout << "Constructing graph..." << std::endl;

        int numVertices, numEdges, sizeR;
        auto *requiredVertices = new std::vector<int>;
        auto *nodeMap = new std::unordered_map<int, Node *>;

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
                        requiredVertices->push_back(std::stoi(splitGetFirst(line, " ")));
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

        graph = new Graph(inputFileName, numVertices, numEdges, sizeR, requiredVertices, nodeMap);
    } else {
        std::cerr << "Unable to open file " << inputFileName << std::endl;
        return -1;
    }

    graph->writeToDot();
    std::cout << "Wrote graph to .dot file" << std::endl;

    return 0;
}
