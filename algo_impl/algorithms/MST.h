//
// Created by nathan on 10/4/23.
//

#ifndef ALGOBOWL_MST_H
#define ALGOBOWL_MST_H


#include "Algorithm.h"
#include <cstdlib>

class MST : public Algorithm {

public:
    explicit MST(Graph *graph);

    void run() override;

    void writeToDot();

    void writeAlgoBowlOutput();

    /// Returns the cheapest Edge and corresponding Node (both to be added to the MST)
    std::tuple<Node *, Edge *> getCheapestEdge();
};


#endif //ALGOBOWL_MST_H
