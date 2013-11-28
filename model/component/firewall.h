/*
 * firewall.h
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#ifndef FIREWALL_H_
#define FIREWALL_H_

#include "model/component/component.h"


class Firewall: public Component {
public:
    Firewall();
    std::string getRules() const;
    void setRules(std::string newRules);

    void setPublicAddress(Address newPublicAddress);
    Address getPublicAddress() const;

private:
    std::string rules;
    Address publicAddress;
};

#endif /* FIREWALL_H_ */
