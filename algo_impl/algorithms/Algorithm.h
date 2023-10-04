//
// Created by nathan on 10/4/23.
//

#ifndef ALGOBOWL_ALGORITHM_H
#define ALGOBOWL_ALGORITHM_H


#include "../graph/Graph.h"

class Algorithm {
private:
    Graph *graph;

public:
    explicit Algorithm(Graph *graph);

    [[nodiscard]] Graph *getGraph() const;

    virtual void run() = 0;

    void writeToDot(const std::string &algorithm);

    void writeAlgoBowlOutput(const std::string &algorithm);

    void reset();
};


#endif //ALGOBOWL_ALGORITHM_H
