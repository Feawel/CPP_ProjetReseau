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

BuildingView::~BuildingView()
{
    for(unsigned int i =0; i <floorViews.size(); i++)
    {
        delete floorViews[i];
    }
    delete building;
    delete panel;
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
    int def = 0;
    int sup = 0;
    int admin = 0;
    if(panel->isReadOnly())
    {
        for(unsigned int i = 0 ;i< building->getFloors().size(); i++)
        {
            def += building->getFloors()[i]->getUserNumber(NUserType::DEFAULT);
            sup += building->getFloors()[i]->getUserNumber(NUserType::SUP);
            admin += building->getFloors()[i]->getUserNumber(NUserType::ADMIN);
        }
    }
    else
    {
        def = building->getUserNumber(NUserType::DEFAULT);
        sup = building->getUserNumber(NUserType::SUP);
        admin = building->getUserNumber(NUserType::ADMIN);
    }
    return "D: " + QString::number(def) + " S: " +QString::number(sup)+" A: "+QString::number(admin);
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
    Floor *floor(building->addFloor());
    FloorView *floorView = new FloorView(floor);
    floorViews.push_back(floorView);

    panel->setUsersReadOnly();
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
