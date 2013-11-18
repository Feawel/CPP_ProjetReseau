/*
 * lieu.cpp
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#include "location.h"
using namespace std;

Location::Location() :
		userNumber(0) {
}

Location::Location(unsigned int userNumber) :
		userNumber(userNumber) {
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
