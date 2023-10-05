//
// Created by nathan on 10/4/23.
//

#ifndef ALGOBOWL_ALGORITHM_H
#define ALGOBOWL_ALGORITHM_H


#include "../graph/Graph.h"

class Algorithm {
private:
    Graph *graph;
    std::string name;

public:
    explicit Algorithm(std::string name, Graph *graph);

    [[nodiscard]] Graph *getGraph() const;

    [[nodiscard]] const std::string &getName() const;

    virtual void run() = 0;

    void writeToDot(const std::string &algorithm);

    void writeAlgoBowlOutput(const std::string &algorithm);

    void reset();

};


#endif //ALGOBOWL_ALGORITHM_H
