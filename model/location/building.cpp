/*
 *
 * building.cpp
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#include "building.h"
#include <sstream>
#include <typeinfo>

using namespace std;

Building::~Building()
{
    for(unsigned int i = 0; i< floors.size(); i++)
    {
        delete floors[i];
    }
}

Building::Building(string name, bool admin) :
    Location(name), admin(admin) {
}

/**
 * @brief Building::getFloors
 * @return all floors (array) for the current building
 */
vector<Floor*> Building::getFloors() {
    return floors;
}

/**
 * @brief Building::addFloor
 * @return the newFloor (ptr)
 * create a floor in the current building
 */
Floor* Building::addFloor() {
    Floor* newFloor = new Floor("Floor "+Constant::numberToString(floors.size()),floors.size());
    floors.push_back(newFloor);
    return newFloor;
}

/**
 * @brief Building::addSpecialSection
 * @param newSpecialSection
 * add a virtual floor for admin section and private serveurs
 */
void Building::addSpecialSection(Floor* newSpecialSection){
    floors.push_back(newSpecialSection);
}

/**
 * @brief Building::getFloorsNumber
 * @return number of floors
 */
int Building::getFloorsNumber(){
    return floors.size();
}

/**
 * @brief Building::isAdmin
 * @return if the building is an admin one
 */
bool Building::isAdmin(){
    return admin;
}

/**
 * @brief Building::setAdmin
 * @param isAdmin
 * set building admin status to isAdmin
 */
void Building::setAdmin(bool isAdmin)
{
    admin=isAdmin;
}
