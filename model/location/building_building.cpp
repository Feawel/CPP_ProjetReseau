/*
 * building_building.cpp
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */
#include "building_building.h"

Building_Building::Building_Building(Building *building1, Building *building2,
        double distance, bool visibility) :
    building1(building1), building2(building2), distance(distance), visibility(visibility), existingTechsSize(4), existingTechs(existingTechsSize,false)
{
}

/**
 * Add a existing technology between 2 buildings
 */
void Building_Building::setExistingTechnology(NTechnology::Technology technology, bool exist) {
    existingTechs[technology]=exist;
}

double Building_Building::getDistance() const {
    return distance;
}

bool Building_Building::getVisibility() const {
    return visibility;
}

Building* Building_Building::getBuilding1() const{
    return building1;
}

Building* Building_Building::getBuilding2() const{
    return building2;
}

std::vector<bool> Building_Building::getExistingTechs() const{
    return existingTechs;
}

bool Building_Building::isExistingTechs(NTechnology::Technology technology) const
{
    return existingTechs[technology];
}

void Building_Building::setDistance(double distance)
{
    this->distance=distance;
}

bool Building_Building::existingTechs() const
{
   return existingTechs[NTechnology::FIBER] || existingTechs[NTechnology::TWISTEDPAIR] || existingTechs[NTechnology::WIFI] || existingTechs[NTechnology::INFRARED];
}
