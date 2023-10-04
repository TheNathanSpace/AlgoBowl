//
// Created by nathan on 10/4/23.
//

#ifndef ALGOBOWL_MST_H
#define ALGOBOWL_MST_H


#include "Algorithm.h"

class MST : public Algorithm {

public:
    explicit MST(Graph *graph);

    void run() override;

    void writeToDot();

    void writeAlgoBowlOutput();
};


#endif //ALGOBOWL_MST_H
