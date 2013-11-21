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
#include "buildingpanel.h"

class BuildingView: public QRect {
public:
    BuildingView(int x, int y, int width, int height, std::string name);
    Building* getBuilding();
    BuildingPanel* getPanel();
    QString getName();
    QString getUsers();
private:
    Building *building;
    BuildingPanel *panel;
};

#endif // BUILDINGVIEW_H
