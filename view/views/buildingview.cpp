/*
 * buildingview.cpp
 *
 *  Created on: 19 nov. 2013
 *      Author: MOULIN
 */

#include "buildingview.h"
#include "../../model/constant.h"

using namespace std;

BuildingView::BuildingView(string name ): QRect(100,100,150,200), building(0)
{
    building = new Building(name);
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
    return "D: " + QString::number(building->getUserNumber(NUserType::DEFAULT)) + " S: " +QString::number(building->getUserNumber(NUserType::SUP))+" A: "+QString::number(building->getUserNumber(NUserType::ADMIN));
}

QPoint BuildingView::getMidTop()
{
    QPoint point(left()+width()/2,top());
    return point;
}

QPoint BuildingView::getMidBottom()
{
    QPoint point(left()+width()/2,bottom());
    return point;
}

QPoint BuildingView::getMidLeft()
{
    QPoint point(left(),top()+height()/2);
    return point;
}

QPoint BuildingView::getMidRight()
{
    QPoint point(right(),top()+height()/2);
    return point;
}

FloorView* BuildingView::addFloor()
{
    int fn = floorViews.size();
    if(height()<15 + (fn+1)* 90)
        setHeight(height()+90);
    FloorView *floorView = new FloorView(building->addFloor());
    floorViews.push_back(floorView);
    return floorView;
}

vector<FloorView*> BuildingView::getFloorViews()
{
    return floorViews;
}

void BuildingView::setBuildingPanel(BuildingPanel* buildingPanel)
{
    panel=buildingPanel;
}

BuildingPanel* BuildingView::getBuildingPanel()
{
    return panel;
}
