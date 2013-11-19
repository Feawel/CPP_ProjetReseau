/*
 * lieu.h
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#ifndef LIEU_H_
#define LIEU_H_

#include <vector>
#include "../constant.h"
#include "../component/component.h"

class Location {

public:
	Location();
	Location(unsigned int userNumber);
	unsigned int getUserNumber() const;
	void setUserNumber(unsigned int userNumber);
	void cantUseTechnology(Technology technology);
	std::vector<Technology> getCantUseTechs();
    std::vector<Component> getComponents();
    void addComponent(Component newComponent);

private:
	unsigned int userNumber;
	std::vector<Technology> cantUseTechs;
    std::vector<Component> components;
};

#endif /* LIEU_H_ */
