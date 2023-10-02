#include <iostream>
#include <fstream>
#include "graph/Graph.h"

int main() {
    std::cout << "Enter input file: ";
    std::string inputFileName;
    std::cin >> inputFileName;

    std::cout << "Constructing graph..." << std::endl;
    auto *graph = new Graph(inputFileName);
    graph->writeToDot();
    std::cout << "Wrote graph to .dot file" << std::endl;

    return 0;
}
