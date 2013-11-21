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
#include <string>
#include "../model/location/building.h"
#include "../model/constant.h"
#include "buildingpanel.h"

class BuildingView: public QRect {
public:
    BuildingView(int x, int y, int width, int height, std::string name);
    Building* getBuilding();
    BuildingPanel* getPanel();
    QString getName();
    QString getUsers();
    void setUsers(NUserType::UserType userType, unsigned int userNumber);
private:
    Building *building;
    BuildingPanel *panel;
};

#endif // BUILDINGVIEW_H
