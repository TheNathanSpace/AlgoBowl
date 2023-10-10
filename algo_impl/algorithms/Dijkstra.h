//
// Created by nathan on 10/10/23.
//

#ifndef ALGOBOWL_DIJKSTRA_H
#define ALGOBOWL_DIJKSTRA_H


#include "Algorithm.h"

class Dijkstra : public Algorithm {
public:
    explicit Dijkstra(Graph *graph);

    void run() override;

    void writeToDot();

    std::string writeAlgoBowlOutput();

    /// Returns the cheapest Edge and corresponding Node (both to be added to the MST)
    std::tuple<Node *, Edge *> getCheapestEdge();

};


#endif //ALGOBOWL_DIJKSTRA_H
