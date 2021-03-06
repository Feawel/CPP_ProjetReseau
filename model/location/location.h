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
    Location(std::string name);
    unsigned int getUserNumber(NUserType::UserType userType) const;
    std::vector<int> getUserNumbers() const;
    void setUserNumber(NUserType::UserType userType, unsigned int userNumber);
    void setUseTechnology(NTechnology::Technology technology, bool use);
    std::vector<bool> getUseTechs();
    std::vector<Component*> getComponents();
    void addComponent(Component* newComponent);
    std::string getName();
    void setName(std::string name);
    bool isUsersNull() const;

private:
    std::vector<int> userNumbers;
    std::vector<bool> useTechs;
    std::vector<Component*> components;
    std::string name;
};

#endif /* LIEU_H_ */
