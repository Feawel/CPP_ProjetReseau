#include "graph_generate.h"
#include "../model/location/building.h"
// basic file operations
#include <iostream>
#include <fstream>
#include <sstream>

//mockup
#include "model/request.h"
#include <vector>
#include "model/location/building.h"
#include "model/component/router.h"
#include "model/component/switch.h"
#include "model/location/building_building.h"
//This function generates the name of a cluster from the number of the building.

using namespace::std;

/**
 * @brief replaceSpacesByUnderscores
 * @param str
 * @return str with "_" instead of " "
 */
string replaceSpacesByUnderscores(string str){
    char space = ' ';
    for(unsigned int i = 0; i < str.size(); i++){
        if(str[i] == space){
               str[i] = '_';
        }
    }
    return str;
}

/**
 * @brief findBInB2B
 * @param buildings
 * @param building
 * @return the postion of a building in a Building_building vector, if the building
 * is not in the building_building it return -1
 */
int findBInB2B(std::vector<Building*> buildings, Building* building)
{
    for(unsigned int i = 0; i < buildings.size(); i++ ) {
        if( buildings[i]== building) {
            return i;
       }
    }
    return -1;
}

/**
 * @brief getColorB2B
 * @param tech
 * @return the string of the color of a building.
 */
string getColorB2B(NTechnology::Technology* tech){
    switch (*tech)
    {
    case NTechnology::WIFI:
        return "blue";
    break;

    case NTechnology::ETHERNET:
        return "black";
    break;

    case NTechnology::FIBER:
        return "red";
    break;

    case NTechnology::INFRARED:
        return "purple";
    break;

    case NTechnology::TWISTEDPAIR:
        return "yellow";
    break;

    default:
        return "darkorange";
    break;
}
}
/**
 * @brief createClusterName
 * @param position
 * @return the name of the cluster, eg. "cluste_1"
 */
string createClusterName(int position)
{
    stringstream building1_stream;
    building1_stream << "cluster_" << position;
    string cluster_name = building1_stream.str();
    return cluster_name;
}

/**
 * Draw a cluster with a name and a label in a ofstream file.
 * @brief drawCluster
 * @param file
 * @param name
 * @param legend
 * @param props
 */
void drawCluster(ofstream& file, string name, string legend, string props=""){
    string name_no_underscore = replaceSpacesByUnderscores(name);
    file << "subgraph "<< name_no_underscore << "{"<< endl
         << "label = \""
         << legend <<"\""
         << props<< endl
         <<  "}"<< endl <<endl;
}

/**
 * @brief generateLabel
 * @param line1
 * @param line2
 * @param line3
 * @return the label with mininum two lines.
 */
string generateLabel(string line1, string line2="", string line3=""){
    stringstream label_stream;
    label_stream << line1;
    if( line2 != ""){
        label_stream << " \\n" << line2 ;
    }
    if( line3 != ""){
        label_stream << " \\n" << line3 ;
    }
    string cluster_name = label_stream.str();
    return cluster_name;
}
/**
 * Draw a location in file given a name, a location and eventually properties.
 * @brief drawLocationStr
 * @param file
 * @param name
 * @param location
 * @param props
 */
void drawLocationStr(ofstream& file, string name, Location* location, string props= ""){
    //we create the first line with name.
    string label_line1;
    label_line1=location->getName();

    //We create the line 2 with the IP address:
    Component* comp = (location->getComponents()).front();
    string IP =  comp->getAddress().toString();
    string label_line2=IP;

    string label= generateLabel(label_line1,label_line2);
    drawCluster(file,name,label,props);
}
/**
 * Allow to draw a location with given an interger.
 * @brief drawLocation
 * @param file
 * @param int_name
 * @param location
 */
void drawLocation(ofstream& file, int int_name, Location* location){
    string name = createClusterName(int_name);
    drawLocationStr(file, name, location);
}
/**
 * Constructor
 * @brief GraphGenerate::GraphGenerate
 * @param request
 * @param folder
 */
GraphGenerate::GraphGenerate(Request* request, string folder):request(request), folder(folder)
{
}

/**
 * Generate all the graphs given a request.
 * @brief GraphGenerate::graphGenerateAll
 */
void GraphGenerate::graphGenerateAll(){
    globalGraphGenerate();
    std::vector<Building*> bs =request->getBuildings();
    for(unsigned int ii=0; ii < bs.size(); ii++)
    {
        graphBuildingGenerate(bs[ii]);
    }
}

/**
 * Generates the detailled graph for a given building.
 * @brief GraphGenerate::graphBuildingGenerate
 * @param building
 */
void GraphGenerate::graphBuildingGenerate(Building* building){
    //we create the stream and folder
    string building_name=(building->getName());
    string file_name ="graph_building_"+replaceSpacesByUnderscores(building_name);

    ofstream myfile;
    myfile.open (( this->folder+"/"+file_name+".txt").c_str());
    myfile << "graph G {" << endl;

    //We start by drawing the L2L3
    if(building->isAdmin()){
        //We draw the firewall
        Firewall* firewall = (Firewall*) (building->getComponents())[0];
        string public_IP_firewall = firewall->getPublicAddress().toString();
        string private_IP_firewall = firewall->getAddress().toString();

        string label =generateLabel("Firewall", "IP Publique: "+public_IP_firewall, "IP Privé: "+private_IP_firewall) ;
        drawCluster(myfile, "cluster_firewall",label);

        //We draw the router
        Router* router= (Router*)building->getComponents()[1];
        string IP_router =  router->getAddress().toString();

        label =generateLabel("Router",IP_router) ;
        drawCluster(myfile, "cluster_L2L3",label);
        myfile << "cluster_L2L3"<< "--" <<  "cluster_firewall"<< endl;
    }else{
        // we just draw the switch of the floor.
        Component* L2 = building->getComponents()[0];
        string IP_switch =  L2->getAddress().toString();

        string label =generateLabel("Switch",IP_switch) ;
        drawCluster(myfile, "cluster_L2L3",label);
    }

    //Then we draw the floors.
    vector<Floor*> floors= building->getFloors();
    for(unsigned int ii=0; ii < floors.size(); ii++)
    {
        Floor* floor= floors[ii];
        int component_number = floor->getComponents().size();

        //If it's a normal floor.
        if(component_number==1){
            drawLocation(myfile,ii , floors[ii]);
            myfile << "cluster_L2L3 " << " -- " << "cluster_" << ii <<endl<<endl;

        //If it's a special floor (with servers)
        }else if(component_number==2){
            //First the firewall
            stringstream firewall_label_stream;
            firewall_label_stream << "FW " << floor->getName();
            string firewall_label = firewall_label_stream.str();

            string label =generateLabel(firewall_label) ;
            stringstream firewall_stream;
            firewall_stream << "cluster_firewall_special_floor" << ii;
            string firewall_name = firewall_stream.str();
            drawCluster(myfile, firewall_name ,label);

            //We draw the router
            Switch* switch_floor= (Switch*)building->getComponents()[1];
            string IP_router =  switch_floor->getAddress().toString();

            label =generateLabel(floor->getName(),IP_router) ;

            stringstream L2L3_name_stream;
            L2L3_name_stream << "cluster_L2L3_special_floor" << ii;
            string L2L3_name = L2L3_name_stream.str();
			
            drawCluster(myfile, L2L3_name,label);
            myfile << "cluster_L2L3" << "--" <<  "cluster_firewall_special_floor"<< ii << endl;

            myfile << "cluster_firewall_special_floor"<<ii << "--"
                   << "cluster_L2L3_special_floor"<< ii << endl;
    }

    //We create the links with the others buildings.
    std::vector<Building_Building*> b2bs= request->getBuilding_Buildings();
    for(unsigned int ii=0; ii < b2bs.size(); ii++)
    {
    Building_Building* building_Building=b2bs[ii];
    NTechnology::Technology tech = building_Building->getAppliedTechnology();
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
            string props ="color=\"green\" style=\"filled\"";
            drawLocationStr(myfile,name_connected_building, building_to_build,props);

            myfile << name_connected_building << " -- " << "cluster_L2L3 "
                   << "[color = \"" <<getColorB2B(&tech)<<"\"]"<<endl;
        }
    }

    myfile << "graph [label=\"Map of " << building_name << "\" bgcolor=\"transparent\"]"<< endl;
    myfile << this->legend;
    myfile <<endl<< "}" << endl;
    myfile.close();

    //  Generate the file using GraphViz.
    system (("fdp -Tpng "+this->folder+"/"+file_name+".txt >"+this->folder+"/"+file_name+".png").c_str());
}
}

/**
 * Generates the graph for the full organization.
 * @brief GraphGenerate::globalGraphGenerate
 */
void GraphGenerate::globalGraphGenerate(){
    std::vector<Building*> bs =request->getBuildings();
    std::vector<Building_Building*> b2bs= request->getBuilding_Buildings();

    ofstream myfile;
    string file_name ="global_graph";
    myfile.open ( (this->folder+"/"+file_name+".txt").c_str());
    myfile << "graph G {" << endl;

    //First we draw all the buildings.
    for(unsigned int ii=0; ii < bs.size(); ii++)
    {
        drawLocation(myfile,ii , bs[ii]);
    }
    //Then we create the links between them.
    for(unsigned int ii=0; ii < b2bs.size(); ii++)
    {
        Building_Building* building_Building=b2bs[ii];
        NTechnology::Technology tech = building_Building->getAppliedTechnology();

        Building* building1=building_Building->getBuilding1();
        int positionBuilding1= findBInB2B(bs, building1);
        string cluster1= createClusterName(positionBuilding1);

        Building* building2=building_Building->getBuilding2();
        int positionBuilding2= findBInB2B(bs, building2);
        string cluster2= createClusterName(positionBuilding2);

        myfile << cluster1 << " -- " << cluster2 << "[color = \"" <<getColorB2B(&tech)<<"\"]"<<endl;
    }

    myfile << "graph [label=\"Global map\" bgcolor=\"transparent\"]"<< endl;
    myfile << this->legend;
    myfile <<endl<< "}" << endl;
    myfile.close();

//  Generate the image for the graph with Graphviz.
    system (("fdp -Tpng "+this->folder+"/"+file_name+".txt >"+this->folder+"/"+file_name+".png").c_str());
}
