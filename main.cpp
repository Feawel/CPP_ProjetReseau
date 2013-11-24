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
#include <sstream>
using namespace std;
//This function generates the name of a cluster from the number of the building.
string createClusterName(int position)
{
    stringstream building1_stream;
    building1_stream << "cluster_" << position;
    string cluster_name = building1_stream.str();
    return cluster_name;
}

//This function returns the postion of a building in a Building_building vector.
int findBInB2B(std::vector<Building*> buildings, Building building)
{
    for( int i = 0; i < buildings.size(); i++ ) {
        //Je compare les batiments par leurs nom : ilfaut faire en sorte que les noms soient uniques.
        if( (*buildings[i]).getName() == building.getName()) {
            return i;
       }
    }
    return -1;
}

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

    Building_Building b2b1 = Building_Building(&b1, &b2,0, true);
    std::vector<Building_Building*> b2bs;
    b2bs.push_back(&b2b1);

    ofstream myfile;
    myfile.open ("graphviz.txt");
    myfile << "graph G {" << endl;

    for(int ii=0; ii < bs.size(); ii++)
    {
        myfile << "subgraph cluster_"<<ii << "{"<< endl;
        myfile << "label = \"" <<(*bs[ii]).getName() <<"\""<< endl;
        myfile << "}"<< endl <<endl;
    }



    for(int ii=0; ii < b2bs.size(); ii++)
    {
        Building_Building building_Building=*b2bs[ii];
        vector<NTechnology::Technology> techs = building_Building.getExistingTechs();
        if(techs.size()>0){
            Building building1=building_Building.getBuilding1();
            int positionBuilding1= findBInB2B(bs, building1);
            string cluster1= createClusterName(positionBuilding1);


            Building building2=building_Building.getBuilding2();
            int positionBuilding2= findBInB2B(bs, building2);
            string cluster2= createClusterName(positionBuilding2);


            myfile << cluster1 << "--" << cluster2 <<endl;
        }
    }

    myfile << "}" << endl;



    myfile.close();

//  Génére le graphe en SVG avec un appel système, nécessite graphviz. + ne marche plus
//    system ("dot -Tsvg -graph.svg graphviz.txt");

    return app.exec();
}
