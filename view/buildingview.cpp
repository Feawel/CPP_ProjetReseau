/*
 * buildingview.cpp
 *
 *  Created on: 19 nov. 2013
 *      Author: MOULIN
 */

#include "buildingview.h"
#include "../model/constant.h"

using namespace std;

BuildingView::BuildingView( int x, int y, int width, int height, string name ): QRect(x, y, width, height), building(0)
{
    building = new Building(name);
    panel = new BuildingPanel;
}

Building* BuildingView::getBuilding()
{
    return building;
}

BuildingPanel* BuildingView::getPanel()
{
    return panel;
}

QString BuildingView::getName()
{
    return QString::fromStdString(building->getName());
}


QString BuildingView::getUsers()
{
    return "D: " + QString::number(building->getUserNumber(NUserType::DEFAULT));
}

void BuildingView::setUsers(NUserType::UserType userType, unsigned int userNumber)
{
    building->setUserNumber(userType, userNumber);
}
