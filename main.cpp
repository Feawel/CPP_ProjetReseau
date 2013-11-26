/*
 * main.cpp
 *
 *  Created on: 15 nov. 2013
 *      Author: MOULIN
 */

#include "view/requestinterface.h"
#include "graph_view/graph_generate.h"
#include <QApplication>
#include <QtGui>
#include <iostream>
#include "model/component/router.h"

using namespace std;


//mockup
#include "phases/request.h"
#include <vector>
#include "model/location/building.h"
#include "model/location/building_building.h"


using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    RequestInterface window ;
    window.show();

    //mockup:
    Building b1=Building("B1");
    Building b2=Building("B2");
    Building b3=Building("B3");
    b1.addComponent(Component(Address(10,0,0,1,0)));
    b2.addComponent(Component(Address(10,0,0,2,0)));
    b3.addComponent(Component(Address(10,0,0,3,0)));
    std::vector<Building*> bs;
    bs.push_back(&b1);
    bs.push_back(&b2);
    bs.push_back(&b3);

    Building_Building b2b1 = Building_Building(&b1, &b2,0, true);
    b2b1.addExistingTechnology(NTechnology::WIFI);

    Building_Building b2b2 = Building_Building(&b3, &b2,0, true);
    b2b2.addExistingTechnology(NTechnology::INFRARED);

    std::vector<Building_Building*> b2bs;
    b2bs.push_back(&b2b1);
    b2bs.push_back(&b2b2);
    Request request = Request(bs, b2bs);
    Graph_generate graph_generate = Graph_generate(&request);
    graph_generate.global_graph_generate();
    return app.exec();
}
