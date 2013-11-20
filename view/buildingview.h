/*
 * buildingview.h
 *
 *  Created on: 19 nov. 2013
 *      Author: MOULIN
 */

#ifndef BUILDINGVIEW_H
#define BUILDINGVIEW_H

#include <QRect>

class BuildingView: public QRect {
public:
    BuildingView(int x, int y, int width, int height);
private:
};

#endif // BUILDINGVIEW_H
