/*
 * floorview.cpp
 *
 *  Created on: 25 nov. 2013
 *      Author: MOULIN
 */

#include "floorview.h"

using namespace std;

FloorView::FloorView(Floor* floor): floor(floor)
{
}

FloorView::~FloorView()
{
    delete panel;
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
    return "D: " + QString::number(floor->getUserNumber(NUserType::DEFAULT)) + " S: " +QString::number(floor->getUserNumber(NUserType::SUP))+" A: "+QString::number(floor->getUserNumber(NUserType::ADMIN));
}

QString FloorView::getName() const
{
    return QString::fromStdString(floor->getName());
}
