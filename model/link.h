/*
 * link.h
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#ifndef LINK_H_
#define LINK_H_

#include "component/component.h"

class Link {
public:
	Link(Component *component1, Component *component2);

private:
	Component *component1;
	Component *component2;

};

#endif /* LINK_H_ */
