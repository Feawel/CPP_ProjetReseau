/*
 * floor.h
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#ifndef FLOOR_H_
#define FLOOR_H_

#include "location.h"

class Floor: public Location {

public:
	Floor(int floorNumber);
	Floor(int userNumber,int floorNumber);
	int getFloorNumber();

private:
	int floorNumber;

};

#endif /* FLOOR_H_ */
