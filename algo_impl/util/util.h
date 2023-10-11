//
// Created by nathan on 10/2/23.
//

#ifndef ALGOBOWL_UTIL_H
#define ALGOBOWL_UTIL_H

///  Splits the string on the delimiter, returning
///  the first token and erasing it from the string.
std::string splitGetFirst(std::string &string, const std::string &delimiter);

int verify(const std::string &inputFileName, const std::string &outputFileName);

std::string &rtrim(std::string &s);

#endif //ALGOBOWL_UTIL_H
