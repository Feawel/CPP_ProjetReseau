/*
 * firewall.cpp
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#include "model/component/firewall.h"
#include "../constant.h"

Firewall::Firewall()
{

}

std::string Firewall::getRules() const
{
    return rules;
}

void Firewall::setRules(Request request)
{
    std::string newRules;


    this->rules=newRules;
}
