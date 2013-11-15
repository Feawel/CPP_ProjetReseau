/*
 * main.cpp
 *
 *  Created on: 15 nov. 2013
 *      Author: MOULIN
 */

#include <iostream>
#include "model/address.h"
#include "model/component/component.h"

using namespace std;

int main() {
	Address address(255, 255, 255, 255, 0);
	cout << address << endl;

	Component component;
	component.setAddress(address);
	cout << component.getAddress() << endl;

	return 0;
}

