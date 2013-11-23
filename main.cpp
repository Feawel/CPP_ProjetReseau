/*
 * main.cpp
 *
 *  Created on: 15 nov. 2013
 *      Author: MOULIN
 */

#include "view/requestinterface.h"
#include <QApplication>
#include <QtGui>


//mockup
#include "phases/request.h"
#include <vector>
#include "model/location/building.h"
#include "model/location/building_building.h"

// basic file operations
#include <iostream>
#include <fstream>
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

    std::vector<Building*> bs;
    bs.push_back(&b1);
    bs.push_back(&b2);
    bs.push_back(&b3);

    ofstream myfile;
    myfile.open ("graphviz.txt");
    myfile << "graph G {" << endl;

    for(int ii=0; ii < bs.size(); ii++)
    {
        myfile << (*bs[ii]).getName() << endl;
    }
    myfile << "}" << endl;

    myfile.close();

//  Génére le graphe en SVG avec un appel système, nécessite graphviz.
//     system ("dot -Tsvg -graph.svg graphviz.txt");

    return app.exec();
}
