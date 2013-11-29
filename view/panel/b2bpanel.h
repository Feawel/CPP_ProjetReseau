/*
 * b2bpanel.h
 *
 *  Created on: 25 nov. 2013
 *      Author: MOULIN
 */

#ifndef B2BPANEL_H
#define B2BPANEL_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <vector>
#include "model/constant.h"

class Building_BuildingPanel: public QWidget
{
public:
    Building_BuildingPanel();
    ~Building_BuildingPanel();
    QDoubleSpinBox* getDistanceField() const;
    QCheckBox* getExistingTechCheck(NTechnology::Technology technology) const;
private:
    QDoubleSpinBox* distanceField;
    std::vector<QCheckBox*> existingTechFields;
};
#endif // B2BPANEL_H

