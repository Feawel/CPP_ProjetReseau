#include "graph_generate.h"
#include "../model/location/building.h"
// basic file operations
#include <iostream>
#include <fstream>
#include <sstream>

//mockup
#include "phases/request.h"
#include <vector>
#include "model/location/building.h"
#include "model/location/building_building.h"
//This function generates the name of a cluster from the number of the building.

using namespace::std;

string createClusterName(int position)
{
    stringstream building1_stream;
    building1_stream << "cluster_" << position;
    string cluster_name = building1_stream.str();
    return cluster_name;
}

//This function returns the postion of a building in a Building_building vector.
int findBInB2B(std::vector<Building*> buildings, Building* building)
{
    for( int i = 0; i < buildings.size(); i++ ) {
        if( buildings[i]== building) {
            return i;
       }
    }
    return -1;
}

//Permet de déterminer la couleur d'un lien représentant une technologie.
string getColorB2B(NTechnology::Technology* tech){
    switch (*tech)
    {
    //WIFI
    case 0:
        return "blue3";
    break;

    //ETHERNET
    case 1:
        return "darkorange";
    break;

    //FIBER
    case 2:
        return "darkorchid";
    break;

    //INFRARED
    case 3:
        return "red";
    break;

    //TWISTEDPAIR
    case 4:
        return "deepskyblue4";
    break;

    default:
        return "black";
    break;
}
}

Graph_generate::Graph_generate(Request* request):request(request)
{
}
void Graph_generate::graph_buildings_generate(){
    std::vector<Building*> bs =request->getBuildings();
    std::vector<Building_Building*> b2bs= request->getBuilding_Buildings();

    ofstream myfile;
    myfile.open ("graphviz.txt");
    myfile << "graph G {" << endl;

    for(int ii=0; ii < bs.size(); ii++)
    {
        myfile << "subgraph cluster_"<<ii << "{"<< endl;
        myfile << "label = \"" <<(*bs[ii]).getName() <<"\""<< endl;
        myfile <<  "}"<< endl <<endl;
    }

    for(int ii=0; ii < b2bs.size(); ii++)
    {
        Building_Building* building_Building=b2bs[ii];
        vector<NTechnology::Technology> techs = building_Building->getExistingTechs();
        if(techs.size()>0){
            Building* building1=building_Building->getBuilding1();
            int positionBuilding1= findBInB2B(bs, building1);
            string cluster1= createClusterName(positionBuilding1);

            Building* building2=building_Building->getBuilding2();
            int positionBuilding2= findBInB2B(bs, building2);
            string cluster2= createClusterName(positionBuilding2);

            for(int it=0; it < techs.size(); it++)
            {
                myfile << cluster1 << " -- " << cluster2 << "[color = \"" <<getColorB2B(&techs[it])<<"\"]"<<endl;
            }
        }
    }

    myfile << "}" << endl;
    myfile.close();

//  Génére le graphe en png avec un appel système, nécessite graphviz. + ne marche plus
  system ("fdp -Tpng graphviz.txt >graphe.png");
}
