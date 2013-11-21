/*
 * building.cpp
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#include <vector>
#include "building.h"

using namespace std;

Building::Building() :
		Location() {
}

Building::Building(int userNumber, string name, bool admin) :
        Location(userNumber, name) {
}

vector<Floor> Building::getFloors() {
	return floors;
}

void Building::addFloor(int userNumber) {
	Floor newFloor(userNumber, floors.size() + 1);
	floors.push_back(newFloor);
	userNumber += userNumber;
}

int Building::getFloorsNumber(){
	return floors.size();
}

bool Building::isAdmin(){
    return admin;
}
