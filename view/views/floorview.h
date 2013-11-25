/*
 * floorview.h
 *
 *  Created on: 25 nov. 2013
 *      Author: MOULIN
 */

#ifndef FLOORVIEW_H
#define FLOORVIEW_H

#include <QRect>
#include <QString>

#include "../panel/locationpanel.h"
#include "../../model/location/floor.h"

class FloorView
{
public:
    FloorView(Floor* floor);
    LocationPanel* getFloorPanel() const;
    void setFloorPanel(LocationPanel* floorPanel);
    Floor* getFloor() const;
    QString getUsers() const;
private:
    Floor* floor;
    LocationPanel* panel;
};

#endif // FLOORVIEW_H
