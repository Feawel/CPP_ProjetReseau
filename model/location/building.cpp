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
