/*
 * floorview.h
 *
 *  Created on: 25 nov. 2013
 *      Author: MOULIN
 */

#ifndef FLOORVIEW_H
#define FLOORVIEW_H

#include <QRect>
#include "../model/location/floor.h"

class FloorView
{
public:
    FloorView(Floor* floor);
    QRect getRect();
private:
    Floor* floor;
};

#endif // FLOORVIEW_H
