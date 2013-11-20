/*
 * location.h
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#ifndef LOCATION_H_
#define LOCATION_H_

#include <vector>
#include <string>
#include "../constant.h"
#include "../component/component.h"

class Location {

public:
	Location();
    Location(unsigned int userNumber, std::string name);
	unsigned int getUserNumber() const;
	void setUserNumber(unsigned int userNumber);
	void cantUseTechnology(Technology technology);
	std::vector<Technology> getCantUseTechs();
    std::vector<Component> getComponents();
    void addComponent(Component newComponent);
    std::string getName();
    void setName(std::string name);

private:
	unsigned int userNumber;
	std::vector<Technology> cantUseTechs;
    std::vector<Component> components;
    std::string name;
};

#endif /* LIEU_H_ */
