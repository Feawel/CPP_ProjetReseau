/*
 * buildingview.cpp
 *
 *  Created on: 19 nov. 2013
 *      Author: MOULIN
 */

#include "buildingview.h"

using namespace std;

BuildingView::BuildingView( int x, int y, int width, int height, string name ): QRect(x, y, width, height), building(0)
{
    building = new Building(0,name);
}

Building* BuildingView::getBuilding()
{
    return building;
}

QString BuildingView::getName()
{
    return QString::fromStdString(building->getName());
}


QString BuildingView::getUsers()
{
    return QString::fromStdString("Users: ") + QString::number(building->getUserNumber());
}
