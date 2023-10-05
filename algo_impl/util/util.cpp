//
// Created by nathan on 10/2/23.
//

#include <string>
#include "util.h"

std::string splitGetFirst(std::string &string, const std::string &delimiter) {
    std::string token = string.substr(0, string.find(' '));
    string.erase(0, string.find(' ') + delimiter.length());
    return token;
}