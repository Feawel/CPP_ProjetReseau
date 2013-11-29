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
    for(unsigned int i = 0; i < buildings.size(); i++ ) {
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


void draw_location_str(ofstream& file, string name, Location* location, bool generate_label=true){
    file << "subgraph "<< name << "{"<< endl;
    Component comp = (location->getComponents()).front();
    string IP =  comp.getAddress().toString();
    file << "label = \"";
    if(generate_label){
        file <<location->getName();
    }else{
        file << name;
    }
    file <<" \\n"  << IP  <<"\""<< endl;
    file <<  "}"<< endl <<endl;
}

void draw_location(ofstream& file, int int_name, Location* location, bool generate_label=true){
    string name = createClusterName(int_name);
    draw_location_str(file, name, location,generate_label);
}

Graph_generate::Graph_generate(Request* request, string folder):request(request), folder(folder)
{
}


void Graph_generate::graph_generate_all(){
    global_graph_generate();
    std::vector<Building*> bs =request->getBuildings();
    for(unsigned int ii=0; ii < bs.size(); ii++)
    {
        graph_building_generate(bs[ii]);
    }
}

//Generates the graph for a given building.
void Graph_generate::graph_building_generate(Building* building){
    string building_name=building->getName();
    string file_name ="graph_building_"+building_name;

    ofstream myfile;
    myfile.open (( file_name+".txt").c_str());
    myfile << "graph G {" << endl;

    //On commence par dessiner le L2L3
    draw_location_str(myfile, "cluster_L2L3",building, false);

    //Then we draw the floors.
    vector<Floor*> floors= building->getFloors();
    for(unsigned int ii=0; ii < floors.size(); ii++)
    {
        draw_location(myfile,ii , floors[ii]);
        myfile << "cluster_L2L3 " << " -- " << "cluster_" << ii <<endl<<endl;
    }

    std::vector<Building_Building*> b2bs= request->getBuilding_Buildings();
    for(unsigned int ii=0; ii < b2bs.size(); ii++)
    {
        Building_Building* building_Building=b2bs[ii];
        vector<NTechnology::Technology> techs = building_Building->getExistingTechs();
        if(techs.size()>0){
            Building* building1=building_Building->getBuilding1();
            Building* building2=building_Building->getBuilding2();

            if(building1 == building ||  building2 == building  ){
                Building* building_to_build =NULL;
                if(building1 == building){
                    building_to_build = building2;
                }else{
                    building_to_build = building1;

                }
                stringstream name_connected_building_stream;
                name_connected_building_stream << "cluster_building_connected_" << ii;
                string name_connected_building = name_connected_building_stream.str();
                draw_location_str(myfile,name_connected_building, building_to_build);

                for(unsigned int it=0; it < techs.size(); it++)
                {
                    myfile << name_connected_building << " -- " << "cluster_L2L3 " << "[color = \"" <<getColorB2B(&techs[it])<<"\"]"<<endl;
                }
            }
        }
    }

    myfile << "graph [label=\"Map of " << building_name << "\" bgcolor=\"transparent\"]"<< endl;
    myfile << "legend[label = <<FONT color=\"red\">Infrared</FONT><BR/><FONT color=\"orange\">Ethernet</FONT><BR/><FONT color=\"darkorchid\">Fiber</FONT><BR/><FONT color=\"blue\">Twisted pair</FONT><BR/><FONT color=\"blue\">Wifi</FONT>>]";
    myfile <<endl<< "}" << endl;
    myfile.close();

    //  Génére le graphe en png avec un appel système, nécessite graphviz.
    system (("fdp.exe -Tpng "+file_name+".txt >"+file_name+".png").c_str());
}

//Generates the graph for the full organization.
void Graph_generate::global_graph_generate(){
    std::vector<Building*> bs =request->getBuildings();
    std::vector<Building_Building*> b2bs= request->getBuilding_Buildings();

    ofstream myfile;
    string file_name ="global_graph";
    myfile.open ( (file_name+".txt").c_str());
    myfile << "graph G {" << endl;

    for(unsigned int ii=0; ii < bs.size(); ii++)
    {
        draw_location(myfile,ii , bs[ii]);
    }

    for(unsigned int ii=0; ii < b2bs.size(); ii++)
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

            for(unsigned int it=0; it < techs.size(); it++)
            {
                myfile << cluster1 << " -- " << cluster2 << "[color = \"" <<getColorB2B(&techs[it])<<"\"]"<<endl;
            }
        }
    }

    myfile << "graph [label=\"Global map\" bgcolor=\"transparent\"]"<< endl;
    myfile << "legend[label = <<FONT color=\"red\">Infrared</FONT><BR/><FONT color=\"orange\">Ethernet</FONT><BR/><FONT color=\"darkorchid\">Fiber</FONT><BR/><FONT color=\"blue\">Twisted pair</FONT><BR/><FONT color=\"blue\">Wifi</FONT>>]";
    myfile <<endl<< "}" << endl;
    myfile.close();

//  Génére le graphe en png avec un appel système, nécessite graphviz. + ne marche plus
    system (("fdp.exe -Tpng "+file_name+".txt >"+file_name+".png").c_str());
}
