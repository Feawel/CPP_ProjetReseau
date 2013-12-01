#ifndef GRAPH_GENERATE_H
#define GRAPH_GENERATE_H
#include "model/request.h"
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
    const std::string legend = "<<FONT color=\"purple\">Infrared</FONT><BR/><FONT color=\"black\">Ethernet</FONT><BR/><FONT color=\"red\">Fiber</FONT><BR/><FONT color=\"yellow\">Twisted pair</FONT><BR/><FONT color=\"blue\">Wifi</FONT>>]";

};

#endif // GRAPH_GENERATE_H
