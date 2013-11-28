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
#include "model/component/firewall.h"


class Building: public Location {

public:
    Building();
    ~Building();
    Building(std::string name, bool admin = false);
    std::vector<Floor*> getFloors();
    Floor* addFloor();
    int getFloorsNumber();
    Firewall* getFirewall(std::vector<Component> components);
    bool isAdmin();
    void setAdmin(bool isAdmin);
    void addSpecialSection(Floor* newSpecialSection);

private:
    std::vector<Floor*> floors;
    bool admin;
};

#endif /* BUILDING_H_ */
