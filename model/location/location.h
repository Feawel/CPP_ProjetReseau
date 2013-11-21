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
    Location(std::string name);
    unsigned int getUserNumber(NUserType::UserType userType) const;
    std::vector<int> getUserNumbers() const;
    void setUserNumber(NUserType::UserType userType, unsigned int userNumber);
    void cantUseTechnology(NTechnology::Technology technology);
    std::vector<NTechnology::Technology> getCantUseTechs();
    std::vector<Component> getComponents();
    void addComponent(Component newComponent);
    std::string getName();
    void setName(std::string name);

private:
    std::vector<int> userNumbers;
    std::vector<NTechnology::Technology> cantUseTechs;
    std::vector<Component> components;
    std::string name;
};

#endif /* LIEU_H_ */
