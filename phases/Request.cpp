//
//  Request.cpp
//  NetworkBuilder
//
//  Created by Jonathan Banon on 21/11/2013.
//  Copyright (c) 2013 Jonathan Banon. All rights reserved.
//

#include "request.h"
#include <vector>
#include "../model/location/building.h"
#include "../model/location/building_building.h"

// basic file operations
#include <iostream>
#include <fstream>
using namespace std;

Request::Request() : buildings(0), building_buildings(0)
{
}

/**
 * @brief Request::getBuildings
 * @return array with all the buildings created by the user
 */
vector<Building*> Request::getBuildings() {
    return buildings;
}

/**
 * @brief Request::addBuilding
 * @param newBuilding
 * add one building to the request
 */
void Request::addBuilding(Building* newBuilding) {
    buildings.push_back(newBuilding);
}

/**
 * @brief Request::removeBuilding
 * @param id
 * erase one building of the request
 */
void Request::removeBuilding(int id) {
    buildings.erase(buildings.begin()+id);
}

/**
 * @brief Request::getBuilding_Buildings
 * @return array of building_building between all the buildings defined by the user
 */
vector<Building_Building*> Request::getBuilding_Buildings() {
    return building_buildings;
}

/**
 * @brief Request::addBuilding_Building
 * @param newBuilding_Buildings
 * add one building_building to the request
 */
void Request::addBuilding_Building(Building_Building* newBuilding_Building) {
    building_buildings.push_back(newBuilding_Building);
}

/**
 * @brief Request::removeBuilding_Building
 * @param id
 * erase one building_building of the request
 */
void Request::removeBuilding_Building(int id) {
    building_buildings.erase(building_buildings.begin()+id);
}

void Request::setBuilding_Buildings(std::vector<Building_Building*> newBuilding_buildings){
    building_buildings = newBuilding_buildings;
}



/**
 * @brief Request::generateGraphText
 */
void Request::generateGraphText(){
    //mockup:
    Building b1=Building("B1");
    Building b2=Building("B2");
    Building b3=Building("B3");

    vector<Building*> bs;
    bs.push_back(&b1);
    bs.push_back(&b2);
    bs.push_back(&b3);

    for(int ii=0; ii < bs.size(); ii++)
    {
        cout << (*bs[ii]).getName() << endl;
    }

    ofstream myfile;
    cout << '\n';
    myfile.open ("example.txt");
    myfile << "Writing this to a file.\n";
    myfile.close();
}

/**
 * @brief Request::checkData
 * @return error message
 * check if the request has data ok for process
 */
string Request::checkData()
{
    // check if there is at least 2 buildings
    if(buildings.size()<2)
        return "You need to define at least 2 buildings";

    // check if there is an admin building
    bool hasAdmin;
    for(unsigned int i = 0; i<buildings.size(); i++ )
    {
        if(buildings[i]->isAdmin())
        {
            hasAdmin =true;
            break;
        }
    }

    if(!hasAdmin)
        return "You need to define an admin building";

    // return "", no error
    return "";
}
