/*
 * b2bpanel.cpp
 *
 *  Created on: 25 nov. 2013
 *      Author: MOULIN
 */

#include <QFormLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QCheckBox>

#include "b2bpanel.h"

Building_BuildingPanel::Building_BuildingPanel(): QWidget()
{
    distanceField = new QDoubleSpinBox;

    QGroupBox* existingTechsGroup = new QGroupBox;
    QVBoxLayout* existingTechsLayout = new QVBoxLayout;
    QCheckBox* wifiCheck = new QCheckBox("Wifi Bridge:");
    QCheckBox* infraredCheck = new QCheckBox("Infrared:");
    QCheckBox* fiberCheck = new QCheckBox("Fiber:");
    QCheckBox* twistedPairCheck = new QCheckBox("Twisted Pair:");
    existingTechsLayout->addWidget(wifiCheck);
    existingTechsLayout->addWidget(infraredCheck);
    existingTechsLayout->addWidget(fiberCheck);
    existingTechsLayout->addWidget(twistedPairCheck);

    existingTechsGroup->setLayout(existingTechsLayout);

    QFormLayout *layout = new QFormLayout;
    layout->addRow("Distance (m):", distanceField);
    layout->addRow("Existing technologies:", existingTechsGroup);

    this->setLayout(layout);
}

Building_BuildingPanel::~Building_BuildingPanel()
{
    delete distanceField;
}


QDoubleSpinBox* Building_BuildingPanel::getDistanceField() const
{
    return distanceField;
}
