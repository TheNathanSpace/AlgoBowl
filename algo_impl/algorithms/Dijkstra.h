//
// Created by nathan on 10/10/23.
//

#ifndef ALGOBOWL_DIJKSTRA_H
#define ALGOBOWL_DIJKSTRA_H


#include "Algorithm.h"

#define MAX_EDGE (10000 * 50 + 1)

class Dijkstra : public Algorithm {
public:
    explicit Dijkstra(Graph *graph);

    void run() override;

    void writeToDot();

    std::string writeAlgoBowlOutput();

};


#endif //ALGOBOWL_DIJKSTRA_H
