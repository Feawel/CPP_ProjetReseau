/*
 * component.cpp
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#include "component.h"
#include "../address.h"

Component::Component()
{

}

Component::Component(Address address): address(address)
{

}

Address Component::getAddress() const
{
	return address;
}

void Component::setAddress(Address address)
{
	this->address=address;
}


