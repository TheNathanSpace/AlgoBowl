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
    graph->writeToDot(inputFileName + "_base");

    /* This is where you'd run the algorithm.
     * You can save the output separately for each one. */
//    graph->mst();
//    graph->writeToDot(inputFileName + "_mst");

    /* Reset the graph to run the next algorithm. */
//    graph->reset();

//    graph.dijkstra();
//    graph->writeToDot(inputFileName + "_dijkstra");

    std::cout << "Finished all algorithms/output. Exiting." << std::endl;

    return 0;
}
