#ifndef GRAPH_GENERATE_H
#define GRAPH_GENERATE_H
#include "../phases/request.h"
class Graph_generate
{
public:
    Graph_generate(Request* request);
    void global_graph_generate();
    void graph_building_generate(Building* building);
    void graph_generate_all();
private:
    Request* request;

};

#endif // GRAPH_GENERATE_H
