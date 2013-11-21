//
//  Request.cpp
//  NetworkBuilder
//
//  Created by Jonathan Banon on 21/11/2013.
//  Copyright (c) 2013 Jonathan Banon. All rights reserved.
//

#include "Request.h"
#include <vector>
#include "building.cpp"


using namespace std;

Request::Request(vector<Building>) :
{
}

vector<Floor> Building::getBuildings() {
	return buildings;
}

void Request::addBuilding(int userNumber, string name, bool admin=false) {
	Building newBuilding(userNumber, name, admin);
	buildings.push_back(newBuilding);
}

void Request::removeBuilding(iterator it) {
	buildings.erase(it);
}