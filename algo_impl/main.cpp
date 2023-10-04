#include <iostream>
#include <fstream>
#include "graph/Graph.h"
#include "algorithms/MST.h"

int main() {
    // Get graph file name from the user.
    std::cout << "Enter input file: ";
    std::string inputFileName;
    std::cin >> inputFileName;

    // Construct the graph object.
    std::cout << "Constructing graph..." << std::endl;
    auto graph = Graph(inputFileName);
    // Output the graph as a DOT file for visualization.
    graph.writeToDot(inputFileName + "_base");

    /*
     * This is how you run algorithms:
     *   1. Create the Algorithm object, passing in the Graph.
     *   2. Run the Algorithm.
     *   3. (Optional) Write the Graph visualization to a DOT file.
     *   4. Write the AlgoBowl Graph output to a TXT file.
     *   5. Reset the Graph (so you can run the next algorithm).
     */
    MST mst = MST(&graph);
    mst.run();
    mst.writeToDot();
    mst.writeAlgoBowlOutput();
    mst.reset();

    std::cout << "Finished all algorithms/output. Exiting." << std::endl;

    return 0;
}
