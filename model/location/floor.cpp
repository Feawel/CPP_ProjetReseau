/*
 * floor.cpp
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#include "floor.h"
using namespace std;

Floor::Floor(int floorNumber) :
		Location(), floorNumber(floorNumber) {
}

Floor::Floor(int userNumber, int floorNumber) :
		Location(userNumber), floorNumber(floorNumber) {
}

int Floor::getFloorNumber() {
	return floorNumber;
}

