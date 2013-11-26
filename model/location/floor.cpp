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

Address Floor::setBroadcastAddress(Address newBroadcastAddress){
    this->broadcastAddress = newBroadcastAddress;
}

Address Floor::setNetworkAddress(Address newNetworkAddress){
    this->networkAddress = newNetworkAddress;
}

void Floor::getBroadcastAddress(){
    return broadcastAddress;
}

void Floor::getNetworkAddress(){
    return networkAddress;
}
