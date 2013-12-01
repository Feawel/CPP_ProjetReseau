/*
 *
 * building.cpp
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#include "TestsBuilding.h"


using namespace std;

Building::~Building()
{

}

bool TestsBuilding::testGetFloors() {
    bool result = false, testPart1 = false, testPart2 = false;
    Building building1("Building 1");
    vector<Floor*> floors = building1.getFloors();
    if(floors.empty())
            testPart1 = true;
    Floor* newFloor = new Floor("Floor Test", 0);
    building1.addSpecialSection(newFloor);
    vector<Floor*> floors2 = building1.getFloors();
    if(floors2[0] == newFloor)
        testPart2 = true;
    if (testPart1 && testPart2)
        result = true;
    return result;
}



bool TestsBuilding::testIsAdmin() {
    bool result = false, testPart1 = false, testPart2 = false;
    Building building1("Building 1");
    bool isAdmin = building1.isAdmin();
    if(!isAdmin)
        testPart1 = true;
    building1.setAdmin(true);
    bool isAdmin2 = building1.isAdmin();
    if(isAdmin2)
        testPart2 = true;
    return result;
}

//bool TestsBuilding::testGetFirewall(){
//    Firewall* newFirewall = new Firewall();
//    Building building1("Building test");
//    building1.addComponent(newFirewall);
//    vector<Component*> components = building1.getComponents();
//    Firewall* testFirewall = building1.getFirewall(*components);
//    if(newFirewall == testFirewall)
//        return true;
//    else
//        return false;
//}
