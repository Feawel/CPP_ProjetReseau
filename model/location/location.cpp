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

Location::Location(int userNumber) :
		userNumber(userNumber) {
}

int Location::getUserNumber() const {
	return userNumber;
}

void Location::setUserNumber(int userNumber) {
	this->userNumber = userNumber;
}
