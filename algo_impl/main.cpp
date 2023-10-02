#include <iostream>
#include <fstream>
#include "graph/Graph.h"

int main() {
    // Get graph file name from the user.
    std::cout << "Enter input file: ";
    std::string inputFileName;
    std::cin >> inputFileName;

    // Construct the graph object.
    std::cout << "Constructing graph..." << std::endl;
    auto *graph = new Graph(inputFileName);

    // Output the graph as a DOT file for visualization.
    graph->writeToDot();
    std::cout << "Wrote graph to .dot file" << std::endl;

    return 0;
}
