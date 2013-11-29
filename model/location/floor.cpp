/*
 * floor.cpp
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#include "floor.h"
using namespace std;

Floor::Floor(string name, int floorNumber) :
    Location(name), floorNumber(floorNumber) {
}

/**
 * @brief Floor::getFloorNumber
 * @return the floor number
 */
int Floor::getFloorNumber() {
    return floorNumber;
}

/**
 * @brief Floor::setBroadcastAddress
 * @param newBroadcastAddress
 * set the broadcast adress of the floor
 */
void Floor::setBroadcastAddress(Address newBroadcastAddress){
    this->broadcastAddress = newBroadcastAddress;
}

/**
 * @brief Floor::setNetworkAddress
 * @param newNetworkAddress
 * set the network adress
 */
void Floor::setNetworkAddress(Address newNetworkAddress){
    this->networkAddress = newNetworkAddress;
}

/**
 * @brief Floor::getBroadcastAddress
 * @return broadcast adress
 */
Address Floor::getBroadcastAddress(){
    return broadcastAddress;
}

/**
 * @brief Floor::getNetworkAddress
 * @return network adress
 */
Address Floor::getNetworkAddress(){
    return networkAddress;
}


