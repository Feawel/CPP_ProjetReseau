/*
 *
 * building.cpp
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#include "building.h"
#include <sstream>

using namespace std;

Building::Building() :
    Location(), floors(0) {
}

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

vector<Floor*> Building::getFloors() {
    return floors;
}

Floor* Building::addFloor() {
    std::ostringstream oss;
    oss << "Floor " << (floors.size() + 1);
    Floor* newFloor = new Floor(oss.str(),floors.size() + 1);
    floors.push_back(newFloor);
    return newFloor;
}

void Building::addSpecialSection(Floor* newSpecialSection){
    floors.push_back(newSpecialSection);
}

int Building::getFloorsNumber(){
    return floors.size();
}

bool Building::isAdmin(){
    return admin;
}

//Retourne un pointeur sur le firewall du building
Firewall* Building::getFirewall(vector<Component> components){
    for(int k=0; k<components.size();k++){
        if(typeid(components[k]) == typeid(Firewall)){
            return (Firewall*)&components[k];
        }
    }
}

void Building::setAdmin(bool isAdmin)
{
    admin=isAdmin;
}
