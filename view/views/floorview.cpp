/*
 * floorview.cpp
 *
 *  Created on: 25 nov. 2013
 *      Author: MOULIN
 */

#include "floorview.h"
#include <iostream>

using namespace std;

FloorView::FloorView(Floor* floor): floor(floor)
{
}

LocationPanel* FloorView::getFloorPanel() const
{
    return panel;
}

void FloorView::setFloorPanel(LocationPanel* floorPanel)
{
    panel= floorPanel;
}

Floor* FloorView::getFloor() const
{
    return floor;
}

QString FloorView::getUsers() const
{
    //cout << floor->getUserNumbers()[0] <<endl;
    return "D: " + QString::number(floor->getUserNumber(NUserType::DEFAULT)) + " S: " +QString::number(floor->getUserNumber(NUserType::SUP))+" A: "+QString::number(floor->getUserNumber(NUserType::ADMIN));
}
