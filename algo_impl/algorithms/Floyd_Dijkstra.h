//
// Created by Kai Hoshijo on 10/10/2023.
//

#ifndef ALGOBOWL_FLOYD_DIJKSTRA_H
#define ALGOBOWL_FLOYD_DIJKSTRA_H

#include "Algorithm.h"

class Floyd_Dijkstra : public Algorithm {
private:

public:
    explicit Floyd_Dijkstra(Graph *graph);

    void run() override;

    void writeToDot();

    std::string writeAlgoBowlOutput();
};


#endif //ALGOBOWL_FLOYD_DIJKSTRA_H
