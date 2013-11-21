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
        userNumbers(3, 0), name("") {
}

Location::Location(string name) :
        userNumbers(3, 0), name(name) {
}

vector<int> Location::getUserNumbers() const {
    return userNumbers;
}

unsigned int Location::getUserNumber(NUserType::UserType userType) const {
    return userNumbers[userType];
}

void Location::setUserNumber(NUserType::UserType userType, unsigned int userNumber) {
    userNumbers[userType]=userNumber;
}

void Location::cantUseTechnology(NTechnology::Technology technology) {
    cantUseTechs.push_back(technology);
}

std::vector<NTechnology::Technology> Location::getCantUseTechs() {
    return cantUseTechs;
}

vector<Component> Location::getComponents() {
    return components;
}

void Location::addComponent(Component newComponent) {
    components.push_back(newComponent);
}

std::string Location::getName() {
    return name;
}

void Location::setName(std::string name) {
    this->name = name;
}
