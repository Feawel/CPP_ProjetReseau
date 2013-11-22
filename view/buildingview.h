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
#include "../model/location/building.h"
#include "../model/constant.h"

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

private:
    Building *building;

};

#endif // BUILDINGVIEW_H
