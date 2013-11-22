/*
 * b2bview.h
 *
 *  Created on: 19 nov. 2013
 *      Author: MOULIN
 */

#ifndef B2BVIEW_H
#define B2BVIEW_H

#include <QLine>
#include <QPoint>

#include "../model/location/building_building.h"
#include "buildingview.h"

class Building_BuildingView
{
public:
    Building_BuildingView(BuildingView *buildingView1, BuildingView *buildingView2);
    QLine getLine() const;
private:
    Building_Building *b2b;
    BuildingView* buildingView1;
    BuildingView* buildingView2;
};

#endif // B2BVIEW_H
