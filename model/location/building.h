/*
 * building.h
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#ifndef BUILDING_H_
#define BUILDING_H_

#include <vector>
#include "floor.h"

class Building: public Location {

public:
    Building();
    Building(std::string name, bool admin = false);
    std::vector<Floor*> getFloors();
    Floor* addFloor();
    int getFloorsNumber();
    Floor getAdminFloor();
    bool isAdmin();
    void setAdmin(bool isAdmin);
private:
    std::vector<Floor*> floors;
    bool admin;
};

#endif /* BUILDING_H_ */
