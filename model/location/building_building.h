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
    void setExistingTechnology(NTechnology::Technology technology, bool exist);
    double getDistance() const;
    Building* getBuilding1() const;
    Building* getBuilding2() const;
    bool getVisibility() const;
    std::vector<bool> getExistingTechs() const;
    bool isExistingTechs(NTechnology::Technology technology) const;
    void setDistance(double distance);
    bool existTech() const;

private:
    double distance;
    Building *building1;
    Building *building2;
    bool visibility;
    std::vector<bool> existingTechs;
};

#endif /* BUILDING_BUILDING_H_ */
