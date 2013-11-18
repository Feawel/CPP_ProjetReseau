/*
 * building_building.h
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#ifndef BUILDING_BUILDING_H_
#define BUILDING_BUILDING_H_

#include "building.h"
#include "../constant.h"
#include <vector>

class Building_Building {

public:
	Building_Building(Building *building1, Building *building2, float distance,bool visibility);
	void addExistingTechnology(Technology technology);
	float getDistance();
	std::vector<Technology> getExistingTechs();

private:
	float distance;
	Building *building1;
	Building *building2;
	bool visibility;
	std::vector<Technology> existingTechs;
};

#endif /* BUILDING_BUILDING_H_ */
