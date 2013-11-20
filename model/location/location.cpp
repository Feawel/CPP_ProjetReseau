/*
 * lieu.cpp
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#include "location.h"
#include "../component/component.h"
using namespace std;

Location::Location() :
    userNumber(0) ,name(""){
}

Location::Location(unsigned int userNumber, string name) :
    userNumber(userNumber), name(name){
}

unsigned int Location::getUserNumber() const {
	return userNumber;
}

void Location::setUserNumber(unsigned int userNumber) {
	this->userNumber = userNumber;
}

void Location::cantUseTechnology(Technology technology) {
	cantUseTechs.push_back(technology);
}

std::vector<Technology> Location::getCantUseTechs() {
	return cantUseTechs;
}


vector<Component> Location::getComponents() {
    return components;
}

void Location::addComponent(Component newComponent) {
    components.push_back(newComponent);
}

std::string Location::getName()
{
    return name;
}

void Location::setName(std::string name)
{
    this->name= name;
}
