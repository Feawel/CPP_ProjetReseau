#ifndef GRAPH_GENERATE_H
#define GRAPH_GENERATE_H
#include "model/request.h"
#include <string>

class GraphGenerate
{
public:
    GraphGenerate(Request* request, std::string folder);
    void globalGraphGenerate();
    void graphBuildingGenerate(Building* building);
    void graphGenerateAll();
private:
    Request* request;
    std::string folder;
    const std::string legend = "legend[label =<<FONT color=\"purple\">Infrared</FONT><BR/><FONT color=\"black\">Ethernet</FONT><BR/><FONT color=\"red\">Fiber</FONT><BR/><FONT color=\"yellow\">Twisted pair</FONT><BR/><FONT color=\"blue\">Wifi</FONT>>]";

};

#endif // GRAPH_GENERATE_H
