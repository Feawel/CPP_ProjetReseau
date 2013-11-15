/*
 * component.h
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "../address.h"

class Component {
public:
	Address getAddress() const;
	void setAddress(Address adress);

private:
	Address address;
};

#endif /* COMPONENT_H_ */
