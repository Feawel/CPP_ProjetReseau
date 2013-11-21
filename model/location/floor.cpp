/*
 * floor.cpp
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#include "floor.h"
using namespace std;

Floor::Floor(int floorNumber) :
    Location("Floor " + floorNumber), floorNumber(floorNumber) {
}

int Floor::getFloorNumber() {
	return floorNumber;
}

