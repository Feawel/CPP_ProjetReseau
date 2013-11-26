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
    Building_Building(Building *building1, Building *building2, double distance = 0,bool visibility=true);
    void addExistingTechnology(NTechnology::Technology technology);
    double getDistance();
    Building* getBuilding1();
    Building* getBuilding2();
    bool getVisibility();
    std::vector<NTechnology::Technology> getExistingTechs();
    void setDistance(double distance);

private:
    double distance;
    Building *building1;
    Building *building2;
    bool visibility;
    std::vector<NTechnology::Technology> existingTechs;
};

#endif /* BUILDING_BUILDING_H_ */
