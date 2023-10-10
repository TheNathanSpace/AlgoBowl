#include <iostream>
#include <fstream>
#include "graph/Graph.h"
#include "algorithms/MST.h"

int main() {
    // Get graph file name from the user.
    std::string inputListFileName = "all_inputs.txt";
//    std::cout << "Enter input list file: ";
//    std::cin >> inputListFileName;

    std::vector<std::string> inputFiles;
    std::string line;
    std::ifstream inputFile(inputListFileName);
    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            inputFiles.push_back(line);
        }
        inputFile.close();
    } else {
        std::cerr << "Could not read file " << inputListFileName << std::endl;
        return -1;
    }

    for (const std::string &fileName: inputFiles) {
        // Construct the graph object.
        std::cout << "--- Reading file " << fileName << " ---" << std::endl;
        std::cout << "Constructing graph..." << std::endl;
        auto graph = Graph(fileName);

        // Output the graph as a DOT file for visualization.
        graph.writeToDot(inputListFileName + "_base");

        /*
         * This is how you run algorithms:
         *   1. Create the Algorithm object, passing in the Graph.
         *   2. Run the Algorithm.
         *   3. (Optional) Write the Graph visualization to a DOT file. (We won't want to do this for complex/large graphs).
         *   4. Write the AlgoBowl Graph output to a TXT file.
         *   5. Reset the Graph (so you can run the next algorithm).
         */
        MST mst = MST(&graph);
        std::cout << "Starting MST..." << std::endl;
        mst.run();
        std::cout << "MST finished!\n" << std::endl;
        mst.writeToDot();
        std::string outputFileName = mst.writeAlgoBowlOutput();

        // Only running one algorithm right now, so don't waste the time:
//        mst.reset();
    }

    // all done :)
    std::cout << "\nFinished all algorithms/output. Exiting." << std::endl;

    return 0;
}
