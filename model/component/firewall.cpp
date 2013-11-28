/*
 * firewall.cpp
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#include "model/component/firewall.h"
#include "../constant.h"

using namespace std;

Firewall::Firewall()
{

}

std::string Firewall::getRules() const
{
    return rules;
}

void Firewall::setRules(string newRules)
{
    this->rules=newRules;
}


Address Firewall::getPublicAddress() const
{
    return publicAddress;
}

void Firewall::setPublicAddress(Address newPublicAddress)
{
    this->publicAddress=newPublicAddress;
}
