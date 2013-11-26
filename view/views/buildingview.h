/*
 * buildingview.h
 *
 *  Created on: 19 nov. 2013
 *      Author: MOULIN
 */

#ifndef BUILDINGVIEW_H
#define BUILDINGVIEW_H

#include <QRect>
#include <QString>
#include <QPoint>
#include <string>
#include <vector>
#include "../../model/location/building.h"
#include "../../model/constant.h"
#include "../../model/location/floor.h"
#include "floorview.h"
#include "../panel/buildingpanel.h"

class BuildingView: public QRect {
public:
    BuildingView(std::string name);
    ~BuildingView();
    Building* getBuilding();
    QString getName();
    QString getUsers();
    void setUsers(NUserType::UserType userType, unsigned int userNumber);
    QPoint getMidTop();
    QPoint getMidBottom();
    QPoint getMidLeft();
    QPoint getMidRight();
    FloorView* addFloor();
    std::vector<FloorView*> getFloorViews();
    void setBuildingPanel(BuildingPanel* buildingPanel);
    BuildingPanel* getBuildingPanel();

private:
    Building *building;
    std::vector<FloorView*> floorViews;
    BuildingPanel *panel;

};

#endif // BUILDINGVIEW_H
