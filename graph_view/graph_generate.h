#ifndef GRAPH_GENERATE_H
#define GRAPH_GENERATE_H
#include "../phases/request.h"
#include <string>

class Graph_generate
{
public:
    Graph_generate(Request* request, std::string folder);
    void global_graph_generate();
    void graph_building_generate(Building* building);
    void graph_generate_all();
private:
    Request* request;
    std::string folder;

};

#endif // GRAPH_GENERATE_H
