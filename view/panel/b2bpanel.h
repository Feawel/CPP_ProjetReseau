/*
 * b2bpanel.h
 *
 *  Created on: 25 nov. 2013
 *      Author: MOULIN
 */

#ifndef B2BPANEL_H
#define B2BPANEL_H

#endif // B2BPANEL_H

#include <QWidget>
#include <QDoubleSpinBox>

class Building_BuildingPanel: public QWidget
{
public:
    Building_BuildingPanel();
private:
    QDoubleSpinBox* distanceField;
};
