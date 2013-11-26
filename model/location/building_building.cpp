/*
 * building_building.cpp
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */
#include "building_building.h"

Building_Building::Building_Building(Building *building1, Building *building2,
        double distance, bool visibility) :
        building1(building1), building2(building2), distance(distance), visibility(
                visibility)
{
}

/**
 * Add a existing technology between 2 buildings
 */
void Building_Building::addExistingTechnology(NTechnology::Technology technology) {
    existingTechs.push_back(technology);
}

double Building_Building::getDistance() {
    return distance;
}

bool Building_Building::getVisibility() {
    return visibility;
}

Building* Building_Building::getBuilding1() {
    return building1;
}

Building* Building_Building::getBuilding2() {
    return building2;
}

std::vector<NTechnology::Technology> Building_Building::getExistingTechs() {
    return existingTechs;
}

void Building_Building::setDistance(double distance)
{
    this->distance=distance;
}
