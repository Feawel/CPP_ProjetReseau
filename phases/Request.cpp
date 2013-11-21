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

using namespace std;

Request::Request() : buildings(0)
{
}

vector<Building> Request::getBuildings() {
    return buildings;
}

void Request::addBuilding(Building newBuilding) {
    buildings.push_back(newBuilding);
}

void Request::removeBuilding(int id) {
    buildings.erase(buildings.begin()+id);
}
