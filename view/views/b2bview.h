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

#include "../../model/location/building_building.h"
#include "buildingview.h"
#include "../panel/b2bpanel.h"

class Building_BuildingView
{
public:
    Building_BuildingView(BuildingView *buildingView1, BuildingView *buildingView2);
    QLine getLine() const;
    Building_BuildingPanel* getB2bPanel();
    void setB2bPanel(Building_BuildingPanel* b2bPanel);
    Building_Building* getB2b() const;
    QString getDistance() const;
private:
    Building_Building *b2b;
    BuildingView* buildingView1;
    BuildingView* buildingView2;
    Building_BuildingPanel* panel;
};

#endif // B2BVIEW_H
