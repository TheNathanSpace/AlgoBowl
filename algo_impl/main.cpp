#include <iostream>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include "graph/Graph.h"
#include "algorithms/MST.h"
#include "algorithms/Dijkstra.h"
#include "util/util.h"
#include "algorithms/Floyd_Dijkstra.h"

int main() {
    std::string inputListFileName = "real_inputs.txt";

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
        std::cout << "Constructing graph..." << std::endl;
        auto graph = Graph(inputFileName);

        // Output the graph as a DOT file for visualization.
        graph.writeToDot(inputListFileName + "_base");

        auto algoWeights = std::unordered_map<std::string, int>();
        std::string outputFileName;

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
        std::cout << "    Starting MST..." << std::endl;
        mst.run();
        std::cout << "    MST finished! (Weight: " << graph.getSelectedWeight() << ")" << std::endl;
        mst.writeToDot();
        outputFileName = mst.writeAlgoBowlOutput();

        int result = verify(inputFileName, outputFileName);
        if (result != 0) {
            std::cout << "    " << outputFileName << " incorrect!" << std::endl;
        } else {
            algoWeights[outputFileName] = graph.getSelectedWeight();
        }
        mst.reset();


        Floyd_Dijkstra fl_dk = Floyd_Dijkstra(&graph);
        std::cout << "    Starting FL DK..." << std::endl;
        fl_dk.run();
        std::cout << "    FL DK finished! (Weight: " << graph.getSelectedWeight() << ")" << std::endl;
        fl_dk.writeToDot();
        outputFileName = fl_dk.writeAlgoBowlOutput();

        result = verify(inputFileName, outputFileName);
        if (result != 0) {
            std::cout << "    " << outputFileName << " incorrect!" << std::endl;
        } else {
            algoWeights[outputFileName] = graph.getSelectedWeight();
        }
        fl_dk.reset();


        Dijkstra dijkstra = Dijkstra(&graph);
        std::cout << "    Starting Dijkstra..." << std::endl;
        dijkstra.run();
        std::cout << "    Dijkstra finished! (Weight: " << graph.getSelectedWeight() << ")" << std::endl;
        dijkstra.writeToDot();
        outputFileName = dijkstra.writeAlgoBowlOutput();

        result = verify(inputFileName, outputFileName);
        if (result != 0) {
            std::cout << "    " << outputFileName << " incorrect!" << std::endl;
        } else {
            algoWeights[outputFileName] = graph.getSelectedWeight();
        }
        dijkstra.reset();


        // Find cheapest weight
        int cheapestCost = INT_MAX;
        std::string cheapestName = "";
        for (std::pair<std::string, int> it: algoWeights) {
            if (it.second < cheapestCost) {
                cheapestCost = it.second;
                cheapestName = it.first;
            }
        }

        // Create final output directory
        std::string outputDir = "./finalOutputs";
        std::string finalOutputFileName = outputDir + "/" + graph.getName();
        std::filesystem::create_directories(outputDir);
        fclose(fopen(finalOutputFileName.c_str(), "w"));

        // Copy cheapest output to final output
        std::ifstream src(cheapestName, std::ios::binary);
        std::ofstream dst(finalOutputFileName, std::ios::binary);
        dst << src.rdbuf();
        src.close();
        dst.close();

        std::cout << "Cheapest weight: " << cheapestCost << " (output file: " << cheapestName << ")"
                  << std::endl;
        std::cout << std::endl;
    }

    // all done :)
    std::cout << "\nFinished all algorithms/output. Exiting." << std::endl;

    return 0;
}
