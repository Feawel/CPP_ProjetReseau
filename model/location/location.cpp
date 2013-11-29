/*
 * lieu.cpp
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#include "location.h"
#include "../component/component.h"
using namespace std;

Location::Location(string name) :
    userNumbers(3, 0), name(name), useTechs(5,true) {
    useTechs[NTechnology::FIBER]=false;
    useTechs[NTechnology::TWISTEDPAIR]=false;
    useTechs[NTechnology::INFRARED]=false;
}


/**
 * @brief Location::getUserNumbers
 * @return array with user number of each type of user (NUserType::UserType)
 */
vector<int> Location::getUserNumbers() const {
    return userNumbers;
}

/**
 * @brief Location::getUserNumber
 * @param userType
 * @return user number of the userType
 */
unsigned int Location::getUserNumber(NUserType::UserType userType) const {
    int index = userType;
    return userNumbers[index];
}

/**
 * @brief Location::setUserNumber
 * @param userType
 * @param userNumber
 * set the user number for the userType to userNumber
 */
void Location::setUserNumber(NUserType::UserType userType, unsigned int userNumber) {
    userNumbers[userType]=userNumber;
}

/**
 * @brief Location::setUseTechnology
 * @param technology
 */
void Location::setUseTechnology(NTechnology::Technology technology, bool use) {
    useTechs[technology]=use;
}

/**
 * @brief Location::getUseTechs
 * @return
 */
std::vector<bool> Location::getUseTechs() {
    return useTechs;
}

/**
 * @brief Location::getComponents
 * @return all components of the location (vector)
 */
vector<Component> Location::getComponents() {
    return components;
}

/**
 * @brief Location::addComponent
 * @param newComponent
 * add a component on the location
 */
void Location::addComponent(Component newComponent) {
    components.push_back(newComponent);
}

/**
 * @brief Location::getName
 * @return building name
 */
std::string Location::getName() {
    return name;
}

/**
 * @brief Location::setName
 * @param name
 * set building name to naame
 */
void Location::setName(std::string name) {
    this->name = name;
}

/**
 * @brief Location::isUsersNull
 * @return check if all users number == 0 (bool)
 */
bool Location::isUsersNull() const
{
    if(getUserNumber(NUserType::DEFAULT)!=0)
        return false;
    else if(getUserNumber(NUserType::SUP)!=0)
        return false;
    else if(getUserNumber(NUserType::ADMIN)!=0)
        return false;
    return true;
}
