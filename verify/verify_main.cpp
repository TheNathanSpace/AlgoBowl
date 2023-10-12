#include <string>
#include <iostream>
#include "Verifier.h"

//
// Created by nathan on 10/9/2023.
//
int main(int argc, char **argv) {
    if (argc > 1) {
        verify(0, argv);
    } else {
        std::string inputFileName = "input_group683.txt";
        std::string outputFileName = "./finalOutputs/kai-josh/output_from_683_to_683.txt";
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

        std::cout << "Verifying files " << qualifiedInputFileName << " and " << outputFileName << std::endl;
        verify(0, files);

    }
}