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

Building::Building(string name, bool admin) :
    Location(name), admin(admin) {
}

vector<Floor> Building::getFloors() {
    return floors;
}

void Building::addFloor() {
    Floor newFloor(floors.size() + 1);
    floors.push_back(newFloor);
}

int Building::getFloorsNumber(){
    return floors.size();
}

bool Building::isAdmin(){
    return admin;
}
