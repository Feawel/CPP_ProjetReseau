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

Building::Building(int userNumber) :
		Location(userNumber) {
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


vector<Component> Building::getComponents() {
	return components;
}

void Building::addComponent(Component newComponent) {
	components.push_back(newComponent);
}