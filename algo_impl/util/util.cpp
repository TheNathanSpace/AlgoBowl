//
// Created by nathan on 10/2/23.
//

#include <string>
#include <iostream>
#include "util.h"
#include "../../verify/Verifier.h"

std::string splitGetFirst(std::string &string, const std::string &delimiter) {
    std::string token = string.substr(0, string.find(' '));
    string.erase(0, string.find(' ') + delimiter.length());
    return token;
}

/// Verify input and output, given as string file names
int verify(const std::string &inputFileName, const std::string &outputFileName) {
    // Get the file names into C strings for argv input...
    std::string qualifiedInputFileName = "./inputs/" + inputFileName;
    char inputArray[qualifiedInputFileName.size() + 1];
    for (int c = 0; c < qualifiedInputFileName.size(); c++) {
        inputArray[c] = qualifiedInputFileName[c];
    }
    inputArray[qualifiedInputFileName.size()] = '\0';

    char outputArray[outputFileName.size() + 1];
    for (int c = 0; c < outputFileName.size(); c++) {
        outputArray[c] = outputFileName[c];
    }
    outputArray[outputFileName.size()] = '\0';

    char *files[3] = {nullptr, inputArray, outputArray};

    return verify(3, files);
}


/// trim from end of string (right)
std::string &rtrim(std::string &s) {
    const char *ws = " \t\n\r\f\v";
    s.erase(s.find_last_not_of(ws) + 1);
    return s;
}