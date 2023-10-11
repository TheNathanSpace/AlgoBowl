#include <iostream>
#include <fstream>
#include "graph/Graph.h"
#include "algorithms/MST.h"
#include "algorithms/Floyd_Dijkstra.h"
#include "../verify/Verifier.h"

int main() {
    // Get graph file name from the user.
    std::string inputListFileName = "real_inputs.txt";
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

    for (const std::string &inputFileName: inputFiles) {
        // Construct the graph object.
        std::cout << "--- Reading file " << inputFileName << " ---" << std::endl;
        std::cout << "Constructing graph..." << std::endl;
        auto graph = Graph(inputFileName);

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
//        MST mst = MST(&graph);
//        std::cout << "Starting MST..." << std::endl;
//        mst.run();
//        std::cout << "MST finished!\n" << std::endl;
//        mst.writeToDot();
//        std::string outputFileName = mst.writeAlgoBowlOutput();
        Floyd_Dijkstra fl_dk = Floyd_Dijkstra(&graph);
        std::cout << "Starting FL DK..." << std::endl;
        fl_dk.run();
        std::cout << "FL DK finished!\n" << std::endl;
        fl_dk.writeToDot();
        std::string outputFileName = fl_dk.writeAlgoBowlOutput();

        // Only running one algorithm right now, so don't waste the time:
//        mst.reset();

        /*
         *  The following was my attempt to automate the verification, but it's not working yet...
         */

        // Get the file names into C strings for argv input...
        std::string qualifiedInputFileName = "./inputs/" + inputFileName;
        char inputArray[qualifiedInputFileName.size()];
        for (int c = 0; c < qualifiedInputFileName.size(); c++) {
            inputArray[c] = qualifiedInputFileName[c];
        }

        char outputArray[outputFileName.size()];
        for (int c = 0; c < outputFileName.size(); c++) {
            outputArray[c] = outputFileName[c];
        }

        char *files[] = {inputArray, outputArray};

        std::cout << "Verifying files " << qualifiedInputFileName << " " << outputFileName << std::endl;
        verify(0, files);
        std::cout << "Verification finished!\n" << std::endl;
    }

    // all done :)
    std::cout << "\nFinished all algorithms/output. Exiting." << std::endl;

    return 0;
}
