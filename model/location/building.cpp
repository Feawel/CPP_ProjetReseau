/*
 * building.cpp
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#include <vector>
#include "building.h"

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
    Floor* newFloor = new Floor(floors.size() + 1);
    floors.push_back(newFloor);
    return newFloor;
}

int Building::getFloorsNumber(){
    return floors.size();
}

bool Building::isAdmin(){
    return admin;
}

//Retourne un pointeur sur l'adminFloor
Floor Building::getAdminFloor(){
    /*
     *Ici faut qu'on se mette d'accord sur la méthode...Par exemple la partie admin
     *a un numéro de floor défini à 100 ? Après tout ce n'est pas vraiment un étage,
     *mais plutot une division du batiment (salle, ensemble de salles etc...) qui
     *est isolé du reste.
     *
     *On pourrait par exemple envisager :
     */

//    this->addFloor();
//    Floor adminFloor = this->getFloors().back();
//    return adminFloor;
     /*Dans ce cas on se charge nous meme d'ajouter la partie admin, qui sera présente
     *dans tout réseau.
     */
}

void Building::setAdmin(bool isAdmin)
{
    admin=isAdmin;
}

/**
 * @brief Building::getB2bs
 * @param b2bs
 * @return all b2b adjacents to current building
 */
vector<Building_Building*> Building::getB2bs(vector<Building_Building*> b2bs) const
{
    vector<Building_Building*> currentB2bs;
    for(unsigned int i = 0; i< b2bs.size(); i++)
    {
        if(b2bs[i]->getbuilding1()==*this)
            currentB2bs.push_back(b2bs[i]);
        else if(b2bs[i]->getbuilding2()==*this)
            currentB2bs.push_back(b2bs[i]);
    }
    return currentB2bs;
}
