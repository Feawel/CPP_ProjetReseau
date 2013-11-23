//
//  Request.cpp
//  NetworkBuilder
//
//  Created by Jonathan Banon on 21/11/2013.
//  Copyright (c) 2013 Jonathan Banon. All rights reserved.
//

#include "Request.h"
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

Request::Request(std::vector<Building*> b,std::vector<Building_Building*> b2b) : buildings(b), building_buildings(b2b)
{
}

vector<Building*> Request::getBuildings() {
    return buildings;
}

void Request::addBuilding(Building* newBuilding) {
    buildings.push_back(newBuilding);
}

void Request::removeBuilding(int id) {
    buildings.erase(buildings.begin()+id);
}

vector<Building_Building*> Request::getBuilding_Buildings() {
    return building_buildings;
}

void Request::addBuilding_Building(Building_Building* newBuilding_Buildings) {
    building_buildings.push_back(newBuilding_Buildings);
}

void Request::removeBuilding_Building(int id) {
    building_buildings.erase(building_buildings.begin()+id);
}
void Request::generateGraphText(){
    ofstream myfile;
    std::cout << '\n';
    myfile.open ("example.txt");
    myfile << "Writing this to a file.\n";
    myfile.close();
}
