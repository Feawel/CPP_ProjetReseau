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
#include "../model/location/building.h"
#include "../model/constant.h"
#include "../model/location/floor.h"
#include "floorview.h"

class BuildingView: public QRect {
public:
    BuildingView(std::string name);
    Building* getBuilding();
    QString getName();
    QString getUsers();
    void setUsers(NUserType::UserType userType, unsigned int userNumber);
    QPoint getMidTop();
    QPoint getMidBottom();
    QPoint getMidLeft();
    QPoint getMidRight();
    void addFloor();
    std::vector<FloorView*> getFloorViews();

private:
    Building *building;
    std::vector<FloorView*> floorViews;

};

#endif // BUILDINGVIEW_H
