/*
 * firewall.h
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#ifndef FIREWALL_H_
#define FIREWALL_H_

#include "model/component/component.h"
#include "phases/request.h"

class Firewall: public Component {
public:
    Firewall();
    std::string getRules() const;
    void setRules(Request request);

private:
    std::string rules;
};

#endif /* FIREWALL_H_ */
