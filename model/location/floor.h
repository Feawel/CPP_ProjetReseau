/*
 * floor.h
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#ifndef FLOOR_H_
#define FLOOR_H_

#include "location.h"

class Floor: public Location {

public:
    Floor(int floorNumber);
	int getFloorNumber();
    Address setBroadcastAddress(Address newBroadcastAddress);
    Address setNetworkAddress(Address newNetworkAddress);
    void getBroadcastAddress();
    void getNetworkAddress();

private:
	int floorNumber;
    Address broadcastAddress;
    Address networkAddress;

};

#endif /* FLOOR_H_ */
