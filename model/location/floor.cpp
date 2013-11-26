/*
 * floor.cpp
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#include "floor.h"
using namespace std;

Floor::Floor(int floorNumber) :
    Location("Floor"), floorNumber(floorNumber) {
}

int Floor::getFloorNumber() {
    return floorNumber;
}

void Floor::setBroadcastAddress(Address newBroadcastAddress){
    this->broadcastAddress = newBroadcastAddress;
}

void Floor::setNetworkAddress(Address newNetworkAddress){
    this->networkAddress = newNetworkAddress;
}

Address Floor::getBroadcastAddress(){
    return broadcastAddress;
}

Address Floor::getNetworkAddress(){
    return networkAddress;
}


