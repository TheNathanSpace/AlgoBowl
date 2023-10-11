#include <iostream>
#include <fstream>
#include <algorithm>
#include "graph/Graph.h"
#include "algorithms/MST.h"
#include "algorithms/Dijkstra.h"
#include "util/util.h"
#include "algorithms/Floyd_Dijkstra.h"

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
            inputFiles.push_back(rtrim(line));
        }
        inputFile.close();
    } else {
        std::cerr << "Could not read file " << inputListFileName << std::endl;
        return -1;
    }

    for (const std::string &inputFileName: inputFiles) {
        // Construct the graph object.
        std::cout << "--- Reading file " << inputFileName << " ---" << std::endl;
        std::cout << "Constructing graph...\n" << std::endl;
        auto graph = Graph(inputFileName);

        // Output the graph as a DOT file for visualization.
        graph.writeToDot(inputListFileName + "_base");

        /*
         * This is how you run algorithms:
         *   1. Create the Algorithm object, passing in the Graph.
         *   2. Run the Algorithm.
         *   3. (Optional) Write the Graph visualization to a DOT file. (We won't want to do this for complex/large graphs).
         *   4. Write the AlgoBowl Graph output to a TXT file.
         *   5. Verify using the Verification program.
         *   6. Reset the Graph (so you can run the next algorithm).
         */

        MST mst = MST(&graph);
        std::cout << "Starting MST..." << std::endl;
        mst.run();
        std::cout << "MST finished!" << std::endl;
        mst.writeToDot();
        std::string mstOutputFileName = mst.writeAlgoBowlOutput();

        int result = verify(inputFileName, mstOutputFileName);
        if (result != 0) {
            std::cout << mstOutputFileName << " incorrect!" << std::endl;
        }
        mst.reset();

        Floyd_Dijkstra fl_dk = Floyd_Dijkstra(&graph);
        std::cout << "Starting FL DK..." << std::endl;
        fl_dk.run();
        std::cout << "FL DK finished!\n" << std::endl;
        fl_dk.writeToDot();
        std::string fdOutputFileName = fl_dk.writeAlgoBowlOutput();

        result = verify(inputFileName, fdOutputFileName);
        if (result != 0) {
            std::cout << fdOutputFileName << " incorrect!" << std::endl;
        }
        fl_dk.reset();


//        Dijkstra dijkstra = Dijkstra(&graph);
//        std::cout << "\nStarting Dijkstra..." << std::endl;
//        dijkstra.run();
//        std::cout << "Dijkstra finished!" << std::endl;
//        dijkstra.writeToDot();
//        std::string dOutputFileName = dijkstra.writeAlgoBowlOutput();
//
//        result = verify(inputFileName, dOutputFileName);
//        if (result != 0) {
//            std::cout << dOutputFileName << " incorrect!" << std::endl;
//            auto nodeSet = std::set<int>();
//            for (auto edge: graph.getSelectedEdges()) {
//                nodeSet.insert(edge->getNodes().first->getNumber());
//                nodeSet.insert(edge->getNodes().second->getNumber());
//            }
//            std::vector<int> visited(nodeSet.begin(), nodeSet.end());
//            std::sort(visited.begin(), visited.end());
//            std::cout << "Visited nodes: ";
//            for (auto node: visited) {
//                std::cout << node << " ";
//            }
//            std::cout << std::endl;
//        }
//        dijkstra.reset();
        std::cout << std::endl;
    }

    // all done :)
    std::cout << "\nFinished all algorithms/output. Exiting." << std::endl;

    return 0;
}
