#ifndef GRAPH_GENERATE_H
#define GRAPH_GENERATE_H
#include "../phases/request.h"
class Graph_generate
{
public:
    Graph_generate(Request* request);
    void graph_buildings_generate();
private:
    Request* request;

};

#endif // GRAPH_GENERATE_H
