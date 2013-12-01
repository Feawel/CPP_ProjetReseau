/*
 * building.h
 *
 *  Created on: 4 nov. 2013
 *      Author: BANON
 */

#include <vector>
#include "../model/location/building.h"
#include "../model/location/floor.h"
#include "../model/component/firewall.h"


class TestsBuilding {

public:
    ~TestsBuilding();

    bool testGetFloors();
    bool testIsAdmin();
    bool testGetFirewall();


};


